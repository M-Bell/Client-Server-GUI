#include "decryptor.h"

Decryptor::Decryptor() {}

char *Decryptor::decrypt(const unsigned char *input, int &len) {
  int out = 0;
  int out2 = 0;
  unsigned char *outD = new unsigned char[len * 2];
  unsigned char ckey[] = "1234567898765432";

  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

  if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, ckey, NULL)) {
    qDebug() << "Init error";
    //    qDebug() << "EVP_DecryptInit() error: "
    //              << ERR_error_string(ERR_get_error(), NULL);
  }

  if (!EVP_DecryptUpdate(ctx, outD, &out, input, len)) {
    qDebug() << "Decrypt Update";

    //    std::cout << "EVP_DecryptUpdate() error: "
    //              << ERR_error_string(ERR_get_error(), NULL);
  }

  if (!EVP_DecryptFinal_ex(ctx, outD + out, &out2)) {
    qDebug() << "EVP_DecryptFinal() error: "
             << ERR_error_string(ERR_get_error(), NULL);
  }

  EVP_CIPHER_CTX_free(ctx);

  len = out + out2;
  char *decryptedData = new char[out + out2];
  for (int i = 0; i < len; ++i) {
    decryptedData[i] = outD[i];
  }
  return decryptedData;
}
