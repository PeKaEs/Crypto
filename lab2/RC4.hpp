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

public:
  RC4(unsigned int stateByteSize, unsigned int keyByteSize);
  virtual ~RC4();
  void setKey(unsigned char newKey[], unsigned int size);
  void info();

};

#endif
