#ifndef RC4_hpp
#define RC4_hpp

#include <stdio.h>
#include <cstdlib>
#include <string.h>

#include <iostream>


class RC4{

  unsigned char *internalState;
  unsigned char *key;

  unsigned int stateSize;
  unsigned int keySize;
  unsigned int T;

  bool keySet;

public:
  RC4(unsigned int stateByteSize, unsigned int keyByteSize, unsigned int t);
  virtual ~RC4();
  void setKey(unsigned char newKey[], unsigned int size);
  void ksaAlg();
  void info();

};

#endif
