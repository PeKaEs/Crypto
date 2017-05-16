#include "unif01.h"
#include "gdef.h"
#include "swrite.h"
#include "bbattery.h"

int main (void)
{

  swrite_Basic = FALSE;

  bbattery_FIPS_140_2File ("RC4_NN_drop_64N_64T_64K_128Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_256N_256T_64K_512Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_16N_16T_64K_32Bdrop.bin");

  bbattery_FIPS_140_2File ("RC4_NN_drop_64N_64T_128K_128Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_16N_16T_64K_128Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_256N_256T_40K_1024Bdrop.bin");

  bbattery_FIPS_140_2File ("RC4_NN_drop_256N_256T_128K_2048Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_64N_64T_64K_512Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_16N_16T_128K_64Bdrop.bin");

  bbattery_FIPS_140_2File ("RC4_NN_drop_16N_16T_64K_64Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_16N_16T_40K_32Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_256N_256T_40K_512Bdrop.bin");

  bbattery_FIPS_140_2File ("RC4_NN_drop_16N_16T_40K_128Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_64N_64T_128K_256Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_256N_256T_64K_1024Bdrop.bin");

  bbattery_FIPS_140_2File ("RC4_NN_drop_256N_256T_128K_1024Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_16N_16T_40K_64Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_256N_256T_40K_2048Bdrop.bin");

  bbattery_FIPS_140_2File ("RC4_NN_drop_64N_64T_40K_128Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_64N_64T_64K_256Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_256N_256T_128K_512Bdrop.bin");

  bbattery_FIPS_140_2File ("RC4_NN_drop_64N_64T_40K_512Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_16N_16T_128K_128Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_256N_256T_64K_2048Bdrop.bin");

  bbattery_FIPS_140_2File ("RC4_NN_drop_64N_64T_128K_512Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_64N_64T_40K_256Bdrop.bin");
  bbattery_FIPS_140_2File ("RC4_NN_drop_16N_16T_128K_32Bdrop.bin");

  return 0;
}
