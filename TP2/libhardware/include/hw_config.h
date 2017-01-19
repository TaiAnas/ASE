#ifndef _hw_config_
#define _hw_config_

//For drive
#define HDA_CMDREG 0x3F6
#define HDA_DATAREGS 0x110
#define HDA_IRQ  14
#define HDA_SECTORSIZE 512

//HDA_CMDREG      = 0x3F6        # registre de commande du disque maitre
//HDA_DATAREGS    = 0x110        # base des registres de donn�es (r,r+1,r+2,...r+15)
//HDA_IRQ         = 14           # Interruption du disque

#define TIMER_IRQ 10
/* a 8 milliseconds timer */
#define TIMER_SEC  0
#define TIMER_USEC 8000


#endif
