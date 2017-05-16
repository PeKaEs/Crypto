#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "RC4.hpp"


void RC4_NN(){
  uint N[3] = {16, 64, 256};
  uint keyLen[3] = {40, 64, 128};

  std::string filePath = "RC4_NN/RC4_NN_";

  for(uint i = 0; i < 3 ; ++i){
    for(uint j = 0; j < 3; ++j){
      RC4* tests = new RC4(N[i], keyLen[j], N[i], 2500, 0);//(N,keyLen,T,outSize,dropByte)

      tests -> genRandom();
      tests -> saveNumbers((filePath+std::to_string(N[i])+"N_"+std::to_string(N[i])+"T_"+std::to_string(keyLen[j])+"K"));

      delete tests;
    }
  }
}

void RC4_NN_drop(){
  uint N[3] = {16, 64, 256};
  uint keyLen[3] = {40, 64, 128};
  uint K[3] = {2, 4, 8};
  std::string filePath = "RC4_NN_drop/RC4_NN_drop_";

  for(uint i = 0; i < 3 ; ++i){
    for(uint j = 0; j < 3; ++j){
      for(uint k = 0; k < 3; ++k){
        RC4* tests = new RC4(N[i], keyLen[j], N[i], 2500, K[k]*N[i]);//(N,keyLen,T,outSize,dropByte)

        tests -> genRandom();
        tests -> saveNumbers((filePath+std::to_string(N[i])+"N_"+std::to_string(N[i])+
              "T_"+std::to_string(keyLen[j])+"K_"+std::to_string(K[k]*N[i])+"Bdrop"));

        delete tests;
      }
    }
  }
}

void RC4_NkN(){
  uint N[3] = {16, 64, 256};
  uint keyLen[3] = {40, 64, 128};
  uint K[3] = {2, 4, 8};
  std::string filePath = "RC4_kN/RC4_kN_";

  for(uint i = 0; i < 3 ; ++i){
    for(uint j = 0; j < 3; ++j){
      for(uint k = 0; k < 3; ++k){
        RC4* tests = new RC4(N[i], keyLen[j], K[k]*N[i], 2500, 0);//(N,keyLen,T,outSize,dropByte)

        tests -> genRandom();
        tests -> saveNumbers((filePath+std::to_string(N[i])+"N_"+std::to_string(K[k]*N[i])+
              "T_"+std::to_string(keyLen[j])+"K"));

        delete tests;
      }
    }
  }
}

int main(){

  RC4_NN();
  RC4_NN_drop();
  RC4_NkN();
  return 0;
}
