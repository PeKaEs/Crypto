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

unsigned long long int uint_pow(uint base, uint exp)
{
    unsigned long long int result = 1;
    while (exp)
    {
        if (exp & 1){
           result *= (unsigned long long int)base;
std::cout<<std::dec<<exp<<std::endl;
}
        exp /= 2;
        base *= base;
    }
    return result;
}

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

  //for(uint i = 0; i<bytesBuffSize ; ++i){
    //std::cout<<std::hex<<buffer[i];
  //}
  //std::cout<<""<<std::endl;
}

void  MerkleCli::bruteforceKey(){
    unsigned char endConstVal[4];
    unsigned char ivec[16], tmpIV[16], brokenKey[16] = {0};
    unsigned char* tempBuff = new unsigned char [bytesBuffSize-16];
    unsigned char* encryptedPair = new unsigned char [bytesBuffSize-16];
    bool decrypted = false;
    AES_KEY encKey;
    int num = 0;
    uint perc = 0;
    unsigned long long int sizeOfKeySpace = uint_pow(2,uPreamble[1]);

    memcpy(ivec,buffer,sizeof(ivec));
    memcpy(tmpIV ,ivec,sizeof(ivec));
    memcpy( encryptedPair, buffer+16,bytesBuffSize-16 );

    for(uint i = 0; i < 4; ++i){
      endConstVal[i] = (uPreamble[4] >> (24-( i*8 ))) & 0xFF;
    }
unsigned long long int end = 4294967296;
    for(unsigned long long int i=0 ; i < pow(2,uPreamble[1]); ++i){

        for( uint j = 15 ; j > 15 - (uPreamble[1]/8) ; --j ){
          brokenKey[j] = (i >> (j * 8)) & 0xFF;
          }


      AES_set_encrypt_key(brokenKey, 128, &encKey);

      AES_cfb128_encrypt(encryptedPair, tempBuff, bytesBuffSize-16, &encKey, tmpIV, &num, AES_DECRYPT);

      for (uint j =  0; j < 4; ++j){

        if (tempBuff[j+(bytesBuffSize-16-4)] != endConstVal[j])
            break;
        if (j == 3)
            decrypted = true;
      }


      memcpy(tmpIV ,ivec,sizeof(tmpIV));
      num = 0;

      if(i%(end/100) == 0)
        std::cout<<i%(end/10)<<"%"<<std::endl;


      if ( decrypted ){
        for(uint j = 0; j<bytesBuffSize-16; ++j){
          std::cout<<tempBuff[j];
        }
          break;
      }

    }

    delete tempBuff;
    delete encryptedPair;

}

void MerkleCli::run(){
  prepareBuffs();
  chooseKey();
  getChosenBuff();
  bruteforceKey();
}
