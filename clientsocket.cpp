#include "clientsocket.h"
#include "packetutil.h"
ClientSocket::ClientSocket(QObject *parent)
    : QObject{parent}, socket(new QTcpSocket(this)) {}

void ClientSocket::connect() {
  socket->connectToHost("127.0.0.1", 9090);

  if (socket->waitForConnected()) {
    qDebug() << "Connected";
  } else {
    qDebug() << "Server unavailable";
  }
}

QByteArray ClientSocket::sendData(const QByteArray data, const int len) {
  if (socket->isOpen()) {
    socket->write(data.data(), len);
    socket->flush();
    qDebug() << "Data written";
  } else {
    qDebug() << "Socket closed - Cant send data";
  }
  if (socket->waitForReadyRead()) {
    qDebug() << "Data read";
    return socket->readAll();
  } else {
    qDebug() << "No response";
  }
  return QByteArray();
}

void ClientSocket::close() {
  if (socket->isOpen()) {
    socket->close();
    qDebug() << "Socket closed";
  } else {
    qDebug() << "Socket closed before method call";
  }
}
