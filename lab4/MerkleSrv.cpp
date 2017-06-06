#include "MerkleSrv.hpp"

MerkleSrv::MerkleSrv(){
  n = 24;
  puzzleSize = pow (2,n);
  keysSize = 128;
  brokenCryptoKeySize = 20;

}

MerkleSrv::MerkleSrv(unsigned int sysPow, unsigned int keyS, unsigned int brokenKeyS){
  if (sysPow > 28)
    n = 28;
  else
    n = sysPow;

  puzzleSize = pow (2,n);
  if (keyS > 256)
    keysSize = 256;
  else
  keysSize = keyS;

  if (brokenKeyS > 128)
    brokenCryptoKeySize = 128;
  else
    brokenCryptoKeySize = brokenKeyS;
  makePerm();
  makeKeys();
}


void MerkleSrv::makePerm(){
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<uint> dis(0x0, 0xFFFFFFFF);

  unsigned long long int j = 0;
  unsigned long long int statePointer;

  for( uint i = 0; i < puzzleSize; ++i ){
    valKeyPosPerm.push_back(i);
  }

  for( unsigned long long int i = 0; i <= puzzleSize*2; ++i){
    statePointer = i % puzzleSize;
    j = (j+ valKeyPosPerm[statePointer] + dis(gen)) % puzzleSize;
    iter_swap(valKeyPosPerm.begin() + statePointer, valKeyPosPerm.begin() + j);

  }

}

void MerkleSrv::makeKeys(){
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<uint> dis(0x0, pow(2,keysSize));

  for( uint i = 0; i < puzzleSize; ++i ){
    valKeyMap.insert(std::pair<uint,uint>(i,dis(gen)));
  }

  for(uint i = 0; i < puzzleSize; ++i){
    std::cout<<valKeyMap[i]<<std::endl;
  }
  std::cout<<"\n"<<pow(2,keysSize/8)<<"\n"<<std::endl;
  for(uint i = 0; i < puzzleSize; ++i){
    std::cout<<valKeyMap[valKeyPosPerm[i]]<<std::endl;
  }
}
