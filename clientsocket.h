#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QDebug>
#include <QObject>
#include <QTcpSocket>

class ClientSocket : public QObject {
  Q_OBJECT
public:
  explicit ClientSocket(QObject *parent = nullptr);
  ~ClientSocket() { delete socket; }
  QByteArray sendData(const QByteArray data, const int len);
  void connect();
  void close();
signals:

private:
  QTcpSocket *socket;
};

#endif // CLIENTSOCKET_H
