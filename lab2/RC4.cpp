#include "RC4.hpp"

RC4::RC4(unsigned int stateByteSize, unsigned int keyByteSize, unsigned int t){

  internalState = new unsigned char [stateByteSize + 1];//Remember of \0
  key = new unsigned char [keyByteSize + 1];

  stateSize = stateByteSize;
  keySize = keyByteSize;
  T = t;//perms

  keySet = false;
  randomValue = 0;
  iterationOfAlg = 0;

}

RC4::~RC4(){
  delete[] internalState;
  delete[] key;
}

void RC4::setKey(unsigned char newKey[], unsigned int size){
  if (size != keySize + 1)//Remember of \0
    {fputs ("Keys sizes not equal \n",stderr); exit (1);}

  memcpy(key,newKey,sizeof(key));//Remember of \0
  keySet = true;
  iterationOfAlg = 0;
}

void RC4::info(){
    std::cout<<key<<std::endl;
    for(unsigned int i = 0; i<=stateSize; ++i){
      printf("%d",internalState[i]);
    }
}

void RC4::ksaAlg(){
  if(!keySet)
    {fputs ("ksaAlg Key not set \n",stderr); exit (2);}

  unsigned int j = 0;
  unsigned int statePointer, keyPoiter;
  unsigned int stateSwapingSpace, keySwapingSpace, jSwapping;

  stateSwapingSpace = stateSize + 1;
  keySwapingSpace = keySize + 1;

  for( unsigned int i = 0; i <= stateSize; ++i ){
    internalState[i] = i;
  }

  for( unsigned int i = 0; i <= T; ++i){
    statePointer = i % stateSwapingSpace;
    keyPoiter = i % keySwapingSpace;

    j = (j+ internalState[statePointer + key[keyPoiter]]) % stateSwapingSpace;
    jSwapping = j % stateSwapingSpace;

    internalState[statePointer] = internalState[statePointer] ^ internalState [jSwapping];
    internalState [jSwapping] = internalState[statePointer] ^ internalState [jSwapping];
    internalState[statePointer] = internalState[statePointer] ^ internalState [jSwapping];

  }
}

void RC4::prgaAlg(unsigned int generatingOut){
    unsigned int i = 0, j = 0, stateSwapingSpace;

    stateSwapingSpace = stateSize + 1;

    for (unsigned int x = 0; x < generatingOut; ++x){
      i = (i + 1) % stateSwapingSpace;
      j = (j + internalState[i]) % stateSwapingSpace;

      internalState[i] = internalState[i] ^ internalState[j];
      internalState[j] = internalState[i] ^ internalState[j];
      internalState[i] = internalState[i] ^ internalState[j];

      randomValue = internalState[(internalState[i] + internalState[j]) % stateSwapingSpace];
    }
}

unsigned char RC4::getTrueRandom(){
  int randomData = open("/dev/random", O_RDONLY);
  unsigned char randValue[1];
  size_t randomDataLen = 0;
  size_t size = 1;
  while (randomDataLen < size)
  {
      ssize_t result = read(randomData, randValue, size - randomDataLen);
      if (result < 0)
      {
        fputs ("Unable to read dev/random\n",stderr); exit (2);
      }
      randomDataLen += result;
    }
    close(randomData);

    return randValue[0];
}


void RC4::generateKey(){
  unsigned int seed = getTrueRandom();
  printf("\nSeed debug : %d \n", seed);

  srand(seed);
  for(unsigned int i = 0; i <= keySize; ++i){
    key[i] = rand();
  }
  keySet = true;
}

unsigned char RC4::getRandom(unsigned int iterationsOfPRNG){
  if(!keySet){
    printf ("getRandom Key insnt set, \n Generating key...");
    generateKey();
  }
  if (iterationOfAlg == 0){
    ksaAlg();
    //info();
  }
  iterationOfAlg++;
  prgaAlg(stateSize);

  return randomValue;
}
