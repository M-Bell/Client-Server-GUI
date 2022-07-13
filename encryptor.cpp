#include "encryptor.h"
#include <QDebug>

Encryptor::Encryptor() {}

unsigned char *Encryptor::encrypt(const char *input, int &len) {
  int out = 0;
  int out2 = 0;
  unsigned char *inD = (unsigned char *)input;
  unsigned char *outD = new unsigned char[len * 2];
  unsigned char ckey[] = "1234567898765432";
  unsigned char ivec[] = "";

  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

  if (!EVP_EncryptInit(ctx, EVP_aes_128_ecb(), ckey, ivec)) {
    qDebug() << "Init error";
    //    qDebug() << "EVP_DecryptInit() error: "
    //              << ERR_error_string(ERR_get_error(), NULL);
  }

  if (!EVP_EncryptUpdate(ctx, outD, &out, inD, len)) {
    qDebug() << "Encrypt Update";

    //    std::cout << "EVP_DecryptUpdate() error: "
    //              << ERR_error_string(ERR_get_error(), NULL);
  }

  if (!EVP_EncryptFinal(ctx, outD + out, &out2)) {
    qDebug() << "Encrypt Final";

    //    std::cout << "EVP_DecryptFinal() error: "
    //              << ERR_error_string(ERR_get_error(), NULL);
  }

  EVP_CIPHER_CTX_flags(ctx);
  len = out + out2;
  unsigned char *encryptedData = new unsigned char[len];
  for (int i = 0; i < out + out2; ++i) {
    encryptedData[i] = outD[i];
  }
  return encryptedData;
}
