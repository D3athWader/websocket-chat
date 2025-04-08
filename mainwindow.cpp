#include "mainwindow.h"
#include "parser.h"
#include "qabstractsocket.h"
#include "qhostaddress.h"
#include "qlist.h"
#include "qobjectdefs.h"
#include "qurl.h"
#include "ui_mainwindow.h"
#include <QMetaEnum>
#include <QStyle>
#include <qt/QtCore/qglobal.h>
#include <utility>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setconnector();
  ui->groupBox_2->setDisabled(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Ip_textChanged(const QString &arg1) {
  QHostAddress address(arg1);
  QString state = "0";
  if (arg1 == "...") {
    state = "";
  }
  if (QAbstractSocket::IPv4Protocol == address.protocol()) {
    state = "1";
  }
  ui->Ip->setProperty("state", state);
  ui->Ip->style()->unpolish(ui->Ip);
  ui->Ip->style()->polish(ui->Ip);
  ui->Ip->update();
}

void MainWindow::on_connect_clicked() {
  if (ui->connect->text() == "Disconnect") {
    QString send = _parser.stringify({2, ""});
    _connector.sendMessage(send);
    _connector.disconnect();
    ui->groupBox_2->setDisabled(true);
  } else {
    auto ip = ui->Ip->text();
    auto port = ui->port->value();
    _connector.connectTo(ip, port);
  }
}

void MainWindow::device_connected() {
  ui->console->addItem("Connected To Device");
  ui->connect->setText("Disconnect");
  ui->groupBox_2->setDisabled(false);
  ui->console->addItem("First Message will be treated as your username!");
}
void MainWindow::device_disconnected() {
  ui->console->addItem("Disconnected");
  ui->users->clear();
  ui->connect->setText("Connect");
};
void MainWindow::device_stateChanged(QAbstractSocket::SocketState stt) {
  // ui->console->addItem("State Changed");
  QMetaEnum metaenum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
  ui->console->addItem(metaenum.valueToKey(stt));
};
void MainWindow::device_errorOccurred(QAbstractSocket::SocketError err) {
  QMetaEnum metaenum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
  ui->console->addItem(metaenum.valueToKey(err));
};
void MainWindow::device_dataReady(QString data) {
  std::pair<int, QString> res = _parser.parse(data);
  switch (res.first) {
  case 0:
    ui->users->addItem(res.second);
    break;
  case 1:
    ui->console->addItem(res.second);
    break;
  case 3:
    ui->console->addItem("Invalid Username");
    // ui->console->addItem("SERVER:: Your Username: "+res.second);
    ui->users->addItem(res.second);
    break;
  case 2:
    QListWidgetItem *it =
        ui->users->findItems(res.second, Qt::MatchExactly).first();
    delete ui->users->takeItem(ui->users->row(it));
    break;
  }
}
void MainWindow::setconnector() {
  connect(&_connector, &connector::connected, this,
          &MainWindow::device_connected);
  connect(&_connector, &connector::disconnected, this,
          &MainWindow::device_disconnected);
  connect(&_connector, &connector::stateChanged, this,
          &MainWindow::device_stateChanged);
  connect(&_connector, &connector::errorOccurred, this,
          &MainWindow::device_errorOccurred);
  connect(&_connector, &connector::dataReady, this,
          &MainWindow::device_dataReady);
}
void MainWindow::on_clearbtn_clicked() { ui->console->clear(); }
void MainWindow::on_send_clicked() {
  int action;
  if (first) {
    action = 0;
    first = false;
  } else {
    action = 1;
  }
  const QString message = ui->lineEdit->text().trimmed();
  QString payload = _parser.stringify({action, message});
  _connector.sendMessage(payload);
}
