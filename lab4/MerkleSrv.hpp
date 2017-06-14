#ifndef MerkleSrv_hpp
#define MerkleSrv_hpp

#include <iostream>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <vector>
#include <map>
#include <openssl/aes.h>
#include <string.h>

class MerkleSrv{

unsigned int n;
unsigned int keysSize;
unsigned int brokenCryptoKeySize;
uint puzzleSize;
bool keysGenerated;

std::vector <uint> valKeyPosPerm;
std::map <uint,std::vector<unsigned char>> valKeyMap;

std::random_device rd;  //Will be used to obtain a seed for the random number engine

const uint constValue = 0xFEEDFACE ;
unsigned char* finalRow;
std::string filePath;

void makePerm();
void makeKeys();
void constructFinal(uint ID);
void encAndSave();

public:
  MerkleSrv();
  ~MerkleSrv();
  MerkleSrv(unsigned int sysPow, unsigned int keyS, unsigned int brokenKeyS, std::string fPath);
  void generatePuzzle();
  std::vector<unsigned char> getKey(uint ID);
};

#endif
