#include "connector.h"
// #include "qtcpsocket.h"
#include "QtWebSockets/qwebsocket.h"
#include "parser.h"
#include <qt/QtNetwork/qabstractsocket.h>
connector::connector(QObject *parent) : QObject{parent} {
  connect(&_socket, &QWebSocket::connected, this, &connector::connected);
  connect(&_socket, &QWebSocket::disconnected, this, &connector::disconnected);
  connect(&_socket, &QWebSocket::stateChanged, this,
          &connector::socket_stateChanged);
  connect(&_socket, &QWebSocket::errorOccurred, this,
          &connector::errorOccurred);
  connect(&_socket, &QWebSocket::textMessageReceived, this,
          &connector::socket_readyRead);
}
void connector::connectTo(QString ip, int port) {
  if (_socket.state() == QAbstractSocket::ConnectedState) {
    if (ip == _ip && port == _port) {
      return;
    }
    _socket.close();
  }
  _ip = ip;
  _port = port;
  QString url = QString("ws://%1:%2").arg(_ip).arg(_port);
  _socket.open(QUrl(url));
}
void connector::socket_stateChanged(QAbstractSocket::SocketState state) {
  if (state == QAbstractSocket::UnconnectedState) {
    _socket.close();
  }
  emit stateChanged(state);
}
void connector::disconnect() { _socket.close(); }
void connector::socket_readyRead(QString data) { emit dataReady(data); }
void connector::sendMessage(const QString message) {
  _socket.sendTextMessage(message);
}
