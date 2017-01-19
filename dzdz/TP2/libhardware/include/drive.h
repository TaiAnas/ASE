#ifndef _DRIVE_H_
#define _DRIVE_H_

void read_sector(uint16_t cyl, uint16_t sec, unsigned char *buffer );
void write_sector(uint16_t cyl, uint16_t sec, const unsigned char *buffer );
void format_sector(uint16_t cyl, uint16_t sec, uint16_t nsector, uint32_t value);
void dmps(uint16_t cyl, uint16_t sec);
void frmt(uint16_t cyl, uint16_t sec, uint16_t nsector);

#endif
