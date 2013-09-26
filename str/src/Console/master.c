
/*-----------------------------------------------------------------------------

Melnyk O. V.
master.c

http://ru.wikipedia.org/wiki/%D0%9F%D0%BE%D0%B8%D1%81%D0%BA_%D0%BF%D0%BE%D0%B4%D1%81%D1%82%D1%80%D0%BE%D0%BA%D0%B8
http://www-igm.univ-mlv.fr/~lecroq/string/index.html

-----------------------------------------------------------------------------*/

#include "myinit.h"
#include "myfunc.h"

/*---------------------------------------------------------------------------*/

uli slenP = 0;
uli slenT = 0;
FILE* fpT = NULL;
FILE* fpP = NULL;
FILE* fpL = NULL;
unsigned char* pattern = NULL;
unsigned char* text = NULL;

const char fileT[] = "text.txt";
const char fileP[] = "pattern.txt";
const char fileL[] = "log.txt";

short flR = 0;
short flRStr = 0;
uli CountEll = 150L;

/*---------------------MAIN--------------------------------------------------*/

int main( int argc, char *argv[] )
{

	printf("\n");

	if(flR)
	{
		randText(CountEll);
	}
	if(flRStr)
	{
		randTextStr(CountEll);
	}
	firstInit();

/*---------------------------------------------------------------------------*/

	printf("\n----------------------Start algorithms!---------------------\n");
	fprintf(fpL, "\n-----------------Start algorithms!--------------------\n");
	void (*pFunc)(const unsigned char* const lpattern, uli lslenP,
				  const unsigned char*
				  const ltext, uli lslenT, FILE* lfpL) = NULL;

	printf("\n\n--------------------------------------------------------\n\n");
	fprintf(fpL, "\n\n--------------------------------------------------\n\n");

	pFunc = findBF;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findBFO;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findSO;
	pFunc(pattern, slenP, text, slenT, fpL);

	printf("\n\n--------------------------------------------------------\n\n");
	fprintf(fpL, "\n\n--------------------------------------------------\n\n");

	pFunc = findMP;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findKMP;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findAC;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findBM;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findTBM;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findQS;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findZT;
	pFunc(pattern, slenP, text, slenT, fpL);


	pFunc = findTnBM;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findH;
	pFunc(pattern, slenP, text, slenT, fpL);


	printf("\n\n--------------------------------------------------------\n\n");
	fprintf(fpL, "\n\n--------------------------------------------------\n\n");

	pFunc = findKR;
	pFunc(pattern, slenP, text, slenT, fpL);

	printf("\n\n--------------------------------------------------------\n\n");
	fprintf(fpL, "\n\n--------------------------------------------------\n\n");

	pFunc = findDFA;
	pFunc(pattern, slenP, text, slenT, fpL);

	printf("\n\n--------------------------------------------------------\n\n");
	fprintf(fpL, "\n\n--------------------------------------------------\n\n");

	pFunc = findC;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findTW;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findNSN;
	pFunc(pattern, slenP, text, slenT, fpL);

	printf("\n\n--------------------------------------------------------\n\n");
	fprintf(fpL, "\n\n--------------------------------------------------\n\n");

/*---------------------------------------------------------------------------*/

	pFunc = NULL;
	fprintf(fpL, "\n-------------------------END--------------------------\n");
	fprintf(fpL, "\n");
	deInit();
	printf("\n\n---------------------------END----------------------------\n");
	printf("\n");

	getc(stdin);

	return 0;

}

/*----------------------------END MAIN---------------------------------------*/



