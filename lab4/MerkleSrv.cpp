#include "MerkleSrv.hpp"

MerkleSrv::MerkleSrv(){
  n = 24;
  puzzleSize = pow (2,n);
  keysSize = 128;
  brokenCryptoKeySize = 24;
  finalRow = new unsigned char[(4+ 4+ ( keysSize/8 ))];//IDlenght(byte)+ConstVal(byte)+KeySize(byte)
  filePath = "default";

}

MerkleSrv::MerkleSrv(unsigned int sysPow, unsigned int keyS, unsigned int brokenKeyS, std::string fPath){
  if (sysPow > 28)
    n = 28;
  else
    n = sysPow;

  puzzleSize = pow (2,n);
  if (keyS > 256)
    keysSize = 256;
  else
  keysSize = keyS;

  if (brokenKeyS > 64)
    brokenCryptoKeySize = 64;
  else
    brokenCryptoKeySize = brokenKeyS;

  filePath = fPath;
  finalRow = new unsigned char[(4+ 4+ ( keysSize/8 ))];

  makePerm();
  makeKeys();
  encAndSave();
}

MerkleSrv::~MerkleSrv(){
  delete finalRow;
}

void MerkleSrv::constructFinal(uint ID){

  for(uint i = 4; i<(keysSize/8)+4; ++i){
    finalRow[i] = valKeyMap[ID][i-4];
  }

  for(uint i = 0; i < 4; ++i){
    finalRow[(keysSize/8)+4+i] = (constValue >> (24-( i*8 ))) & 0xFF;
    finalRow[i] = (ID >> (24-( i*8 ))) & 0xFF;
  }

}

void MerkleSrv::encAndSave(){
  int num = 0;
  AES_KEY encKey;
  FILE* pEnc;
  unsigned char ivec[16];
  unsigned char* ckey = new unsigned char[brokenCryptoKeySize/8];

  std::mt19937_64 genIV(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<unsigned long long int> disIV(0x0, 0xFFFFFFFFFFFFFFFF);

  unsigned long long int a = disIV(genIV);
  unsigned long long int b = disIV(genIV)

  memcpy(ivec ,&a,sizeof(a));
  memcpy(ivec+sizeof(b) ,&b,sizeof(b));//if a = 0xA00000000000000B; and  b = 0xC00000000000000D; then ivec = 0B 00 00 00 00 00 00 A0 0D 00 00 00 00 00 00 C0

  std::mt19937_64 genKey(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<unsigned char> disKey(0x0, 0xFF);

  for( uint i = 0 ; i < (brokenCryptoKeySize/8) ; ++i ){
    ckey[i] = disKey(genKey);
  }



  pEnc = fopen(filePath.c_str(), "ab");
      if (pEnc == NULL) {fputs ("Exange file fault, check path\n",stderr); exit (1);}

  //for(uint i = 0; i < puzzleSize; ++i){
  //constructFinal(i);

  if(!fwrite(ivec, 1, sizeof(ivec), pEnc)){
      fputs ("Writing error",stderr); exit (5);}
  //}
  //}
/*
  AES_set_encrypt_key(ckey, brokenCryptoKeySize, &encKey);

  constructFinal(uint ID);
  AES_cfb128_encrypt(finalRow, finalRow, (4+ 4+ ( keysSize/8 )), &encKey, ivec, &num, AES_ENCRYPT);

  memcpy(ivec ,preIV.c_str(),sizeof(ivec));
*/
  delete ckey;
  fclose(pEnc);
}

void MerkleSrv::makePerm(){
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<uint> dis(0x0, 0xFFFFFFFF);

  uint j = 0;
  uint statePointer;

  for( uint i = 0; i < puzzleSize; ++i ){
    valKeyPosPerm.push_back(i);
  }

  for( unsigned long int i = 0; i <= puzzleSize*2; ++i){
    statePointer = i % puzzleSize;
    j = (j+ valKeyPosPerm[statePointer] + dis(gen)) % puzzleSize;
    iter_swap(valKeyPosPerm.begin() + statePointer, valKeyPosPerm.begin() + j);

  }

}

void MerkleSrv::makeKeys(){
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<unsigned char> dis(0x0, 0xFF);

  for( uint i = 0; i < puzzleSize; ++i ){

    //valKeyMap.insert(std::pair<uint,std::vector<unsigned char>>(i,dis(gen)));
    if ( (keysSize/8) * i > 300 )
      gen.seed(rd());

    //if(i%(puzzleSize/10) == 0)
      //std::cout<<i<<std::endl;

    valKeyMap.insert( std::pair< uint, std::vector<unsigned char> > ( i, std::vector<unsigned char>() ) );
    for ( uint j = 0; j < keysSize/8; ++j )
        valKeyMap[i].push_back( dis(gen) );
  }
/*
  for(uint i = 0; i < puzzleSize; ++i){

    for ( uint j = 0; j < keysSize/8; ++j )
      std::cout<<valKeyMap[i][j];

    std::cout<<""<<std::endl;
  }

  std::cout<<"\n"<<valKeyMap[1].size()<<"\n"<<std::endl;

  for(uint i = 0; i < puzzleSize; ++i){

    for ( uint j = 0; j < keysSize/8; ++j )
        std::cout<<valKeyMap[valKeyPosPerm[i]][j];

    std::cout<<""<<std::endl;
  }
  */
}
