#include <stdio.h>
#include <stdint.h>
#include "hardware.h"
#include "hw_config.h"
#include "drive.h"
#include <assert.h>

void read_sector(uint16_t cyl, uint16_t sec, unsigned char *buffer ){

  _out(HDA_DATAREGS, (cyl >> 8) & 0xFF);
  _out(HDA_DATAREGS + 1, (cyl) & 0xFF);

  _out(HDA_DATAREGS + 2, (sec >> 8) & 0xFF);
  _out(HDA_DATAREGS + 3, (sec) & 0xFF);

  _out(HDA_CMDREG, CMD_SEEK);
  _sleep(HDA_IRQ);

  _out(HDA_DATAREGS, 0);
  _out(HDA_DATAREGS, 1);
  _out(HDA_CMDREG, CMD_READ);
  _sleep(HDA_IRQ);

    for(int i = 0; i < HDA_SECTORSIZE ; i++){
      printf("%x ", buffer[i]); // buffer est le MASTERBUFFER
    }
}

void write_sector(uint16_t cyl, uint16_t sec, const unsigned char *buffer ){


  _out(HDA_DATAREGS, (cyl >> 8) & 0xFF);
  _out(HDA_DATAREGS + 1, (cyl) & 0xFF);

  _out(HDA_DATAREGS + 2, (sec >> 8) & 0xFF);
  _out(HDA_DATAREGS + 3, (sec) & 0xFF);

  _out(HDA_CMDREG, CMD_SEEK);
  _sleep(HDA_IRQ);

  _out(HDA_DATAREGS, 0);
  _out(HDA_DATAREGS, 1);


  for(int i = 0; i < HDA_SECTORSIZE ; i++){
    MASTERBUFFER[i] = buffer[i];
  }

  _out(HDA_CMDREG, CMD_WRITE);
  _sleep(HDA_IRQ);
}

void format_sector(uint16_t cyl, uint16_t sec, uint16_t nbsec, uint32_t val){

  _out(HDA_DATAREGS, (cyl >> 8) & 0xFF);
  _out(HDA_DATAREGS + 1, (cyl) & 0xFF);

  _out(HDA_DATAREGS + 2, (sec >> 8) & 0xFF);
  _out(HDA_DATAREGS + 3, (sec) & 0xFF);

  _out(HDA_CMDREG, CMD_SEEK);//déplace la tête de lecture
  _sleep(HDA_IRQ);//attend un signal pour passer à la suite

  _out(HDA_DATAREGS, (nbsec>>8)&0xFF);
  _out(HDA_DATAREGS+1, (nbsec)&0xFF);
  _out(HDA_DATAREGS+2, (val>>24)&0xFFFFFF);
  _out(HDA_DATAREGS+3, (val>>16)&0xFFFFFF);
  _out(HDA_DATAREGS+4, (val>>8)&0xFFFFFF);
  _out(HDA_DATAREGS+5, (val)&0xFFFFFF);

  _out(HDA_CMDREG, CMD_FORMAT);
  _sleep(HDA_IRQ);

}

void dmps(uint16_t cyl,  uint16_t sec){
  read_sector(cyl, sec, MASTERBUFFER);
  for (int i=0; i<HDA_SECTORSIZE; i++)
    printf("%x ", MASTERBUFFER[i]);
}

void frmt(uint16_t cyl, uint16_t sec, uint16_t nbsec){
  format_sector(cyl, sec, nbsec, 0); // pour effacer tout le disque par des 0
}
