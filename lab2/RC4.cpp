#include "RC4.hpp"

RC4::RC4(uint stateByteSize, uint keyByteSize, uint t, uint outputSize, uint drop){

  internalState = new unsigned char [stateByteSize + 1];//Remember of \0
  key = new unsigned char [keyByteSize + 1];
  outputStream = new unsigned char [outputSize + 1];

  stateSize = stateByteSize;
  keySize = keyByteSize;
  outputStreamSize = outputSize;
  dropKNbyte = drop;
  T = t;//perms

  keySet = false;
  randomValue = 0;
  iterationOfAlg = 0;

}

RC4::~RC4(){
  delete[] internalState;
  delete[] key;
  delete[] outputStream;
}

void RC4::setKey(unsigned char newKey[], uint size){
  if (size != keySize + 1)//Remember of \0
    {fputs ("Keys sizes not equal \n",stderr); exit (1);}

  memcpy(key,newKey,sizeof(key));//Remember of \0
  keySet = true;
  iterationOfAlg = 0;
}

void RC4::info(){
    std::cout<<outputStream<<std::endl;
}

void RC4::ksaAlg(){
  if(!keySet)
    {fputs ("ksaAlg Key not set \n",stderr); exit (2);}

  uint j = 0;
  uint statePointer, keyPointer;
  uint stateSwapingSpace, keySwapingSpace, jSwapping;

  stateSwapingSpace = stateSize + 1;
  keySwapingSpace = keySize + 1;

  for( uint i = 0; i <= stateSize; ++i ){
    internalState[i] = i;
  }

  for( uint i = 0; i <= T; ++i){
    statePointer = i % stateSwapingSpace;
    keyPointer = i % keySwapingSpace;

    j = (j+ internalState[statePointer] + key[keyPointer]) % stateSwapingSpace;
    jSwapping = j % stateSwapingSpace;

    if (statePointer^jSwapping){
      internalState[statePointer] = internalState[statePointer] ^ internalState [jSwapping];
      internalState [jSwapping] = internalState[statePointer] ^ internalState [jSwapping];
      internalState[statePointer] = internalState[statePointer] ^ internalState [jSwapping];
    }
  }
}

void RC4::prgaAlg(){
    uint i = 0, j = 0, x = 0, dropByte, stateSwapingSpace;

    dropByte = dropKNbyte;
    stateSwapingSpace = stateSize + 1;

    while(x <= outputStreamSize){
      i = (i + 1) % stateSwapingSpace;
      j = (j + internalState[i]) % stateSwapingSpace;

      if (i^j){
        internalState[i] = internalState[i] ^ internalState[j];
        internalState[j] = internalState[i] ^ internalState[j];
        internalState[i] = internalState[i] ^ internalState[j];
      }
      randomValue = internalState[(internalState[i] + internalState[j]) % stateSwapingSpace];

      if(dropByte == 0){
        outputStream[x] = randomValue;
        ++x;
      }else{
        --dropByte;
      }
    }
}

unsigned char RC4::getTrueRandom(){
  int randomData = open("/dev/random", O_RDONLY);
  unsigned char randValue;
  size_t randomDataLen = 0;
  size_t size = 1;
  while (randomDataLen < size)
  {
      ssize_t result = read(randomData, &randValue, size - randomDataLen);
      if (result < 0)
      {
        fputs ("Unable to read dev/random\n",stderr); exit (2);
      }
      randomDataLen += result;
    }
    close(randomData);

    return randValue;
}


void RC4::generateKey(){
  uint seed = getTrueRandom();

  srand(seed);
  for(uint i = 0; i <= keySize; ++i){
    key[i] = rand();
  }
  keySet = true;
}

void RC4::genRandom(){
  if(!keySet){
    printf ("getRandom Key isnt set, \n Generating key...");
    generateKey();
  }
  if (iterationOfAlg == 0){
    ksaAlg();
  }
  iterationOfAlg++;

  prgaAlg();

}

void RC4::saveNumbers(std::string filePath){
 FILE *randFile;

 randFile = fopen((filePath+".bin").c_str(), "wb");
     if (randFile == NULL) {fputs ("randFile file open fault, check path\n",stderr); exit (1);}

 if(!fwrite(outputStream, 1, outputStreamSize + 1, randFile)){
     fputs ("Writing error",stderr); exit (5);}
}
