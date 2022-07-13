#ifndef GROUPMODELWINDOW_H
#define GROUPMODELWINDOW_H

#include "group.h"
#include <QDialog>
#include <clientsocket.h>

namespace Ui {
class GroupModelWindow;
}

class GroupModelWindow : public QDialog {
  Q_OBJECT

public:
  explicit GroupModelWindow(ClientSocket *socket, const int commandCode,
                            Group *selectedGroup = nullptr,
                            QWidget *parent = nullptr);
  ~GroupModelWindow();

private slots:
    void on_buttonBox_accepted();

private:
  Ui::GroupModelWindow *ui;
  ClientSocket *_socket;
  Group *_selectedGroup;
  int _commandCode;

  void createGroup(QByteArray json);
  void updateGroup(QByteArray json);
};

#endif // GROUPMODELWINDOW_H
