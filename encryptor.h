#pragma once

#include <openssl/evp.h>
using namespace std;
class Encryptor {
public:
  Encryptor();
  unsigned char *encrypt(const char *input, int &len);
};
