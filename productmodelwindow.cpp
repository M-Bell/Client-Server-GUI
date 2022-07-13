#include "productmodelwindow.h"
#include "packetutil.h"
#include "ui_addproductwindow.h"
#include <QJsonDocument>
#include <QJsonObject>

ProductModelWindow::ProductModelWindow(ClientSocket *socket,
                                       const int commandCode, Product *product,
                                       QWidget *parent)
    : QDialog(parent), ui(new Ui::AddProductWindow), _socket(socket),
      _updatedProduct(product), _commandCode(commandCode) {
  ui->setupUi(this);
  if (_updatedProduct) {
    ui->product_name->setText(_updatedProduct->name);
    ui->product_amount->setText(QString::number(_updatedProduct->amount));
    ui->product_amount->setEnabled(false);
    ui->product_description->setText(_updatedProduct->description);
    ui->product_manufacturer->setText(_updatedProduct->manufacturer);
    ui->product_price->setText(QString::number(_updatedProduct->price));
  }

  if (commandCode == 3) {
    on_buttonBox_accepted();
  }
}

ProductModelWindow::~ProductModelWindow() {
  delete ui;
  if (_updatedProduct)
    delete _updatedProduct;
}

void ProductModelWindow::createProduct(QByteArray json) {
  int len = 0;
  QByteArray data = PacketUtil::generatePacket(0, 0, 0, 0, json, len);
  Packet pack = PacketUtil::receivePacket(_socket->sendData(data, len));
}

void ProductModelWindow::deleteProduct(QByteArray json) {
  int len = 0;
  QByteArray data = PacketUtil::generatePacket(0, 0, 3, 0, json, len);
  Packet pack = PacketUtil::receivePacket(_socket->sendData(data, len));
}

void ProductModelWindow::updateProduct(QByteArray json) {
  int len = 0;
  QByteArray data = PacketUtil::generatePacket(0, 0, 2, 0, json, len);
  Packet pack = PacketUtil::receivePacket(_socket->sendData(data, len));
}

void ProductModelWindow::on_buttonBox_accepted() {
  QJsonObject recordObject;
  if (_updatedProduct) {
    recordObject.insert("ID", QJsonValue::fromVariant(
                                  QString::number(_updatedProduct->id) + ""));
  }
  recordObject.insert("Name",
                      QJsonValue::fromVariant(ui->product_name->text()));
  recordObject.insert("Amount",
                      QJsonValue::fromVariant(ui->product_amount->text()));
  recordObject.insert(
      "Description",
      QJsonValue::fromVariant(ui->product_description->toPlainText()));
  recordObject.insert("Group", QJsonValue::fromVariant("1"));
  recordObject.insert("Manufacturer", QJsonValue::fromVariant(
                                          ui->product_manufacturer->text()));
  recordObject.insert("Price",
                      QJsonValue::fromVariant(ui->product_price->text()));
  QJsonDocument doc(recordObject);
  switch (_commandCode) {
  case 0: {
    createProduct(doc.toJson(QJsonDocument::Compact));
    break;
  }
  case 1: {
    // readProduct(doc.toJson(QJsonDocument::Compact));
    break;
  }
  case 2: {
    updateProduct(doc.toJson(QJsonDocument::Compact));
    break;
  }
  case 3: {
    deleteProduct(doc.toJson(QJsonDocument::Compact));
    break;
  }
  }
}
