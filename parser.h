#ifndef PARSER_H
#define PARSER_H

#include "qurl.h"
#include <string>
#include <utility>
class parser {

public:
  parser();

  QString stringify(std::pair<int, QString>);
  std::pair<int, QString> parse(QString);
};
#endif // PARSER_H
