#include "groupswindow.h"
#include "groupmodelwindow.h"
#include "packetutil.h"
#include "ui_groupswindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
GroupsWindow::GroupsWindow(ClientSocket *socket, QWidget *parent)
    : QDialog(parent), ui(new Ui::GroupsWindow), _socket(socket) {
  ui->setupUi(this);
  ui->groups_table->setSortingEnabled(false);
  init();
}

GroupsWindow::~GroupsWindow() { delete ui; }

void GroupsWindow::init() { reset(); }

void GroupsWindow::reset() {
  ui->groups_table->setRowCount(0);
  int len = 0;
  QByteArray message("0+ +0");
  QByteArray data = PacketUtil::generatePacket(0, 0, 9, 0, message, len);
  QByteArray moreData = _socket->sendData(data, len);
  Packet pack = PacketUtil::receivePacket(moreData);
  QStringList allData = QString(pack.message).split('\n');
  Group newGroup;
  for (int i = 0; i < allData.length(); ++i) {
    QJsonDocument temp = QJsonDocument::fromJson(allData.at(i).toUtf8());
    QJsonObject obj = temp.object();
    QStringList keys = obj.keys();
    if (keys.length() < 3)
      continue;
    for (int j = 0; j < keys.length(); ++j) {
      if (keys[j] == "Description") {
        newGroup.description = obj.value(keys[j]).toString();
        continue;
      }
      if (keys[j] == "ID") {
        newGroup.id = obj.value(keys[j]).toInt();
        continue;
      }

      if (keys[j] == "Name") {
        newGroup.name = obj.value(keys[j]).toString();
        continue;
      }
    }

    ui->groups_table->insertRow(ui->groups_table->rowCount());
    ui->groups_table->setItem(
        ui->groups_table->rowCount() - 1, 0,
        new QTableWidgetItem(QString::number(newGroup.id) + ""));
    ui->groups_table->setItem(ui->groups_table->rowCount() - 1, 1,
                              new QTableWidgetItem(newGroup.name));
    ui->groups_table->setItem(ui->groups_table->rowCount() - 1, 2,
                              new QTableWidgetItem(newGroup.description));
  }
}

void GroupsWindow::on_add_group_button_clicked() {
  GroupModelWindow win(_socket, 5);
  win.exec();
  win.show();
  reset();
}

void GroupsWindow::on_edit_group_button_clicked() {
  GroupModelWindow win(_socket, 7, getCurrentGroup());
  win.exec();
  win.show();
  reset();
}

Group *GroupsWindow::getCurrentGroup() {
  if (ui->groups_table->selectedItems().size() > 0) {
    Group *group = new Group();
    int currentRow = ui->groups_table->selectedItems().first()->row();
    qDebug() << currentRow << " " << ui->groups_table->currentRow();
    group->id = ui->groups_table->item(currentRow, 0)->text().toInt();
    group->name = ui->groups_table->item(currentRow, 1)->text();
    group->description = ui->groups_table->item(currentRow, 2)->text();
    return group;
  } else {
    return nullptr;
  }
}

void GroupsWindow::on_delete_group_button_clicked() {
  QMessageBox::StandardButton reply = QMessageBox::question(
      this, "Confirm delete", "Do you really want to delete this?");
  if (reply == QMessageBox::Yes) {
    int len = 0;
    QString paddedID("00000");
    paddedID.append(QString::number(getCurrentGroup()->id));

    QByteArray data =
        PacketUtil::generatePacket(0, 0, 8, 0, paddedID.toUtf8(), len);
    Packet pack = PacketUtil::receivePacket(_socket->sendData(data, len));
    reset();
  }
}

void GroupsWindow::on_refresh_table_button_clicked() { reset(); }
