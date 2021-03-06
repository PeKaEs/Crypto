#ifndef MerkleCli_hpp
#define MerkleCli_hpp

#include <iostream>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <vector>
#include <map>
#include <openssl/aes.h>
#include <string.h>

class MerkleCli{

std::random_device rd;  //Will be used to obtain a seed for the random number engine

uint uPreamble[5]; //{n, brokenCryptoKeySize, keysSize, IDsize, constValue};
uint chosenKey;
uint bytesBuffSize;
uint ID;
bool keyCracked, keyChosen;

unsigned char* currKey;
unsigned char* buffer;

FILE* puzzleFile;

void prepareBuffs();
void chooseKey();
void getChosenBuff();
void bruteforceKey();

public:

MerkleCli();
MerkleCli(std::string fileName);
~MerkleCli();

void run();
void info();
std::vector<unsigned char>getKey();
uint getChosenKeyID();

};

#endif
