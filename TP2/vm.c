/* ------------------------------
   $Id: vm-skel.c,v 1.1 2002/10/21 07:16:29 marquet Exp $
   ------------------------------------------------------------

   Volume manager skeleton.
   Philippe Marquet, october 2002

   1- you must complete the NYI (not yet implemented) functions
   2- you may add commands (format, etc.)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hardware.h"
#include "drive.h"
#include "mbr.h"


static void empty_it(){
  return;
}

/* ------------------------------
   command list
   ------------------------------------------------------------*/
struct _cmd {
    char *name;
    void (*fun) (struct _cmd *c);
    char *comment;
};

static void list(struct _cmd *c);
static void new(struct _cmd *c);
static void del(struct _cmd *c);
static void help(struct _cmd *c) ;
static void save(struct _cmd *c);
static void load(struct _cmd *c);
static void dump(struct _cmd *c);
static void quit(struct _cmd *c);
static void xit(struct _cmd *c);
static void none(struct _cmd *c) ;

static struct _cmd commands [] = {
    {"list", list, 	"display the partition table"},
    {"new",  new,	"create a new partition"},
    {"del",  del,	"delete a partition"},
    {"save", save,	"save the MBR"},
    {"load", load,	"load saved MBR"},
    {"dump", dump, "dump MBR sector"},
    {"quit", quit,	"save the MBR and quit"},
    {"exit", xit,	"exit (without saving)"},
    {"help", help,	"display this help"},
    {0, none, 		"unknown command, try help"}
} ;

/* ------------------------------
   dialog and execute
   ------------------------------------------------------------*/

static void
execute(const char *name)
{
    struct _cmd *c = commands;

    while (c->name && strcmp (name, c->name))
	c++;
    (*c->fun)(c);
}

static void
loop(void)
{
    char name[64];

    while (printf("> "), scanf("%62s", name) == 1)
	execute(name) ;
}

/* ------------------------------
   command execution
   ------------------------------------------------------------*/
static void
list(struct _cmd *c)
{
    printf("%s NYI\n", c->name);
}

static void
new(struct _cmd *c)
{
    printf("%s NYI\n", c->name);
}

static void
del(struct _cmd *c)
{
    printf("%s NYI\n", c->name);
}

static void
save(struct _cmd *c)
{
    save_mbr();
    printf("%s NYI\n", c->name);
}

static void
load(struct _cmd *c)
{
    load_mbr(MASTERBUFFER);
    printf("%s NYI\n", c->name);
}

static void
dump(struct _cmd *c){
  printf("%s MBR\n", c->name);
  dump_mbr();
  printf("\nEND\n");
}

static void
quit(struct _cmd *c)
{
    printf("%s NYI\n", c->name);
    exit(EXIT_SUCCESS);
}

static void
do_xit()
{
    exit(EXIT_SUCCESS);
}

static void
xit(struct _cmd *dummy)
{
    do_xit();
}

static void
help(struct _cmd *dummy)
{
    struct _cmd *c = commands;

    for (; c->name; c++)
	printf ("%s\t-- %s\n", c->name, c->comment);
}

static void
none(struct _cmd *c)
{
    printf ("%s\n", c->comment) ;
}

int
main(int argc, char **argv)
{

  unsigned int i;

  /* init hardware */
  if(init_hardware("libhardware/etc/hardware.ini") == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
  }

  //dmps(2,3);
  /* Interreupt handlers */
  for(i=0; i<16; i++)
  IRQVECTOR[i] = empty_it;

  /* Allows all IT */
  _mask(1);
    /* dialog with user */
    loop();

    /* abnormal end of dialog (cause EOF for xample) */
    do_xit();
    /* make gcc -W happy */
    exit(EXIT_SUCCESS);
}
