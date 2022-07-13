#include "mainwindow.h"
#include "clientsocket.h"
#include "groupswindow.h"
#include "packetutil.h"
#include "product.h"
#include "productmodelwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>

long MainWindow::PACKETS_SENT = 0;

const char MainWindow::ID = 69;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _socket(new ClientSocket(this)),
      ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->storage_table->setSortingEnabled(false);
  _socket->connect();
  init();
}

MainWindow::~MainWindow() {
  delete ui;
  delete _socket;
}

void MainWindow::init() { reset(); }

void MainWindow::reset() {
  ui->storage_table->setRowCount(0);
  int len = 0;
  QByteArray message("0+ +0");
  QByteArray data =
      PacketUtil::generatePacket(ID, PACKETS_SENT++, 4, 0, message, len);
  QByteArray moreData = _socket->sendData(data, len);
  Packet pack = PacketUtil::receivePacket(moreData);
  QStringList allData = QString(pack.message).split('\n');
  Product newProduct;
  for (int i = 0; i < allData.length(); ++i) {
    QJsonDocument temp = QJsonDocument::fromJson(allData.at(i).toUtf8());
    QJsonObject obj = temp.object();
    QStringList keys = obj.keys();
    if (keys.length() < 7)
      continue;
    for (int j = 0; j < keys.length(); ++j) {
      if (keys[j] == "Amount") {
        newProduct.amount = obj.value(keys[j]).toInt();
        continue;
      }
      if (keys[j] == "Description") {
        newProduct.description = obj.value(keys[j]).toString();
        continue;
      }
      if (keys[j] == "Group") {
        newProduct.group = obj.value(keys[j]).toInt();
        continue;
      }
      if (keys[j] == "ID") {
        newProduct.id = obj.value(keys[j]).toInt();
        continue;
      }
      if (keys[j] == "Manufacturer") {
        newProduct.manufacturer = obj.value(keys[j]).toString();
        continue;
      }
      if (keys[j] == "Name") {
        newProduct.name = obj.value(keys[j]).toString();
        continue;
      }
      if (keys[j] == "Price") {
        newProduct.price = obj.value(keys[j]).toDouble();
        continue;
      }
    }

    ui->storage_table->insertRow(ui->storage_table->rowCount());
    ui->storage_table->setItem(
        ui->storage_table->rowCount() - 1, 0,
        new QTableWidgetItem(QString::number(newProduct.id) + ""));
    ui->storage_table->setItem(ui->storage_table->rowCount() - 1, 1,
                               new QTableWidgetItem(newProduct.name));
    ui->storage_table->setItem(ui->storage_table->rowCount() - 1, 2,
                               new QTableWidgetItem(newProduct.description));
    ui->storage_table->setItem(ui->storage_table->rowCount() - 1, 3,
                               new QTableWidgetItem(newProduct.manufacturer));
    ui->storage_table->setItem(
        ui->storage_table->rowCount() - 1, 4,
        new QTableWidgetItem(QString::number(newProduct.amount) + ""));
    ui->storage_table->setItem(
        ui->storage_table->rowCount() - 1, 5,
        new QTableWidgetItem(QString::number(newProduct.price) + ""));
    ui->storage_table->setItem(
        ui->storage_table->rowCount() - 1, 6,
        new QTableWidgetItem(QString::number(newProduct.group) + ""));
  }
}

void MainWindow::on_exit_button_clicked() {
  _socket->close();
  this->close();
}

void MainWindow::on_action_add_product_triggered() {
  ProductModelWindow win(_socket, 0);
  win.exec();
  win.show();
  reset();
}

void MainWindow::on_add_product_button_clicked() {
  on_action_add_product_triggered();
}

void MainWindow::on_actionUpdate_tables_triggered() { reset(); }

void MainWindow::on_update_table_button_clicked() { reset(); }

void MainWindow::on_read_product_button_clicked() {
  ProductModelWindow win(_socket, 2, getCurrentProduct());
  win.exec();
  win.show();
  reset();
}

void MainWindow::on_delete_product_button_clicked() {
  QMessageBox::StandardButton reply = QMessageBox::question(
      this, "Confirm delete", "Do you really want to delete this?");
  if (reply == QMessageBox::Yes) {
    int len = 0;
    QString paddedID("00000");
    paddedID.append(QString::number(getCurrentProduct()->id));

    QByteArray data =
        PacketUtil::generatePacket(0, 0, 3, 0, paddedID.toUtf8(), len);
    Packet pack = PacketUtil::receivePacket(_socket->sendData(data, len));
    reset();
  }
}

Product *MainWindow::getCurrentProduct() {
  if (ui->storage_table->selectedItems().size() > 0) {
    Product *product = new Product();
    int currentRow = ui->storage_table->selectedItems().first()->row();
    qDebug() << currentRow << " " << ui->storage_table->currentRow();
    product->id = ui->storage_table->item(currentRow, 0)->text().toInt();
    product->name = ui->storage_table->item(currentRow, 1)->text();
    product->amount = ui->storage_table->item(currentRow, 4)->text().toInt();
    product->description = ui->storage_table->item(currentRow, 2)->text();
    product->manufacturer = ui->storage_table->item(currentRow, 3)->text();
    product->group = ui->storage_table->item(currentRow, 6)->text().toInt();
    product->price = ui->storage_table->item(currentRow, 5)->text().toDouble();
    return product;
  } else {
    return nullptr;
  }
}

void MainWindow::on_groups_menu_button_clicked() {
  GroupsWindow win(_socket, this);
  win.exec();
  win.show();
  reset();
}
