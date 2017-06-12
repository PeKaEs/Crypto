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
