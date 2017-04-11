#include "FileEnc.hpp"

FileEnc::FileEnc(){
  encMode = keystorePath = keyIdentifier = specMode ="";
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
}

void FileEnc::set_filePath(string file){
  filePath = file;
}

void FileEnc::debugInfo(){
  printf(" filePath: %s\n encMode: %s\n keystorePath: %s\n keyIdentifier: %s\n specMode: %s\n",filePath.c_str(),encMode.c_str(),
  keystorePath.c_str(),keyIdentifier.c_str(),specMode.c_str() );
}

void FileEnc::run(){
  if(specMode != ""){
    if(specMode == "dec")
      encryptFile(AES_DECRYPT);
    return;
  } else {
    encryptFile(AES_ENCRYPT);
    return;
  }


}

unsigned char* getTrueRandom(unsigned char* tmp, size_t size){
  int randomData = open("/dev/random", O_RDONLY);
  size_t randomDataLen = 0;
  while (randomDataLen < size)
  {
      ssize_t result = read(randomData, tmp + randomDataLen, size - randomDataLen);
      if (result < 0)
      {
        fputs ("Unable to read dev/random\n",stderr); exit (5);
      }
      randomDataLen += result;
    }
    close(randomData);
}

void FileEnc::encryptFile(int encMode){
  FILE *pFileToEncrypt, *pKeystoreFile;
  FILE *pEncrypted;
  long keystoreFileSize;
  int iKeyIdentifier = atoi( keyIdentifier.c_str() );
  size_t result;
  int num = 0;

  int bytes_read, bytes_written;
  unsigned char indata[AES_BLOCK_SIZE];
  unsigned char outdata[AES_BLOCK_SIZE];

  unsigned char ckey[] = "dontusethisinput";
  unsigned char ivec[] = "dontusethisinput";

  AES_KEY key;


  pEncrypted = fopen((filePath+".en").c_str(), "ab");

  pFileToEncrypt = fopen ( filePath.c_str() , "rb" );
      if (pFileToEncrypt == NULL) {fputs ("File to encrypt fault, check path\n",stderr); exit (1);}

  pKeystoreFile = fopen ( keystorePath.c_str() , "rb" );
      if (pKeystoreFile == NULL) {fputs ("Keystore fault, check path\n",stderr); exit (2);}

  if(encMode == AES_DECRYPT){
    bytes_read = fread(ivec, 1, sizeof(ivec), pFileToEncrypt);
    if( bytes_read < 17 ) {fputs ("No IV in file\n",stderr); exit (6);}
    printf("Dec %s\n",ivec );

  } else if (encMode == AES_ENCRYPT){
    getTrueRandom(ivec, sizeof(ivec));
    bytes_written = fwrite(ivec, 1, sizeof(ivec), pEncrypted);
    if( bytes_written < 17 ) {fputs ("Cannot store IV in file\n",stderr); exit (7);}
    printf("Enc %s\n",ivec );

  }

  fseek (pKeystoreFile , 0 , SEEK_END);
  keystoreFileSize = ftell (pKeystoreFile);
  rewind (pKeystoreFile);

  if(iKeyIdentifier < 1 || iKeyIdentifier*AES_BLOCK_SIZE > keystoreFileSize - 1 ){fputs ("keyIdentifier is broken\n",stderr); exit (3);}

  fseek(pKeystoreFile, iKeyIdentifier*AES_BLOCK_SIZE, 0);
  result = fread (ckey, 1, iKeyIdentifier*AES_BLOCK_SIZE, pKeystoreFile);
    if (result != iKeyIdentifier*AES_BLOCK_SIZE) {fputs ("Reading key store error",stderr); exit (4);}

  AES_set_encrypt_key(ckey, 128, &key);

  while (1) {
    bytes_read = fread(indata, 1, AES_BLOCK_SIZE, pFileToEncrypt);

    AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &num, encMode);

    bytes_written = fwrite(outdata, 1, bytes_read, pEncrypted);
    if (bytes_read < AES_BLOCK_SIZE)
  break;
  }

  fclose(pFileToEncrypt);
  fclose(pKeystoreFile);
  fclose(pEncrypted);

}
