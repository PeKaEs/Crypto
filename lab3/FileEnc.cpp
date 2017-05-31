#include "FileEnc.hpp"

FileEnc::FileEnc(){
  encMode = keystorePath = keyIdentifier = specMode ="";
  pFileToEncrypt = pEncrypted = pMessesageList = NULL;
  aesOperation = AES_ENCRYPT;
  indata_size = outdata_size = 0;
  numberOfMessesages = 0;
}

void FileEnc::set_encMode(string enc){
  encMode = enc;
}
void FileEnc::set_keystorePath(string keyS){
  keystorePath = keyS;
}
void FileEnc::set_keyIdentifier(string keyI){
  keyIdentifier = keyI;
}
void FileEnc::set_specMode(string spec){
  specMode = spec;
  if(spec == "dec")
    aesOperation = AES_DECRYPT;
}

void FileEnc::set_filePath(string file){
  filePath = file;
}

void FileEnc::set_keyStorePassword(string pass){
  keyStorePass = pass;
}

void FileEnc::debugInfo(){
  printf(" filePath: %s\n encMode: %s\n keystorePath: %s\n keyIdentifier: %s\n specMode: %s\n",filePath.c_str(),encMode.c_str(),
  keystorePath.c_str(),keyIdentifier.c_str(),specMode.c_str() );
}

void FileEnc::run(){
  if(specMode != "eOr" or specMode != "ch" or specMode != "eOrIV"){
      normalRun();
      return;
    }
  else{
      if(specMode == "eOr" or specMode == "eOr"){
        eOracleRun();
      }else{
        challengeRun();
      }
    }
  }


void FileEnc::normalRun(){
  openFiles();
  menageIvs();
  setBuffs();
  set_encryption_key();
  encryptFile();

  deleteBuffs();
  closeFiles();
  reset();
}

void FileEnc::eOracleRun(){
  pMessesageList = fopen(filePath.c_str(), "r");
    if(pMessesageList == NULL){fputs ("Cannot open Messesage list file\n",stderr); exit (303);}

  while(getNextMesessageFile()){
    normalRun();
  }

  fclose(pMessesageList);
  pMessesageList = NULL;
}
void FileEnc::challengeRun(){
  pMessesageList = fopen(filePath.c_str(), "r");
    if(pMessesageList == NULL){fputs ("Cannot open Messesage list file\n",stderr); exit (303);}

  getTrueRandom();
  char randomBit = ivec[0] & 0x01;

  for(char i = 0x00 ; i <= randomBit ; ++i){
    if (!getNextMesessageFile()){fputs ("Not enough messesages\n",stderr); exit (101);}
  }

   fclose(pMessesageList);
   pMessesageList = NULL;
   normalRun();

}

bool FileEnc::getNextMesessageFile(){
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  if (pMessesageList){
    while ((read = getline(&line, &len, pMessesageList)) != -1);

    if (line){
      free(line);
      filePath = string(line);
      return true;
    }
    return false;

  }else{fputs ("Cannot read from Messesage list file\n",stderr); exit (202);}
}

void FileEnc::getTrueRandom(){
  int randomData = open("/dev/random", O_RDONLY);
  size_t randomDataLen = 0;
  size_t size = sizeof(ivec);
  while (randomDataLen < size)
  {
      ssize_t result = read(randomData, ivec + randomDataLen, size - randomDataLen);
      if (result < 0)
      {
        fputs ("Unable to read dev/random\n",stderr); exit (5);
      }
      randomDataLen += result;
    }
    close(randomData);
}

