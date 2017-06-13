#include "MerkleCli.hpp"

/*
Preamble reading
temp[0] - > N
temp[1] - > Broken Key Size [bits]
temp[2] - > Keys Size [bits]
temp[3] - > ID size [Bytes]
temp[4] - > Const Value

FILE *pEncRead = fopen(filePath.c_str(), "rb");
    if (pEnc == NULL) {fputs ("Exange file fault, check path\n",stderr); exit (1);}
uint temp[5];

  fread(&temp, sizeof(uint), 5, pEncRead);
for(uint i = 0; i < 5 ; ++i){
  std::cout<<temp[i]<<std::endl;
}

Decrypt:

AES_set_encrypt_key(ckey, 128, &encKey);
num = 0;

AES_cfb128_encrypt(toSave, finalRow, (4+ 4+ ( keysSize/8 )), &encKey, ivectest, &num, AES_DECRYPT);

if(!fwrite(finalRow, 1, (4+ 4+ ( keysSize/8 )), pEnc)){
    fputs ("Writing error",stderr); exit (5);}

*/

MerkleCli::MerkleCli(){
  puzzleFile = fopen("default", "rb");
      if (puzzleFile == NULL) {fputs ("Exange file fault, check path\n",stderr); exit (1);}

  prepareBuffs();
}

MerkleCli::MerkleCli(std::string fileName){
  puzzleFile = fopen(fileName.c_str(), "rb");
      if (puzzleFile == NULL) {fputs ("Exange file fault, check path\n",stderr); exit (1);}

}

MerkleCli::~MerkleCli(){
    delete currKey;
    delete buffer;
}

void MerkleCli::info(){
  std::vector<std::string> preambleLabels = {"Exponent : ", "Broken Crypto Key Size [bits] : ", "Keys Sizes [bits] : ", "ID Size [bytes] : ", "Const Value : "};

  for(uint i = 0; i < 5 ; ++i){
      std::cout<<preambleLabels[i];
      std::cout<< std::hex <<"0x"<<uPreamble[i]<<std::endl;
    }
}

void MerkleCli::prepareBuffs(){
  size_t n0OfVal = 0;

  n0OfVal = fread(&uPreamble, sizeof(uint), 5, puzzleFile);
      if (n0OfVal < 5){fputs ("Not enough data to read\n",stderr); exit (2);}

  bytesBuffSize = (16 + uPreamble[3]+ sizeof(uPreamble[4])+ ( uPreamble[2]/8 ));

  currKey = new unsigned char[ uPreamble[2]/8 ];
  buffer = new unsigned char[ bytesBuffSize ];// IVSize + IDSize + ConstValueSize + keySize

  info();
}

void MerkleCli::chooseKey(){
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<uint> dis(0x0, pow(2,uPreamble[0]));

  chosenKey = dis(gen);
}

void MerkleCli::getChosenBuff(){
  size_t n0OfVal = 0;
  fseek(puzzleFile, (long)(chosenKey * bytesBuffSize), SEEK_CUR);

  n0OfVal = fread(buffer, 1, bytesBuffSize, puzzleFile);
      if (n0OfVal < bytesBuffSize){fputs ("Not enough key data to read\n",stderr); exit (2);}

  for(uint i = 0; i < bytesBuffSize ; ++i){
    std::cout<<std::hex<<(uint)buffer[i];
  }

}

void MerkleCli::run(){
  prepareBuffs();
  chooseKey();
  getChosenBuff();
}
