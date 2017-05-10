#include "RC4.hpp"

RC4::RC4(unsigned int stateByteSize, unsigned int keyByteSize){

  internalState = new unsigned char [stateByteSize];
  key = new unsigned char [keyByteSize];

  stateSize = stateByteSize;
  keySize = keyByteSize;

}

RC4::~RC4(){
  delete[] internalState;
  delete[] key;
}

void RC4::setKey(unsigned char newKey[], unsigned int size){
  if (size != keySize)
    {fputs ("Keys sizes not equal \n",stderr); exit (1);}

  memcpy(key,newKey,sizeof(key));
}

void RC4::info(){

  for(unsigned int i = 0; i<keySize; ++i){
    std::cout<<key[i];
  }
  printf("\n");
}
