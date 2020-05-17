//Virtual Machine:
//Used to process custom commands
#include <stdio.h>
#include <stdlib.h>
#define int long long //So converting from int pointer to int has no issues

//Q:
//Why cmd and pc?
// Why use pointers over values?
//Commands of Machine
enum { LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT };

// Pointers
int *sp, *bp, *pc, *cmd;

int tk, eax, inst; // eax register
	



int main(void){
//Create area for stack and code text area
//Must be inside main or else won't run
	bp = sp = malloc(sizeof(int)*100);
	pc = cmd= malloc(sizeof(int)*100);
		
	//test
	*cmd = LEA; cmd++;
	*cmd = -1 ; cmd++;
	*cmd = PSH; cmd++;
	*cmd = IMM; cmd++;
	*cmd = 8  ; cmd++; //eax = 8
	*cmd = SI ; cmd++; 

//	*cmd = IMM; cmd++;
//	*cmd = 10 ; cmd++;
//	*cmd = PSH; cmd++;
//	*cmd = IMM; cmd++;
//	*cmd = 20 ; cmd++;
//	*cmd = PSH; cmd++;

//	*cmd = IMM; cmd++;
//	*cmd = 13 ; cmd++;
//
//	*cmd = ADD; cmd++;
//	*cmd = ADD; cmd++;

	*cmd = EXIT; cmd++;

	while(1){ //Infinitely Run commands till finish
	printf("before exec:pc %llx *pc %llx bp %llx eax:%d *sp: %llx sp %llx \n", pc, *pc, bp, eax, sp, *sp);	
		inst = *pc++;
		//define:
		if(inst == ENT){*--sp = (int)bp; bp = sp; sp = sp - *pc;}
		if(inst == LEV){sp = bp; bp = (int *)*sp++; pc = (int *)*sp++;}
		if(inst == LEA){eax = (int)(bp + *pc++);}
		if(inst == IMM){eax = *pc; pc++;}
		if(inst == PSH){*--sp = eax;}
		if(inst == LI ){eax = *(int *)eax;}
		if(inst == SI ){*(int *)*sp++ = eax;}

		//expr
		if(inst == ADD){eax = *sp++ + eax;}
		if(inst == SUB){eax = eax - *sp++;}
		if(inst == MUL){eax = eax * *sp++;}
		if(inst == DIV){eax = eax / *sp++;}

        printf("%.4s",
        	&"LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,"
        	"OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
        	"OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT,"[inst * 5]);
		printf("\n");
		for(int i=0; i<10; i++) printf(" %llx ", *(bp-i));
		printf("\n");

		if(inst == EXIT){return 0;}
	}
	return 0;
}
