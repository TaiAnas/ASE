#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <assert.h>
#define CTX 0xBABE

typedef int (func_t)(int);

struct ctx_s {
	void* ctx_esp;/* pointeur qui pointe sur le top de la pile */
	void* ctx_ebp;/* pointeur qui pointe sur la base de la pile */
	unsigned ctx;/*  */
};


jmp_buf buf;/*  */
struct ctx_s *pctx;

int try(struct ctx_s *pctx, func_t *f, int arg){
	
		asm("movl %%esp, %0\n" 
			:"=r"(pctx->ctx_esp));
			
		asm("movl %%ebp, %0\n" 
			:"=r"(pctx->ctx_ebp));
			
		pctx-> ctx = CTX;
	
	return (*f)(arg);
}


int throw(struct ctx_s *pctx, int r){
	static int ret = 0;
	ret = r;
	
	assert(pctx->ctx == CTX);
	
		asm("movl %0, %%esp\n" 
			:"r"(pctx->ctx_esp));
			
		asm("movl %0, %%ebp\n" 
			:"r"(pctx->ctx_ebp));

	return ret;
}

