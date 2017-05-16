#ifndef RC4_hpp
#define RC4_hpp

#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>


class RC4{

  unsigned char *internalState;
  unsigned char *key;
  unsigned char *outputStream;

  unsigned char randomValue;

  uint stateSize;
  uint keySize;
  uint outputStreamSize;
  uint T;
  uint iterationOfAlg;
  uint dropKNbyte;

  bool keySet;

  void ksaAlg();
  void prgaAlg();
  void generateKey();
  unsigned char getTrueRandom();

public:
  RC4(uint stateByteSize, uint keyByteSize, uint t, uint outputSize, uint drop);
  virtual ~RC4();
  void setKey(unsigned char newKey[], uint size);
  void genRandom();
  unsigned char* getKey();
  void saveNumbers(std::string filePath);
  void info();

};

#endif
