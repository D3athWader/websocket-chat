#include "parser.h"
#include "qurl.h"
#include <utility>

parser::parser() {}
QString parser::stringify(std::pair<int, QString> req) {
  QString res = "{";
  res.append(QString::number(req.first));
  res.append(";");
  res.append(req.second);
  res.append ("}");
  return res;
}
std::pair<int, QString> parser::parse(QString req) {
  std::pair<int, QString> ans;
  std::string res = req.toStdString();
  std::string sec = "";
  int fn = res.find(";");
  res.erase(res.find("{"), 1);
  res.erase(res.rfind("}"), 1);
  std::string fir = res.substr(0, fn);
  ans.first = std::stoi(fir);
  sec = res.substr(fn);
  ans.second = QString::fromStdString(sec);
  return ans;
}
