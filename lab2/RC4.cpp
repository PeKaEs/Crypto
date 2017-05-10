#include "RC4.hpp"

RC4::RC4(unsigned int stateByteSize, unsigned int keyByteSize, unsigned int t){

  internalState = new unsigned char [stateByteSize + 1];//Remember of \0
  key = new unsigned char [keyByteSize + 1];

  stateSize = stateByteSize;
  keySize = keyByteSize;
  T = t;//perms

  keySet = false;

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
}

void RC4::info(){
    std::cout<<key<<std::endl;
}

void RC4::ksaAlg(){
  if(!keySet)
    {fputs ("ksaAlg Key not set \n",stderr); exit (2);}

  unsigned int j = 0;
  unsigned int statePointer, keyPoiter;
  unsigned int stateSwapingSpace, keySwapingSpace, jSwapping;

  stateSwapingSpace = stateSize + 1;
  keySwapingSpace = keySize + 1;

  for( unsigned int i = 0; i < stateSize; ++i ){
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
