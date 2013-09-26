
/*-----------------------------------------------------------------------------

Melnyk O. V.
Program: MASTER

-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>

/*---------------------------------------------------------------------------*/

#define uli unsigned long int
#define textView 150L

uli slenP = 0;
uli slenT = 0;
FILE* fpT = NULL;
FILE* fpP = NULL;
FILE* fpL = NULL;
char* pattern = NULL;
char* text = NULL;

const char fileT[] = "text.txt";
const char fileP[] = "pattern.txt";
const char fileL[] = "log.txt";
/*enum forTime{CLOCK_REALTIME ,
             CLOCK_MONOTONIC,
             CLOCK_PROCESS_CPUTIME_ID,
             CLOCK_THREAD_CPUTIME_ID,
             CLOCK_MONOTONIC_RAW,
             CLOCK_REALTIME_COARSE,
             CLOCK_MONOTONIC_COARSE};
enum forTime clockTime = CLOCK_REALTIME;*/

/*---------------------------------------------------------------------------*/

void firstInit(void);

void deInit(void);

void funcErr(char* str);

void openFileT(void);

void openFileP(void);

void openFileL(void);

void randText(void);

void initText(void);

void initPattern(void);

void initLog(void);

void findC(const char* const lpattern, uli lslenP,
		   const char* const ltext, uli lslenT, FILE* lfpL);

void findKMP(const char* const lpattern, uli lslenP,
		   const char* const ltext, uli lslenT, FILE* lfpL);

void preKmp(const char* const x, uli m, long int kmpNext[]);

/*---------------------MAIN--------------------------------------------------*/

int main( int argc, char *argv[] )
{

	printf("\n");
	firstInit();

/*---------------------------------------------------------------------------*/

	printf("\n----------------------Start algorithms!---------------------\n");
	fprintf(fpL, "\n-----------------Start algorithms!--------------------\n");
	void (*pFunc)(const char* const lpattern, uli lslenP,
				  const char* const ltext, uli lslenT, FILE* lfpL) = findC;
	pFunc(pattern, slenP, text, slenT, fpL);

	pFunc = findKMP;
	pFunc(pattern, slenP, text, slenT, fpL);

/*---------------------------------------------------------------------------*/

	fprintf(fpL, "\n-------------------------END--------------------------\n");
	fprintf(fpL, "\n");
	deInit();
	printf("\n-----------------------------END----------------------------\n");
	printf("\n");

	getc(stdin);

	return 0;

}

/*----------------------------END MAIN---------------------------------------*/

void openFileT(void)
{

	if(fpT)
		fclose(fpT);
	if ((fpT = fopen(fileT, "r")) == NULL)
		funcErr("Error: can`t open file!");

	return;

}

void openFileP(void)
{

	if(fpP)
		fclose(fpP);
	if ((fpP = fopen(fileP, "r")) == NULL)
		funcErr("Error: can`t open file!");

	return;

}

void openFileL(void)
{

	if(fpL)
		fclose(fpL);
	if ((fpL = fopen(fileL, "w")) == NULL)
		funcErr("Error: can`t open file!");

	return;

}

void funcErr(char* str)
{

	printf("%s", str);
	deInit();
	printf("\n");
	exit(1);

}

void initText(void)
{

	openFileT();
	char ch = '\0';
	while(!feof(fpT))
	{
	    ch = getc(fpT);
	    if(!feof(fpT))
	    {
	    	++slenT;
		}
  	}

	if(slenT < slenP)
		funcErr("Error: length of text < length of pattern!");
	if((text = malloc(sizeof(char) * (slenT + 1))) == NULL)
	    funcErr("Error: no memory!");
	openFileT();
  	ch = '\0';
  	uli i = 0;
  	for(i = 0; i < slenT; ++i)
  	{
		ch = getc(fpT);
		text[i] = ch;
	}
  	text[slenT] = '\0';

	return;

}

void initPattern(void)
{

	openFileP();
	char ch = '\0';
	while(!feof(fpP))
	{
	    ch = getc(fpP);
	    if(!feof(fpP))
	    {
	    	++slenP;
		}
  	}

	if((pattern = malloc(sizeof(char) * (slenP + 1))) == NULL)
	    funcErr("Error: no memory!");
	openFileP();
  	ch = '\0';
  	uli i = 0;
  	for(i = 0; i < slenP; ++i)
  	{
		ch = getc(fpP);
		pattern[i] = ch;
	}
  	pattern[slenP] = '\0';

	return;

}

