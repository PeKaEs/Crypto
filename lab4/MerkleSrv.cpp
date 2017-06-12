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
  //if (keyS > 256)
    //keysSize = 256;
  //else
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
  uint IDsize = 4;
  uint uPreamble[5] = {n, brokenCryptoKeySize, keysSize, IDsize, constValue};
  AES_KEY encKey;
  FILE* pEnc;

  unsigned char ivec[16],ckey[16] = {0};
  unsigned char* toSave = new unsigned char[(uint)(4+ 4+ ( keysSize/8 ))];
  unsigned long long int firIVpart, secIVpart;

  std::mt19937_64 genIV(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::mt19937 genKey(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<unsigned long long int> disIV(0x0, 0xFFFFFFFFFFFFFFFF);
  std::uniform_int_distribution<unsigned char> disKey(0x0, 0xFF);

  pEnc = fopen(filePath.c_str(), "ab");
      if (pEnc == NULL) {fputs ("Exange file fault, check path\n",stderr); exit (1);}

//Preamble
  if(!fwrite(&uPreamble, sizeof(uint), 5, pEnc)){
      fputs ("Writing error",stderr); exit (5);}
//--Preamble

uint perc = 0;

  for(uint i = 0; i < puzzleSize; ++i){

    constructFinal(valKeyPosPerm[i]);

    if ( 2 * i > 300 )  //Prevents prediction of mt19937 values
      genIV.seed(rd());
    if ( (brokenCryptoKeySize/8) * i > 300 )  //Prevents prediction of mt19937 values
      genKey.seed(rd());

    firIVpart = disIV(genIV);
    secIVpart = disIV(genIV);

    memcpy(ivec ,&firIVpart,sizeof(firIVpart));
    memcpy(ivec+sizeof(secIVpart) ,&secIVpart,sizeof(secIVpart));//if a = 0xA00000000000000B; and  b = 0xC00000000000000D; then ivec = 0B 00 00 00 00 00 00 A0 0D 00 00 00 00 00 00 C0

    for( uint i = 15 ; i > 15 - (brokenCryptoKeySize/8) ; --i ){
      ckey[i] = disKey(genKey);
    }

    AES_set_encrypt_key(ckey, 128, &encKey);

    if(!fwrite(ivec, 1, 16, pEnc)){
        fputs ("Writing error",stderr); exit (5);}

    AES_cfb128_encrypt(finalRow, toSave, (4+ 4+ ( keysSize/8 )), &encKey, ivec, &num, AES_ENCRYPT);

    if(!fwrite(toSave, 1, (4+ 4+ ( keysSize/8 )), pEnc)){
        fputs ("Writing error",stderr); exit (5);}

    num = 0;

    if(i%(puzzleSize/10) == 0)
      {std::cout<<"Encrypting/Saving keys: "<<perc<<"%"<<std::endl;perc+=10;}

  }

  delete toSave;
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

uint perc = 0;
  for( uint i = 0; i < puzzleSize; ++i ){

    if ( (keysSize/8) * i > 300 )
      gen.seed(rd());

    if(i%(puzzleSize/10) == 0)
      {std::cout<<"Creating keys: "<<perc<<"%"<<std::endl;perc+=10;}

    valKeyMap.insert( std::pair< uint, std::vector<unsigned char> > ( i, std::vector<unsigned char>() ) );
    for ( uint j = 0; j < keysSize/8; ++j )
        valKeyMap[i].push_back( dis(gen) );
  }
}
