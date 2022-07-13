#include "clientsocket.h"
#include "crc16.h"
#include "decryptor.h"
#include "encryptor.h"
#include "mainwindow.h"
#include "packetutil.h"

#include <QApplication>
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
