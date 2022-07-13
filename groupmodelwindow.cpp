#include "groupmodelwindow.h"
#include "packetutil.h"
#include "ui_groupmodelwindow.h"
#include <QJsonDocument>
#include <QJsonObject>

GroupModelWindow::GroupModelWindow(ClientSocket *socket, const int commandCode,
                                   Group *selectedGroup, QWidget *parent)
    : QDialog(parent), ui(new Ui::GroupModelWindow), _socket(socket),
      _selectedGroup(selectedGroup), _commandCode(commandCode) {
  ui->setupUi(this);
  if (_selectedGroup) {
    ui->group_name->setText(_selectedGroup->name);
    ui->group_description->setText(_selectedGroup->description);
  }
}

GroupModelWindow::~GroupModelWindow() {
  delete ui;
  if (_selectedGroup)
    delete _selectedGroup;
}

void GroupModelWindow::createGroup(QByteArray json) {
  int len = 0;
  QByteArray data = PacketUtil::generatePacket(0, 0, 5, 0, json, len);
  Packet pack = PacketUtil::receivePacket(_socket->sendData(data, len));
}

void GroupModelWindow::updateGroup(QByteArray json) {
  int len = 0;
  QByteArray data = PacketUtil::generatePacket(0, 0, 7, 0, json, len);
  Packet pack = PacketUtil::receivePacket(_socket->sendData(data, len));
}

void GroupModelWindow::on_buttonBox_accepted() {
  QJsonObject recordObject;
  if (_selectedGroup) {
    recordObject.insert("ID", QJsonValue::fromVariant(
                                  QString::number(_selectedGroup->id) + ""));
  }
  recordObject.insert("Name", QJsonValue::fromVariant(ui->group_name->text()));
  recordObject.insert("Description", QJsonValue::fromVariant(
                                         ui->group_description->toPlainText()));
  QJsonDocument doc(recordObject);
  switch (_commandCode) {
  case 5: {
    createGroup(doc.toJson(QJsonDocument::Compact));
    break;
  }

  case 7: {
    updateGroup(doc.toJson(QJsonDocument::Compact));
    break;
  }
  }
}
