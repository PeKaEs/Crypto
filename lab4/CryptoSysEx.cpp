#include "MerkleCli.hpp"
#include "MerkleSrv.hpp"

#include <random>
#include <iostream>

int main(void){

  MerkleSrv MerkleServerSide(3, 128, 32, "exchange");//max n = 28
  //MerkleCli MerkleClientSide;

}
