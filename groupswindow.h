#ifndef GROUPSWINDOW_H
#define GROUPSWINDOW_H

#include "clientsocket.h"
#include "group.h"
#include <QDialog>

namespace Ui {
class GroupsWindow;
}

class GroupsWindow : public QDialog {
  Q_OBJECT

public:
  explicit GroupsWindow(ClientSocket *socket, QWidget *parent = nullptr);
  ~GroupsWindow();

private slots:
    void on_add_group_button_clicked();

    void on_edit_group_button_clicked();

    void on_delete_group_button_clicked();

    void on_refresh_table_button_clicked();

private:
  Ui::GroupsWindow *ui;
  ClientSocket *_socket;

  Group *getCurrentGroup();
  void init();
  void reset();
};

#endif // GROUPSWINDOW_H
