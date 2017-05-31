#include <iostream>
#include <stdio.h>
using namespace std;

void print_bytes(const void *object, size_t size)
{
  const unsigned char * const bytes = (const unsigned char *)object;
  size_t i;

  printf("[ ");
  for(i = 0; i < size; i++)
  {
    printf("%02x ", bytes[i]);
  }
  printf("]\n");
}

int main(){
  char a = 0;
  for( int i = 0 ;i < 257 ;++i ){
    a++;
    print_bytes(&a, sizeof a);
  }
  return 0;
}
