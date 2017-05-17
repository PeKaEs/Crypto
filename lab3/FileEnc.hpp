#ifndef FileEnc_hpp
#define FileEnc_hpp

#include <string>
#include <stdio.h>
#include <openssl/aes.h>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <CkJavaKeyStore.h>

using namespace std;

class FileEnc{

  string encMode;
  string keystorePath;
  string keyIdentifier;
  string specMode;
  string filePath;
  int aesOperation;

  AES_KEY encKey;

  FILE *pKeystoreFile, *pFileToEncrypt, *pEncrypted;

  unsigned char *indata,*outdata;
  long indata_size, outdata_size;

  unsigned char ivec[16];

  void encryptFile();
  long get_file_length( FILE *file );
  void set_encryption_key();
  void getTrueRandom();
  void openFiles();
  void closeFiles();
  void menageIvs();
  void setBuffs();
  void deleteBuffs();


public:
  FileEnc();
  void set_encMode(string enc);
  void set_keystorePath(string keyS);
  void set_keyIdentifier(string keyI);
  void set_specMode(string spec);
  void set_filePath(string file);
  void run();
  void reset();

  void debugInfo();
};

#endif
