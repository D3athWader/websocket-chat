#include <atomic>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/beast.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/beast/core/ostream.hpp>
#include <boost/beast/websocket/error.hpp>
#include <boost/beast/websocket/stream.hpp>
#include <cctype>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>

#include <utility>
std::atomic<int> client_id{0};
std::unordered_map<int,
                   std::pair<std::shared_ptr<boost::beast::websocket::stream<
                                 boost::asio::ip::tcp::socket>>,
                             std::string>>
    clients;
// Parser
// {int,payload}
// int -> action to be performed
// payload -> message to be shown
// 0 = broadcast username
// 1 = message
// 2 = disconnect
// 3 = invalid username
std::pair<int, std::string> parser(std::string req) {
  int n = req.find("{");
  req.erase(n, 1);
  n = req.rfind("}");
  req.erase(n, 1);
  int fn = req.find(";");
  std::string med = req.substr(0, fn);
  std::pair<int, std::string> res = {-1, ""};
  res.first = std::stoi(med);
  res.second = req.substr(fn + 1);
  return res;
};
std::string stringify(std::pair<int, std::string> req) {
  std::string msg = "{";
  msg.append(std::to_string(req.first));
  msg.append(";");
  msg.append(req.second);
  msg.append("}");
  return msg;
}
void assign_username(
    std::shared_ptr<
        boost::beast::websocket::stream<boost::asio::ip::tcp::socket>>
        ws,
    int id) {
  int action = 0;
  boost::beast::flat_buffer buffer;
  ws->read(buffer);
  std::pair<int, std::string> pair =
      parser(boost::beast::buffers_to_string(buffer.data()));
  std::string uname = pair.second;
  if (uname.find(" ") == std::string::npos || uname.size() == 0) {
    for (int i = 0; i < uname.size(); i++) {
      if (std::isspace(uname[i])) {
        uname.erase(i, 1);
        i--;
      }
    }
  } else if (uname.find(" ") != std::string::npos) {
    buffer.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(10000, 100000);
    uname = "Guest" + std::to_string(dist(gen));
    action = 3;
  }
  buffer.clear();
  clients[id].second = uname;
  std::string payload;
  for (auto it : clients) {
    payload += it.second.second + "\n";
  }
  std::string send = stringify({action, payload});
  boost::beast::ostream(buffer) << send;
  for (auto it : clients) {
    it.second.first->write(buffer.cdata());
  }
};

void handle_client(boost::asio::ip::tcp::socket sock) {
  int id = client_id.fetch_add(1);
  try {
    auto ws = std::make_shared<
        boost::beast::websocket::stream<boost::asio::ip::tcp::socket>>(
        std::move(sock));
    clients[id].first = ws;
    ws->accept();
    assign_username(ws, id);
    boost::beast::flat_buffer buffer;
    boost::beast::flat_buffer buf;
    while (1) {
      try {
        ws->read(buffer);
        const std::string out = boost::beast::buffers_to_string(buffer.data());
        buf.clear();
        std::pair<int, std::string> outp = parser(out);
        const std::string str = clients[id].second + " : " + outp.second;
        const int action = 1;
        std::string payload = stringify({action, str});
        boost::beast::ostream(buf) << payload;
        for (auto it : clients) {
          it.second.first->write(buf.cdata());
        }
        buffer.clear();
      } catch (boost::beast::system_error const &e) {
        int action = 2;
        if (e.code() == boost::beast::websocket::error::closed) {
          std::cout << "Client " << id << " " << clients[id].second
                    << " Disconnected" << "\n";
        } else {
          std::cerr << "Error" << e.code() << " " << e.code().message() << "\n";
        }
        for (auto it : clients) {
          if (it.first == id) {
          } else {
            buf.clear();
            std::string payload = stringify({action, clients[id].second});
            boost::beast::ostream(buf) << payload;
            it.second.first->write(buf.cdata());
          }
        }
        clients.erase(id);
        break;
      }
    }
  } catch (boost::beast::system_error const &e) {
    std::cerr << "Error: " << e.code() << " " << e.code().message() << "\n";
    clients.erase(id);
  }
}
int main(int argc, char *argv[]) {
  const boost::asio::ip::address address =
      boost::asio::ip::make_address("127.0.0.1");
  const unsigned short port = static_cast<unsigned short>(std::atoi("8083"));
  boost::asio::io_context ioc{4};
  boost::asio::ip::tcp::acceptor acceptor(ioc, {address, port});
  while (1) {
    boost::asio::ip::tcp::socket socket(ioc);
    acceptor.accept(socket);
    std::cout << "Socket accepted" << std::endl;
    std::thread(handle_client, std::move(socket)).detach();
  }
  return 0;
}
