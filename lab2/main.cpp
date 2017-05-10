#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "RC4.hpp"


int main(){
  RC4* tests = new RC4(5,5);
  
  tests -> setKey((unsigned char*)"eloo",sizeof("eloo"));
  tests -> info();
  delete tests;
  return 0;
}
