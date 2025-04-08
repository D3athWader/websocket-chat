#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "QtWebSockets/qwebsocket.h"
#include "qabstractsocket.h"
#include "qchar.h"
// #include "qtcpsocket.h"
#include "qurl.h"
#include <QObject>
#include <QTcpSocket>
#include <qt/QtCore/qglobal.h>
class connector : public QObject {
  Q_OBJECT
public:
  explicit connector(QObject *parent = nullptr);
  void connectTo(QString ip, int port);
  void disconnect();
  void sendMessage(const QString);
signals:
  void connected();
  void disconnected();
  void stateChanged(QAbstractSocket::SocketState);
  void errorOccurred(QAbstractSocket::SocketError);
  void dataReady(QString);
private slots:
  void socket_stateChanged(QAbstractSocket::SocketState state);
  void socket_readyRead(QString);

private:
  QWebSocket _socket;
  QString _ip;
  int _port;
};

#endif // CONNECTOR_H
