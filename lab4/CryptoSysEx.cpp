#include "MerkleCli.hpp"
#include "MerkleSrv.hpp"

#include <random>
#include <iostream>

int main(void){

  std::vector<unsigned char> chosenKey;
  std::vector<unsigned char> originalKey;

  MerkleSrv MerkleServerSide(4, 128, 8, "exchange3");//max n = 28
  MerkleServerSide.generatePuzzle();

  MerkleCli MerkleClientSide("exchange3");
  MerkleClientSide.run();

  chosenKey = MerkleClientSide.getKey();
  originalKey = MerkleServerSide.getKey(MerkleClientSide.getChosenKeyID());

std::cout<<"Chosen key ID :0x"<<std::hex<<MerkleClientSide.getChosenKeyID()<<"Final extracted key Val (Client) :";

  for (std::vector<unsigned char>::const_iterator i = chosenKey.begin(); i != chosenKey.end(); ++i)
      std::cout<<std::hex<<*i;

  std::cout<<std::endl;

std::cout<<"Original key (Server) :";

  for (std::vector<unsigned char>::const_iterator i = originalKey.begin(); i != originalKey.end(); ++i)
      std::cout<<std::hex<<*i;

  std::cout<<std::endl;

}
