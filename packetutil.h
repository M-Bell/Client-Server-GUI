#pragma once
#include "packet.h"
#include <QByteArray>
#include <cstring>
class PacketUtil {
public:
  PacketUtil();
  static QByteArray generatePacket(char clientId, long packetId,
                                   int commandCode, int userId,
                                   const QByteArray message, int &outLen);
  static Packet receivePacket(const QByteArray input);

private:
  inline static long getLongFromBytes(const QByteArray arr) {
    return ((qlonglong(arr.at(0)) << 56) & 0xFF00000000000000) |
           ((qlonglong(arr.at(1)) << 48) & 0x00FF000000000000) |
           ((qlonglong(arr.at(2)) << 40) & 0x0000FF0000000000) |
           ((qlonglong(arr.at(3)) << 32) & 0x000000FF00000000) |
           ((arr.at(4) << 24) & 0x00000000FF000000) |
           ((arr.at(5) << 16) & 0x0000000000FF0000) |
           ((arr.at(6) << 8) & 0x000000000000FF00) |
           ((arr.at(7) << 0) & 0x00000000000000FF);
  }
  inline static int getIntFromBytes(const QByteArray arr) {
    return ((arr.at(0) << 24) & 0xFF000000) | ((arr.at(1) << 16) & 0x00FF0000) |
           ((arr.at(2) << 8) & 0x0000FF00) | ((arr.at(3) << 0) & 0x000000FF);
  }

  inline static short getShortFromBytes(const QByteArray arr) {
    return ((arr.at(0) << 8) & 0xFF00) | ((arr.at(1) << 0) & 0x00FF);
  }
};
