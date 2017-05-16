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

  unsigned char randomValue;

  unsigned int stateSize;
  unsigned int keySize;
  unsigned int T;
  unsigned int iterationOfAlg;

  bool keySet;

  void ksaAlg();
  void prgaAlg(unsigned int generatingOut);
  void generateKey();
  unsigned char getTrueRandom();

public:
  RC4(unsigned int stateByteSize, unsigned int keyByteSize, unsigned int t);
  virtual ~RC4();
  void setKey(unsigned char newKey[], unsigned int size);
  unsigned char getRandom(unsigned int iterationsOfPRNG);
  unsigned char* getKey();
  //void saveNumbers(string filePath);
  void info();

};

#endif
