#ifndef PRODUCTMODELWINDOW_H
#define PRODUCTMODELWINDOW_H

#include "clientsocket.h"
#include "product.h"
#include <QDialog>

namespace Ui {
class AddProductWindow;
}

class ProductModelWindow : public QDialog {
  Q_OBJECT

public:
  explicit ProductModelWindow(ClientSocket *socket, const int commandCode,
                              Product * = nullptr, QWidget *parent = nullptr);
  ~ProductModelWindow();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::AddProductWindow *ui;
  ClientSocket *_socket;
  Product *_updatedProduct;
  int _commandCode;

  void createProduct(QByteArray json);
  void updateProduct(QByteArray json);
  void deleteProduct(QByteArray json);
};

#endif // PRODUCTMODELWINDOW_H
