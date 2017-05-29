#ifndef FileEnc_hpp
#define FileEnc_hpp

/*
keytool -keystore legitKeyStore -genkey -alias client  GENERATING LEGIT KEYSTORE
keytool -genseckey -alias first -keyalg AES -keysize 128 -storetype jceks -keystore legitKeyStore GENERATING AND ADDING KEY
./encode -f filetoencrypt -p tracer10 -c legitKeyStore -k first -m ofb LAUNCH
g++ -g -Wall  main.cpp FileEnc.cpp -L/home/ghost/Pobrane/chilkat-9.5.0-x86_64-linux-gcc/lib -I/home/ghost/Pobrane/chilkat-9.5.0-x86_64-linux-gcc/include -lssl -lcrypto -lchilkat-9.5.0 -o encode COMPILING

*/

#include <string>
#include <stdio.h>
#include <openssl/aes.h>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <CkJavaKeyStore.h>
#include <iostream>

using namespace std;

class FileEnc{

  string encMode;
  string keystorePath;
  string keyIdentifier;
  string specMode;
  string filePath;
  string keyStorePass;
  int aesOperation;

  AES_KEY encKey;
  CkJavaKeyStore keyStore;

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
  void set_keyStorePassword(string pass);
  void run();
  void reset();

  void debugInfo();
};

#endif
