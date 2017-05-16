#include "unif01.h"
#include "gdef.h"
#include "swrite.h"
#include "bbattery.h"

int main (void)
{

  swrite_Basic = FALSE;

  bbattery_FIPS_140_2File ("RC4_kN_16N_64T_64K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_64N_128T_40K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_64N_256T_128K.bin");

  bbattery_FIPS_140_2File ("RC4_kN_64N_256T_40K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_16N_32T_64K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_256N_1024T_128K.bin");

  bbattery_FIPS_140_2File ("RC4_kN_64N_128T_64K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_16N_64T_40K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_256N_1024T_64K.bin");

  bbattery_FIPS_140_2File ("RC4_kN_64N_256T_64K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_16N_128T_40K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_64N_128T_128K.bin");

  bbattery_FIPS_140_2File ("RC4_kN_256N_512T_128K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_16N_64T_128K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_16N_128T_128K.bin");

  bbattery_FIPS_140_2File ("RC4_kN_256N_512T_64K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_16N_32T_128K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_16N_32T_40K.bin");

  bbattery_FIPS_140_2File ("RC4_kN_256N_1024T_40K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_256N_512T_40K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_256N_2048T_40K.bin");

  bbattery_FIPS_140_2File ("RC4_kN_64N_512T_128K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_256N_2048T_128K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_256N_2048T_64K.bin");

  bbattery_FIPS_140_2File ("RC4_kN_64N_512T_40K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_16N_128T_64K.bin");
  bbattery_FIPS_140_2File ("RC4_kN_64N_512T_64K.bin");

  return 0;
}
