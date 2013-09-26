
/*-----------------------------------------------------------------------------

Melnyk O. V.
myinit.c

-----------------------------------------------------------------------------*/

#include "myinit.h"

/*---------------------------------------------------------------------------*/

extern uli slenP;
extern uli slenT;
extern FILE* fpT;
extern FILE* fpP;
extern FILE* fpL;
extern unsigned char* pattern;
extern unsigned char* text;

extern const char fileT[];
extern const char fileP[];
extern const char fileL[];

/*---------------------------------------------------------------------------*/

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
	/*if((text = malloc(sizeof(unsigned char) * (slenT + 1))) == NULL)
	    funcErr("Error: no memory!");*/
	if((text = malloc(sizeof(unsigned char) * (slenT + 1 + slenP))) == NULL)
	    funcErr("Error: no memory!");
	openFileT();
  	ch = '\0';
  	uli i = 0;
  	for(i = 0; i < slenT; ++i)
  	{
		ch = getc(fpT);
		text[i] = ch;
	}
	/*text[slenT] = '\0';*/
	for(i = slenT; i < (slenT + slenP); ++i)
	  		text[i] = pattern[slenP - 1];
  	text[slenT + slenP + 1] = '\0';

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

	if((pattern = malloc(sizeof(unsigned char) * (slenP + 1))) == NULL)
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

	initPattern();
	initText();
	initLog();

  	if(slenT <= textView)
  		printf("\nText: \n\n%s\n", text);
  	printf("\nSize of text: %u byte.", slenT);
  	if(slenP <= patternView)
  		printf("\nPattern: %s", pattern);
  	printf("\nSize of pattern: %u byte.", slenP);
	if(slenT <= textView)
  		fprintf(fpL, "\nText: \n\n%s\n", text);
  	fprintf(fpL, "\nSize of text: %u byte.", slenT);
  	if(slenP <= patternView)
  		fprintf(fpL, "\nPattern: %s", pattern);
  	fprintf(fpL, "\nSize of pattern: %u byte.", slenP);
	fprintf(fpL, "\n\n");
	printf("\n\n");

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

void randText(uli Ell)
{

	if(fpT)
		fclose(fpT);
	if ((fpT = fopen(fileT, "w")) == NULL)
		funcErr("Error: can`t open file!");

	uli i = 0;
	srand (time(NULL));
	for(i = 0; i < Ell; ++i)
	{
		//int c = rand() % 23 + 98; /*no 97 'a' and no 122 'y' and 'z' [98..120]*/
		int c = rand() % 4 + 98;
		fprintf(fpT, "%c", (unsigned char) c);
		/*if(!(i % 75))
		{
			fprintf(fpT, "%c", (unsigned char) '\n');
			++i;
		}*/
	}

	fclose(fpT);

	return;

}

void randTextStr(uli Ell)
{

	char* str = "abcABC\0";
	uli N = 0;
	uli N1 = 10;
	if(fpT)
		fclose(fpT);
	if ((fpT = fopen(fileT, "w")) == NULL)
		funcErr("Error: can`t open file!");

	uli i = 0;
	uli k = 0;
	srand (time(NULL));
	for(i = 0; i < Ell;)
	{
		uli j = 0;
		for(j = 0; j < N; ++j)
		{
			int c = rand() % 21 + 100; /*no 'abc' and no 'yz'*/
			fprintf(fpT, "%c", (unsigned char) c);
			++i;
		}
		fprintf(fpT, "%s", str);
		i += strlen(str);
		++k;
		if(!(k % N1))
		{
			fprintf(fpT, "%c", (unsigned char) '\n');
			++i;
		}
	}

	fclose(fpT);

	return;

}
/*---------------------------------------------------------------------------*/