long FileEnc::get_file_length( FILE *file ) {
    fpos_t position;
    long length;
    long prevPos = ftell( file );

    fgetpos( file, &position );

    if ( fseek( file, 0, SEEK_END )
        || ( length = ftell( file ) ) == -1 ) {
        perror( "Finding file length" );
    }

    fsetpos( file, &position );
    length -= prevPos;

    return length;
}

  void FileEnc::set_encryption_key(){

    unsigned char *ckey;

    keyStore.UnlockComponent("30 dniowy trial o.O");
    bool success = keyStore.LoadFile(keyStorePass.c_str(),keystorePath.c_str());
    if (success != true)
      {fputs (keyStore.lastErrorText(),stderr); exit (2);}

    int numSecretKeys = keyStore.get_NumSecretKeys();
    for (int i = 0 ; i< numSecretKeys ; ++i){
      if(keyStore.getSecretKeyAlias(i) == keyIdentifier){
         ckey = (unsigned char *)keyStore.getSecretKey(keyStorePass.c_str(),i,"ascii");
         AES_set_encrypt_key(ckey, 128, &encKey);
         return;
      }
    }
    fputs ("There is no key with that indentifier\n",stderr);
    exit (2);
  }

void FileEnc::openFiles(){

  string encryptedFilePath;

  if(specMode == "ch")
    encryptedFilePath = "encryptedChallenge";
  else
    encryptedFilePath = filePath;

  pEncrypted = fopen((encryptedFilePath+".en").c_str(), "ab");
      if (pEncrypted == NULL) {fputs ("Encrypted file fault, check path\n",stderr); exit (1);}

  pFileToEncrypt = fopen ( filePath.c_str() , "rb" );
      if (pFileToEncrypt == NULL) {fputs ("File to encrypt fault, check path\n",stderr); exit (1);}
  }

void FileEnc::menageIvs(){
  int bytes_read, bytes_written;

  if(aesOperation == AES_DECRYPT){
    bytes_read = fread(ivec, 1, sizeof(ivec), pFileToEncrypt);
    if( bytes_read < 16 ) {fputs ("No IV in file\n",stderr); exit (6);}
    printf("Dec %s\n",ivec );
    indata_size = outdata_size = get_file_length( pFileToEncrypt );

  } else if (aesOperation == AES_ENCRYPT ){
    getTrueRandom();
    bytes_written = fwrite(ivec, 1, sizeof(ivec), pEncrypted);
    if( bytes_written < 16 ) {fputs ("Cannot store IV in file\n",stderr); exit (7);}
    printf("Enc %s\n",ivec );
    indata_size = outdata_size = get_file_length( pFileToEncrypt );
  }
  }

void FileEnc::reset(){
  encMode = keystorePath = keyIdentifier = specMode ="";
  pFileToEncrypt = pEncrypted = NULL;
  aesOperation = AES_ENCRYPT;
  indata_size = outdata_size = 0;
}

void FileEnc::setBuffs(){
  if(indata_size && outdata_size){
    indata = new unsigned char[indata_size];
    outdata = new unsigned char[outdata_size];
  }else{
    fputs ("Cannot allocate memory\n",stderr); exit (8);
  }
}
void FileEnc::deleteBuffs(){
  delete indata;
  delete outdata;
}

void FileEnc::closeFiles(){
  if(pFileToEncrypt && pEncrypted){
    fclose(pFileToEncrypt);
    fclose(pEncrypted);
  }else{
    if(pFileToEncrypt){fclose(pFileToEncrypt);}
    if(pEncrypted){fclose(pEncrypted);}
    fputs ("Cannot close at least one file NULL pointer exception\n",stderr); exit (9);
  }
}

void FileEnc::encryptFile(){
  int num = 0;

  if (fread(indata, 1, indata_size, pFileToEncrypt)){

    if (encMode == "cfb"){
      AES_cfb128_encrypt(indata, outdata, indata_size, &encKey, ivec, &num, aesOperation);
    }else if (encMode == "cbc"){
      AES_cbc_encrypt(indata, outdata, indata_size, &encKey, ivec, aesOperation);
    }else if (encMode =="ofb"){
      AES_ofb128_encrypt(indata, outdata, indata_size, &encKey, ivec, &num);
    }else{
      fputs ("Unsuported mode of encryption\n",stderr); exit (6);
    }
    if(!fwrite(outdata, 1, outdata_size, pEncrypted)){
        fputs ("Writing error",stderr); exit (5);
    }
  }

}
