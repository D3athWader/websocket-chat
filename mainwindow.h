#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connector.h"
#include "parser.h"
#include <QMainWindow>
#include <QStyle>
#include <qt/QtCore/qglobal.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

  bool first = true;

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_Ip_textChanged(const QString &arg1);

  void on_connect_clicked();

  void device_connected();
  void device_disconnected();
  void device_stateChanged(QAbstractSocket::SocketState);
  void device_errorOccurred(QAbstractSocket::SocketError);
  void device_dataReady(QString);

  void on_clearbtn_clicked();
  void on_send_clicked();

private:
  Ui::MainWindow *ui;
  connector _connector;
  parser _parser;

  // methods
  void setconnector();
};
#endif // MAINWINDOW_H
