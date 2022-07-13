#pragma once

#include "clientsocket.h"
#include "product.h"
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void start();

private slots:
  void on_exit_button_clicked();

  void on_action_add_product_triggered();

  void on_add_product_button_clicked();

  void on_actionUpdate_tables_triggered();

  void on_update_table_button_clicked();

  void on_read_product_button_clicked();

  void on_delete_product_button_clicked();

private:
  ClientSocket *_socket;
  Ui::MainWindow *ui;
  void init();
  void reset();
  Product *getCurrentProduct();
  static long PACKETS_SENT;
  static char ID;
};
