#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "RC4.hpp"


int main(){
  RC4* tests = new RC4(256,16,256);

  //tests -> setKey((unsigned char*)"elooo",sizeof("elooo"));

  for( int i=0;i<1000;i++){
    printf("%d\n",tests -> getRandom(1));
  }
  //tests -> info();
  delete tests;
  return 0;
}
