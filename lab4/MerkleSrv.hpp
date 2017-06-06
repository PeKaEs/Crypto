#ifndef MerkleSrv_hpp
#define MerkleSrv_hpp

#include <iostream>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <vector>
#include <map>

class MerkleSrv{

unsigned int n;
unsigned int keysSize;
unsigned int brokenCryptoKeySize;
unsigned long long int puzzleSize;

std::vector <uint> valKeyPosPerm;
std::map <uint,uint> valKeyMap;

std::random_device rd;  //Will be used to obtain a seed for the random number engine


void makePerm();
void makeKeys();

public:
  MerkleSrv();
  MerkleSrv(unsigned int sysPow, unsigned int keyS, unsigned int brokenKeyS);
};

#endif
