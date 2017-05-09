#ifndef FileEnc_hpp
#define FileEnc_hpp

#include <string>
#include <stdio.h>
#include <openssl/aes.h>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class FileEnc{

  string encMode;
  string keystorePath;
  string keyIdentifier;
  string specMode;
  string filePath;

  AES_KEY encKey;

  FILE *pKeystoreFile, *pFileToEncrypt, *pEncrypted;

  unsigned char ivec[16];

  void encryptFile(int encMode);
  long get_file_length( FILE *file );
  void set_encryption_key();
  void getTrueRandom();


public:
  FileEnc();
  void set_encMode(string enc);
  void set_keystorePath(string keyS);
  void set_keyIdentifier(string keyI);
  void set_specMode(string spec);
  void set_filePath(string file);
  void run();

  void debugInfo();
};

#endif
