#pragma once
#include <QByteArray>
struct Packet {
  char bMagic;
  char bSrc;
  long bPktId;
  int wLen;
  short wCrc16;
  int cType;
  int bUserId;
  QByteArray message;
  short wMsgCrc16;
};