void initLog(void)
{

	openFileL();

}

void firstInit(void)
{

	/*There are in external: fpT fpP pattern text slenP slenT*/
	initPattern();
	initText();
	initLog();

  	if(slenT <= textView)
  		printf("\nText: \n\n%s\n", text);
  	printf("\nSize of text: %u byte.", slenT);
  	printf("\nPattern: %s", pattern);
  	printf("\nSize of pattern: %u byte.", slenP);
	if(slenT <= textView)
  		fprintf(fpL, "\nText: \n\n%s\n", text);
  	fprintf(fpL, "\nSize of text: %u byte.", slenT);
  	fprintf(fpL, "\nPattern: %s", pattern);
  	fprintf(fpL, "\nSize of pattern: %u byte.", slenP);
	fprintf(fpL, "\n");
	printf("\n");

	return;

}

void deInit(void)
{

	/*FILE* fp*/
	slenP = 0;
	slenT = 0;
	if(fpT)
		fclose(fpT);
	if(fpP)
		fclose(fpP);
	if(fpL)
		fclose(fpL);
	if(text)
		free(text);
	if(pattern)
		free(pattern);

	return;

}

void randText(void)
{

	uli i = 0;
	srand (time(NULL));
	for(i = 0; i < slenT; ++i)
	{
		int c = rand() % 23 + 98; /*no 97 'a' and no 122 'z' [98..121]*/
	    text[i] = (char) c;
	}

	return;

}

/*---------------------------------------------------------------------------*/

void findC(const char* const lpattern, uli lslenP,
		   const char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\nStandart C function 'funcC()' start.");
	fprintf(lfpL, "\nStandart C function 'funcC()' start.");
	/*const int clkID = clockTime;
	struct timespec st, et;
	double   iv;
	double testDouble = LONG_MAX;
	clock_gettime(clkID, &st);*/
	clock_t tstart = 0;
	clock_t tend = 0;
	tstart = clock();

	char* c = NULL;
	c = strstr(ltext, lpattern);
	if(c)
	{
		printf("\n\nYes, there is pattern!");
		fprintf(lfpL, "\n\nYes, there is pattern!");
	}
	else
	{
		printf("\n\nNo, there is not pattern!");
		fprintf(lfpL, "\n\nNo, there is not pattern!");
	}

	tend = clock();
	printf("\n\n%.8lf seconds for `findC()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n\n%.8lf seconds for `findC()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*clock_gettime(clkID, &et);
	iv = (et.tv_sec * 1.0e9 + et.tv_nsec) - (st.tv_sec * 1.0e9 + st.tv_nsec);
	printf("\n%.8lf seconds for `findC()`.\n", iv / 1e9);*/

	return;

}

void findKMP(const char* const lpattern, uli lslenP,
		   const char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\nKMP function 'funcKMP()' start.");
	fprintf(lfpL, "\nKMP function 'funcKMP()' start.");
	clock_t tstart = 0;
	clock_t tend = 0;
	tstart = clock();

	long int i = 0;
	long int j = 0;
	long int* kmpNext = NULL;
	if((kmpNext = malloc(sizeof(long int) * lslenP)) == NULL)
	    funcErr("Error: no memory!");
	printf("\n\nPossition = ");
	fprintf(lfpL, "\n\n Possition = ");

	/* Preprocessing */
   	preKmp(lpattern, lslenP, kmpNext);

   	/* Searching */
   	while (j < lslenT)
   	{
      	while ((i > -1) && (lpattern[i] != ltext[j]))
         	i = kmpNext[i];
      	++i;
      	++j;
      	if (i >= lslenP)
      	{
         	printf(" %li ", (j - i));
			fprintf(lfpL, " %li ", (j - i));
         	i = kmpNext[i];
      	}
   	}

	printf("\n");
	fprintf(lfpL, "\n");
	tend = clock();
	printf("\n\n%.8lf seconds for `findKMP()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n\n%.8lf seconds for `findKMP()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	free(kmpNext);

	return;

}

void preKmp(const char* const x, uli m, long int kmpNext[])
{

	long int i = 0;
	long int j = 0 ;

   	j = kmpNext[0] = -1;
   	while (i < m)
   	{
      	while ((j > -1) && (x[i] != x[j]))
         	j = kmpNext[j];
      	++i;
      	++j;
      	if (x[i] == x[j])
         	kmpNext[i] = kmpNext[j];
      	else
         	kmpNext[i] = j;
   	}

	return;

}

/*---------------------------------------------------------------------------*/

