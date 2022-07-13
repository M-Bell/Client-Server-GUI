#include "packetutil.h"
#include "crc16.h"
#include "decryptor.h"
#include "encryptor.h"
#include <QDataStream>

PacketUtil::PacketUtil() {}

QByteArray PacketUtil::generatePacket(char clientId, long packetId,
                                      int commandCode, int userId,
                                      const QByteArray message, int &outLen) {

  int wLen = message.length() + 8;
  char header[14];
  char messageBytes[wLen];

  header[0] = 0x13;
  header[1] = clientId;
  for (int i = 0; i < 8; ++i) {
    header[2 + i] = (char)(packetId >> (8 * (7 - i))) & 255;
  }

  for (int i = 0; i < 4; ++i) {
    header[10 + i] = (wLen >> (8 * (3 - i))) & 255;
  }
  short crc16 = CRC16::getCRC16(header, 14);
  for (int i = 0; i < 4; ++i) {
    messageBytes[0 + i] = (commandCode >> (8 * (3 - i))) & 255;
  }
  for (int i = 0; i < 4; ++i) {
    messageBytes[4 + i] = (userId >> (8 * (3 - i))) & 255;
  }
  for (int i = 0; i < wLen - 8; ++i) {
    messageBytes[8 + i] = message[i];
  }
  int msgLen = wLen - 8;
  short crc16MSG = CRC16::getCRC16(messageBytes, wLen);
  Encryptor enc;
  unsigned char *encodedMessage = enc.encrypt(message, msgLen);
  wLen = msgLen + 8;
  for (int i = 0; i < 4; ++i) {
    header[10 + i] = (wLen >> (8 * (3 - i))) & 255;
  }
  char encodedMessageBytes[wLen];
  for (int i = 0; i < 8; ++i) {
    encodedMessageBytes[i] = messageBytes[i];
  }
  for (int i = 0; i < wLen - 8; ++i) {
    encodedMessageBytes[8 + i] = encodedMessage[i];
  }
  outLen = 18 + wLen;
  QByteArray result;

  for (int i = 0; i < 14; ++i) {
    result.append(header[i]);
  }
  for (int i = 0; i < 2; ++i) {
    result.append((crc16 >> (8 * (1 - i))) & 255);
  }
  for (int i = 0; i < wLen; ++i) {
    result.append(encodedMessageBytes[i]);
  }
  for (int i = 0; i < 2; ++i) {
    result.append((crc16MSG >> (8 * (1 - i))) & 255);
  }

  return result;
}

Packet PacketUtil::receivePacket(const QByteArray input) {
  if (input.size() == 0)
    return {};
  Packet result;
  Decryptor dec;
  result.bMagic = input.at(0);
  result.bSrc = input.at(1);
  result.bPktId = getLongFromBytes(input.sliced(2, 8));
  result.wLen = getIntFromBytes(input.sliced(10, 4));
  result.wCrc16 = getShortFromBytes(input.sliced(14, 2));
  result.cType = getIntFromBytes(input.sliced(16, 4));
  result.bUserId = getIntFromBytes(input.sliced(20, 4));
  result.wMsgCrc16 = getShortFromBytes(input.sliced(16 + result.wLen, 2));
  int newLen = result.wLen - 8;
  result.message = dec.decrypt(
      (unsigned char *)input.sliced(24, result.wLen - 8).data(), newLen);
  result.wLen = newLen;
  result.message = result.message.sliced(0, result.wLen);
  return result;
}
