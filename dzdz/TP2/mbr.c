#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mbr.h"
#include "hw_config.h"
#include "drive.h"
#include "hardware.h"

/*Un partition est une structure volume, une partition est composée :
* - de la piste et secteur du début de la partition
* - du nombre de sector de la partition
* - et le type de la partition
*/
struct S_VOLUME {
  uint16_t cylinder;
  uint16_t sector;
  unsigned int nbSector;
  E_VOLUME_TYPE type;
};

/*Une structure S_MBR contient :
* - le nombre de volume d'un disque physique
* - un tableau de ces volumes
* - un numéro magic pour s'assurer que la structure n'est pas corrompu
*/
struct S_MBR {
  uint8_t nbVolume;
  S_VOLUME vol[8];
  int magic;
};


/*Global MBR*/
S_MBR s_mbr;// = NULL;

void save_mbr(){//save from mem to struct mbr
  unsigned char buffer[HDA_SECTORSIZE];

  read_sector(0,0,buffer);
  memcpy(&s_mbr, buffer, sizeof(S_MBR));

  if (s_mbr.magic != MBR_MAGIC){
    s_mbr.magic = MBR_MAGIC;
    s_mbr.nbVolume = 0;
  }
}

void load_mbr(){//load from saved mbr to mem
  unsigned char buffer[HDA_SECTORSIZE];
  memcpy(buffer, &s_mbr, sizeof(S_MBR));
  write_sector(0,0,buffer);
}

void dump_mbr(){
  dmps(0,0);
}
