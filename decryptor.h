#pragma once
#include <QDebug>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/evperr.h>
class Decryptor {
public:
  Decryptor();
  char *decrypt(const unsigned char *input, int &len);
};
