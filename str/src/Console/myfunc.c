
/*-----------------------------------------------------------------------------

Melnyk O. V.
myfunc.c

-----------------------------------------------------------------------------*/

#include "myfunc.h"
#include "myinit.h"

/*---------------------------------------------------------------------------*/

static long int MAX(long int a, long int b)
{
    return a > b ? a : b;
}

static long int MIN(long int a, long int b)
{
    return a < b ? a : b;
}

/*---------------------------------------------------------------------------*/

void findC(const unsigned char* const lpattern, uli lslenP,
		   const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nStandart C function 'funcC()' start.");
	fprintf(lfpL, "\n\nStandart C function 'funcC()' start.");

	unsigned char* c = NULL;
	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	tstart = clock();

	c = strstr(ltext, lpattern);

	tend = clock();
	if(c)
	{
		printf(" %li ", ((c - ltext) / (sizeof(unsigned char))));
		fprintf(lfpL, " %li ", ((c - ltext) / (sizeof(unsigned char))));
	}
	/*else
	{
		printf("\nNo, there is not pattern!");
		fprintf(lfpL, "\nNo, there is not pattern!");
	}*/
	printf("\n%.8lf seconds for `findC()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findC()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);

	return;

}

/*---------------------------------------------------------------------------*/

unsigned int preSo(const unsigned char* const x,
			       uli m, uli S[])
{

	uli j = 0;
	uli lim = 0;
    uli i = 0;

    for(i = 0; i < (maxAlf + 1); ++i)
    	S[i] = ~0;
    for(lim = i = 0, j = 1; i < m; ++i, j <<= 1)
    {
    	S[x[i]] &= ~j;
    	lim |= j;
    }
    lim = ~(lim >> 1);

    return(lim);

}

void findSO(const unsigned char* const lpattern, uli lslenP,
		const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nSO function 'funcSO()' start.");
	fprintf(lfpL, "\n\nSO function 'funcSO()' start.");

	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	/*uli res = 0;*/
	uli lim = 0;
	uli state = 0;
    uli S[maxAlf + 1] = {0};
    uli j;
	if(lslenP > (sizeof(int) * 8))
   	{
		printf("Use pattern size <= %li bytes (WORD * 8).", (sizeof(int) * 8));
		fprintf(lfpL, "Use pattern size <= %li bytes (WORD * 8).", (sizeof(int) * 8));
		return;
	}

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
    lim = preSo(lpattern, lslenP, S);

	tstartn = clock();

    /* Searching */
    for(state = ~0, j = 0; j < lslenT; ++j)
    {
    	state = (state << 1) | S[ltext[j]];
      	if(state < lim)
      	{
        	ttime = clock();
        	printf(" %li (%.8lf sec.) ", (j - lslenP + 1), (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", (j - lslenP + 1), (double)(ttime - tstartn)/CLOCKS_PER_SEC);
		}
    }

	tend = clock();
	printf("\n%.8lf seconds for `funcSO()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `funcSO()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `funcSO()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `funcSO()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `funcSO()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `funcSO()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/


	return;

}

/*---------------------------------------------------------------------------*/

void findNSN(const unsigned char* const lpattern, uli lslenP,
		 const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nNSN function 'funcNSN()' start.");
	fprintf(lfpL, "\n\nNSN function 'funcNSN()' start.");

	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	/*uli res = 0;*/
	uli j = 0;
	uli k = 0;
	uli ell = 0;

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
	if(lpattern[0] == lpattern[1])
	{
    	k = 2;
      	ell = 1;
   	}
   	else
   	{
      	k = 1;
      	ell = 2;
   	}

	tstartn = clock();

    /* Searching */
	j = 0;
   	while(j <= lslenT - lslenP)
    	if(lpattern[1] != ltext[j + 1])
        	j += k;
      	else
      	{
        	if(memcmp(lpattern + 2, ltext + j + 2, lslenP - 2) == 0
        		&& lpattern[0] == ltext[j])
        	{
            	ttime = clock();
            	printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
				fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			}
         	j += ell;
      	}

	tend = clock();
	printf("\n%.8lf seconds for `funcNSN()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `funcNSN()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `funcNSN()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `funcNSN()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `funcNSN()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `funcNSN()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	return;

}

/*---------------------------------------------------------------------------*/

void preKmp(const unsigned char* const x, uli m, long int kmpNext[])
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

void findKMP(const unsigned char* const lpattern, uli lslenP,
		     const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nKMP function 'funcKMP()' start.");
	fprintf(lfpL, "\n\nKMP function 'funcKMP()' start.");

	/*uli res = 0;*/
	long int i = 0;
	long int j = 0;
	long int* kmpNext = NULL;
	if((kmpNext = malloc(sizeof(long int) * lslenP)) == NULL)
	    funcErr("Error: no memory!");
	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
   	preKmp(lpattern, lslenP, kmpNext);

	tstartn = clock();

   	/* Searching */
   	while (j < lslenT)
   	{
      	while ((i > -1) && (lpattern[i] != ltext[j]))
         	i = kmpNext[i];
      	++i;
      	++j;
      	if (i >= lslenP)
      	{
         	ttime = clock();
         	printf(" %li (%.8lf sec.) ", (j - i), (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", (j - i), (double)(ttime - tstartn)/CLOCKS_PER_SEC);
         	i = kmpNext[i];
      	}
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findKMP()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findKMP()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findKMP()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findKMP()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findKMP()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findKMP()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	free(kmpNext);

	return;

}

void preMp(const unsigned char* const x, uli m, long int mpNext[])
{

	long int i = 0;
	long int j = 0;

   	j = mpNext[0] = -1;
   	while (i < m)
   	{
      	while (j > -1 && x[i] != x[j])
         	j = mpNext[j];
      	mpNext[++i] = ++j;
   	}

	return;

}

void findMP(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nMP function 'funcMP()' start.");
	fprintf(lfpL, "\n\nMP function 'funcMP()' start.");

	/*uli res = 0;*/
	long int i = 0;
	long int j = 0;
	long int* mpNext = NULL;
	if((mpNext = malloc(sizeof(long int) * lslenP)) == NULL)
	    funcErr("Error: no memory!");
	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

   	/* Preprocessing */
   	preMp(lpattern, lslenP, mpNext);

	tstartn = clock();

   	/* Searching */
   	i = j = 0;
   	while (j < lslenT)
   	{
      	while (i > -1 && lpattern[i] != ltext[j])
         	i = mpNext[i];
      	++i;
      	++j;
      	if (i >= lslenP)
      	{
         	ttime = clock();
         	printf(" %li (%.8lf sec.) ", (j - i), (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", (j - i), (double)(ttime - tstartn)/CLOCKS_PER_SEC);
         	i = mpNext[i];
      	}
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findMP()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findMP()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findMP()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findMP()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findMP()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findMP()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	free(mpNext);

	return;

}

void findAC(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nAC function 'funcAC()' start.");
	fprintf(lfpL, "\n\nAC function 'funcAC()' start.");

	/*uli res = 0;*/
	long int i = 0;
	long int j = 0;
	long int k = 0;
	long int ell = 0;
	long int* kmpNext = NULL;
	if((kmpNext = malloc(sizeof(long int) * lslenP)) == NULL)
	    funcErr("Error: no memory!");
	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
   	preKmp(lpattern, lslenP, kmpNext);
	for(ell = 1; lpattern[ell - 1] == lpattern[ell]; ++ell);
   	if(ell == lslenP)
    	ell = 0;

	tstartn = clock();

   	/* Searching */
	i = ell;
   	j = k = 0;
   	while(j <= lslenT - lslenP)
   	{
    	while(i < lslenP && lpattern[i] == ltext[i + j])
        	++i;
      	if (i >= lslenP)
      	{
        	while (k < ell && lpattern[k] == ltext[j + k])
            	++k;
         	if (k >= ell)
         	{
            	ttime = clock();
            	printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
				fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			}
      	}
      	j += (i - kmpNext[i]);
      	if (i == ell)
         	k = MAX(0, k - 1);
      	else
         	if (kmpNext[i] <= ell)
         	{
            	k = MAX(0, kmpNext[i]);
            	i = ell;
         	}
         	else
         	{
            	k = ell;
            	i = kmpNext[i];
         	}
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findAC()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findAC()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findAC()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findAC()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findAC()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findAC()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	free(kmpNext);

	return;

}

/*---------------------------------------------------------------------------*/

void findKR(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nKR function 'funcKR()' start.");
	fprintf(lfpL, "\n\nKR function 'funcKR()' start.");

	/*uli res = 0;*/
	long int i = 0;
	long int j = 0;
	uli d = 0;
	uli hx = 0;
	uli hy = 0;
	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
   	/* computes d = 2^(m-1) with the left-shift operator */
   	for (d = i = 1; i < lslenP; ++i)
      	d = (d << 1);

   	for (hy = hx = i = 0; i < lslenP; ++i)
   	{
      	hx = ((hx << 1) + lpattern[i]);
      	hy = ((hy << 1) + ltext[i]);
   	}

	tstartn = clock();

   	/* Searching */
   	j = 0;
   	while (j <= lslenT - lslenP)
   	{
      	if (hx == hy && memcmp(lpattern, ltext + j, lslenP) == 0)
      	{
         	ttime = clock();
         	printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
	 	}
      	hy = REHASH(ltext[j], ltext[j + lslenP], hy);
      	++j;
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findKR()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findKR()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findKR()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findKR()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findKR()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findKR()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	return;

}

/*---------------------------------------------------------------------------*/

void findBF(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nBF function 'funcBF()' start.");
	fprintf(lfpL, "\n\nBF function 'funcBF()' start.");

	/*uli res = 0;*/
	long int i = 0;
	long int j = 0;
	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t ttime = 0;
	tstart = clock();

   	/* Searching */
   	for (j = 0; j <= lslenT - lslenP; ++j)
   	{
      	for (i = 0; i < lslenP && lpattern[i] == ltext[i + j]; ++i);
      	if (i >= lslenP)
      	{
         	ttime = clock();
         	printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstart)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstart)/CLOCKS_PER_SEC);
		}
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findBF()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findBF()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	return;

}

void findBFO(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nBFO function 'funcBFO()' start.");
	fprintf(lfpL, "\n\nBFO function 'funcBFO()' start.");

	/*uli res = 0;*/
	const unsigned char* yb = NULL;
	const unsigned char* y = NULL;
	y = ltext;
	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t ttime = 0;
	tstart = clock();

   	/* Searching */
	for (yb = ltext; *y != EOS; ++y)
		if (memcmp(lpattern, y, lslenP) == 0)
		{

      		ttime = clock();
			printf(" %li (%.8lf sec.) ", y - yb, (double)(ttime - tstart)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", y - yb, (double)(ttime - tstart)/CLOCKS_PER_SEC);
		}

	tend = clock();
	printf("\n%.8lf seconds for `findBFO()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findBFO()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	return;

}

/*---------------------------------------------------------------------------*/

void preBmBc(const unsigned char* const x, uli m, long int bmBc[])
{

	long int i = 0;

   	for (i = 0; i < maxAlf + 1; ++i)
      	bmBc[i] = m;
   	for (i = 0; i < m - 1; ++i)
      	bmBc[x[i]] = m - i - 1;

	return;

}


void suffixes(const unsigned char* const x, uli m, long int* suff)
{

   	long int f = 0;
   	long int g = 0;
   	long int i = 0;

   	suff[m - 1] = m;
   	g = m - 1;
   	for (i = m - 2; i >= 0; --i)
   	{
   	   if (i > g && suff[i + m - 1 - f] < i - g)
   	      suff[i] = suff[i + m - 1 - f];
   	   else
   	   {
   	      if (i < g)
   	         g = i;
   	      f = i;
   	      while (g >= 0 && x[g] == x[g + m - 1 - f])
   	         --g;
   	      suff[i] = f - g;
   	   }
   	}

	return;

}

void preBmGs(const unsigned char* const x, uli m, long int bmGs[])
{

   	long int i = 0;
   	long int j = 0;
   	long int* suff = NULL;
   	if((suff = malloc(sizeof(long int) * m)) == NULL)
	    funcErr("Error: no memory!");

   	suffixes(x, m, suff);

   	for (i = 0; i < m; ++i)
   	   bmGs[i] = m;
   	j = 0;
   	for (i = m - 1; i >= 0; --i)
   	   if (suff[i] == i + 1)
   	      for (; j < m - 1 - i; ++j)
	         if (bmGs[j] == m)
   	            bmGs[j] = m - 1 - i;
   	for (i = 0; i <= m - 2; ++i)
   	   bmGs[m - 1 - suff[i]] = m - 1 - i;

	free(suff);

	return;

}

void findBM(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nBM function 'funcBM()' start.");
	fprintf(lfpL, "\n\nBM function 'funcBM()' start.");

	/*uli res = 0;*/
	long int i = 0;
	long int j = 0;
	long int* bmGs = NULL;
	if((bmGs = malloc(sizeof(long int) * lslenP)) == NULL)
	    funcErr("Error: no memory!");
	long int* bmBc = NULL;
	if((bmBc = malloc(sizeof(long int) * (maxAlf + 1))) == NULL)
	    funcErr("Error: no memory!");
   	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

 	/* Preprocessing */
   	preBmGs(lpattern, lslenP, bmGs);
   	preBmBc(lpattern, lslenP, bmBc);

	tstartn = clock();

   	/* Searching */
   	j = 0;
   	while (j <= lslenT - lslenP)
   	{
      	for (i = lslenP - 1; i >= 0 && lpattern[i] == ltext[i + j]; --i);
      	if (i < 0)
      	{
         	ttime = clock();
         	printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
         	j += bmGs[0];
      	}
      	else
      	   j += MAX(bmGs[i], bmBc[ltext[i + j]] - lslenP + 1 + i);
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findBM()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findBM()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findBM()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findBM()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findBM()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findBM()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	free(bmGs);
	free(bmBc);

	return;

}

void findTBM(const unsigned char* const lpattern, uli lslenP,
		     const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nTBM function 'funcTBM()' start.");
	fprintf(lfpL, "\n\nTBM function 'funcTBM()' start.");

	/*uli res = 0;*/
	long int i = 0;
	long int j = 0;
	long int shift = 0;
	long int bcShift = 0;
	long int u = 0;
	long int v = 0;
	long int turboShift = 0;
	long int* bmGs = NULL;
	if((bmGs = malloc(sizeof(long int) * lslenP)) == NULL)
	    funcErr("Error: no memory!");
	long int* bmBc = NULL;
	if((bmBc = malloc(sizeof(long int) * (maxAlf + 1))) == NULL)
	    funcErr("Error: no memory!");
   	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
  	preBmGs(lpattern, lslenP, bmGs);
   	preBmBc(lpattern, lslenP, bmBc);

	tstartn = clock();

   	/* Searching */
   	j = u = 0;
   	shift = lslenP;
   	while (j <= lslenT - lslenP)
   	{
      	i = lslenP - 1;
      	while (i >= 0 && lpattern[i] == ltext[i + j])
      	{
         	--i;
         	if (u != 0 && i == lslenP - 1 - shift)
            	i -= u;
      	}
      	if (i < 0)
      	{
         	ttime = clock();
         	printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
         	shift = bmGs[0];
         	u = lslenP - shift;
      	}
      	else
      	{
         	v = lslenP - 1 - i;
         	turboShift = u - v;
         	bcShift = bmBc[ltext[i + j]] - lslenP + 1 + i;
         	shift = MAX(turboShift, bcShift);
         	shift = MAX(shift, bmGs[i]);
         	if (shift == bmGs[i])
            	u = MIN(lslenP - shift, v);
         	else
         	{
           		if (turboShift < bcShift)
              		shift = MAX(shift, u + 1);
           		u = 0;
         	}
      	}
      	j += shift;
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findTBM()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findTBM()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findTBM()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findTBM()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findTBM()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findTBM()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	free(bmGs);
	free(bmBc);

	return;

}

void findTnBM(const unsigned char* const lpattern, uli lslenP,
		      const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nTnBM function 'funcTnBM()' start.");
	fprintf(lfpL, "\n\nTnBM function 'funcTnBM()' start.");

	/*uli res = 0;*/
	long int k = 0;
	long int j = 0;
	long int shift = 0;
	long int* bmBc = NULL;
	if((bmBc = malloc(sizeof(long int) * (maxAlf + 1))) == NULL)
	    funcErr("Error: no memory!");
   	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
	preBmBc(lpattern, lslenP, bmBc);
	shift = bmBc[lpattern[lslenP - 1]];
	bmBc[lpattern[lslenP - 1]] = 0;
	/*maybe malloc text in main already bigest*/
	memset(ltext + lslenT, lpattern[lslenP - 1], lslenP);

	tstartn = clock();

	/* Searching */
	j = 0;
	while (j < lslenT)
	{
		k = bmBc[ltext[j + lslenP - 1]];
	    while (k !=  0)
	    {
	    	j += k;
	    	k = bmBc[ltext[j + lslenP - 1]];
	        j += k;
	        k = bmBc[ltext[j + lslenP - 1]];
	        j += k;
	        k = bmBc[ltext[j + lslenP - 1]];
	    }
	    if (memcmp(lpattern, ltext + j, lslenP - 1) == 0 && j < lslenT)
	    {
	    	ttime = clock();
	    	printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
		}
	    j += shift;                          /* shift */
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findTnBM()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findTnBM()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findTnBM()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findTnBM()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findTnBM()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findTnBM()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	free(bmBc);

	return;

}

void preZtBc(const unsigned char* const x, uli m,
			 long int ztBc[maxAlf + 1][maxAlf + 1])
{

	long int i = 0;
	long int j = 0;

   	for (i = 0; i < maxAlf + 1; ++i)
      	for (j = 0; j < maxAlf + 1; ++j)
         	ztBc[i][j] = m;
   	for (i = 0; i < maxAlf + 1; ++i)
      	ztBc[i][x[0]] = m - 1;
   	for (i = 1; i < m - 1; ++i)
      	ztBc[x[i - 1]][x[i]] = m - 1 - i;

	return;

}

void findZT(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nZT function 'funcZT()' start.");
	fprintf(lfpL, "\n\nZT function 'funcZT()' start.");

	/*uli res = 0;*/
	long int i = 0;
	long int j = 0;
	long int ztBc[maxAlf + 1][maxAlf + 1];
	long int* bmGs = NULL;
	if((bmGs = malloc(sizeof(long int) * lslenP)) == NULL)
	    funcErr("Error: no memory!");
   	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
	preZtBc(lpattern, lslenP, ztBc);
	preBmGs(lpattern, lslenP, bmGs);

	tstartn = clock();

	/* Searching */
	j = 0;
	while (j <= lslenT - lslenP)
	{
	    i = lslenP - 1;
	    while (i < lslenP && lpattern[i] == ltext[i + j])
	    	--i;
	    if (i < 0)
	    {
	    	ttime = clock();
	    	printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
	       	j += bmGs[0];
	    }
	   	else
	    	j += MAX(bmGs[i],
	    			 ztBc[ltext[j + lslenP - 2]][ltext[j + lslenP - 1]]);
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findZT()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findZT()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findZT()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findZT()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findZT()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findZT()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	free(bmGs);

	return;

}

void findH(const unsigned char* const lpattern, uli lslenP,
		   const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nH function 'funcH()' start.");
	fprintf(lfpL, "\n\nH function 'funcH()' start.");

	/*uli res = 0;*/
	long int j = 0;
	long int bmBc[maxAlf + 1] = {0};
	unsigned char c = '\0';
   	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
	preBmBc(lpattern, lslenP, bmBc);

	tstartn = clock();

   	/* Searching */
	j = 0;
	while (j <= lslenT - lslenP)
	{
		c = ltext[j + lslenP - 1];
	    if (lpattern[lslenP - 1] == c &&
	    	memcmp(lpattern, ltext + j, lslenP - 1) == 0)
	    {
	    	ttime = clock();
	    	printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
		}
	    j += bmBc[c];
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findH()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findH()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findH()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findH()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findH()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findH()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	return;

}

void preQsBc(const unsigned char* const x, uli m, uli qsBc[])
{

	long int i = 0;

   	for (i = 0; i < (maxAlf + 1); ++i)
      	qsBc[i] = m + 1;
   	for (i = 0; i < m; ++i)
      	qsBc[x[i]] = m - i;

	return;

}

void findQS(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nQS function 'funcQS()' start.");
	fprintf(lfpL, "\n\nQS function 'funcQS()' start.");

	/*uli res = 0;*/
	long int j = 0;
	long int qsBc[maxAlf + 1] = {0};
	unsigned char c = '\0';
   	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
	preQsBc(lpattern, lslenP, qsBc);

	tstartn = clock();

   	/* Searching */
	j = 0;
	while (j <= lslenT - lslenP)
	{
		if (memcmp(lpattern, ltext + j, lslenP) == 0)
		{
			ttime = clock();
			printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
		}
	    j += qsBc[ltext[j + lslenP]];               /* shift */
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findQS()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findQS()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findQS()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findQS()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findQS()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findQS()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	return;

}

/*---------------------------------------------------------------------------*/

void error(char* str)
{

	printf("%s", str);
	deInit();
	printf("\n");
	exit(1);

}

Graph newGraph(long int v, long int e)
{

	Graph g;

   	g = (Graph)calloc(1, sizeof(struct _graph));
   	if (g == NULL)
      		error("newGraph");
   	g->vertexNumber = v;
   	g->edgeNumber = e;
   	g->initial = 0;
   	g->vertexCounter = 1;

   	return(g);

}

Graph newAutomaton(long int v, long int e)
{

	Graph aut;

   	aut = newGraph(v, e);
   	aut->target = (long int* )calloc(e, sizeof(long int));
   	if (aut->target == NULL)
      	error("newAutomaton");
   	aut->terminal = (long int* )calloc(v, sizeof(long int));
   	if (aut->terminal == NULL)
      	error("newAutomaton");

   	return(aut);

}

Graph newSuffixAutomaton(long int v, long int e)
{

	Graph aut;

   	aut = newAutomaton(v, e);
   	memset(aut->target, UNDEFINED, e * sizeof(long int));
   	aut->suffixLink = (long int* )calloc(v, sizeof(long int));
   	if (aut->suffixLink == NULL)
      	error("newSuffixAutomaton");
   	aut->length = (long int* )calloc(v, sizeof(long int));
   	if (aut->length == NULL)
      	error("newSuffixAutomaton");
   	aut->position = (long int* )calloc(v, sizeof(long int));
   	if (aut->position == NULL)
      	error("newSuffixAutomaton");
   	aut->shift = (long int* )calloc(e, sizeof(long int));
   	if (aut->shift == NULL)
      	error("newSuffixAutomaton");

   	return(aut);

}

long int newVertex(Graph g)
{

	if (g != NULL && g->vertexCounter <= g->vertexNumber)
      	return(g->vertexCounter++);
   	error("newVertex");

}

long int getInitial(Graph g)
{

	if (g != NULL)
      	return(g->initial);
   	error("getInitial");

}

BOOLean isTerminal(Graph g, long int v)
{

	if (g != NULL && g->terminal != NULL &&
       	v < g->vertexNumber)
      	return(g->terminal[v]);
   	error("isTerminal");

}

void setTerminal(Graph g, long int v)
{

	if (g != NULL && g->terminal != NULL &&
       	v < g->vertexNumber)
      	g->terminal[v] = 1;
   	else
      	error("isTerminal");

}

long int getTarget(Graph g, long int v, unsigned char c)
{

	if (g != NULL && g->target != NULL &&
       	v < g->vertexNumber && v * c < g->edgeNumber)
      	return(g->target[v * (g->edgeNumber/g->vertexNumber) +
                       c]);
   	error("getTarget");

}

void setTarget(Graph g, long int v, unsigned char c, long int t)
{

	if (g != NULL && g->target != NULL &&
       	v < g->vertexNumber &&
       	v * c <= g->edgeNumber && t < g->vertexNumber)
      	g->target[v * (g->edgeNumber/g->vertexNumber) + c] = t;
   	else
      	error("setTarget");

}

long int getSuffixLink(Graph g, long int v)
{

	if (g != NULL && g->suffixLink != NULL &&
       	v < g->vertexNumber)
      	return(g->suffixLink[v]);
   	error("getSuffixLink");

}

void setSuffixLink(Graph g, long int v, long int s)
{

	if (g != NULL && g->suffixLink != NULL &&
       	v < g->vertexNumber && s < g->vertexNumber)
      	g->suffixLink[v] = s;
   	else
      	error("setSuffixLink");

}

long int getLength(Graph g, long int v)
{

   if (g != NULL && g->length != NULL &&
       v < g->vertexNumber)
      return(g->length[v]);
   error("getLength");

}

void setLength(Graph g, long int v, long int ell)
{

	if (g != NULL && g->length != NULL &&
       	v < g->vertexNumber)
      	g->length[v] = ell;
   	else
      	error("setLength");
}

long int getPosition(Graph g, long int v)
{

	if (g != NULL && g->position != NULL &&
       	v < g->vertexNumber)
      	return(g->position[v]);
   	error("getPosition");

}

void setPosition(Graph g, long int v, long int p)
{

	if (g != NULL && g->position != NULL &&
       	v < g->vertexNumber)
      	g->position[v] = p;
   	else
      	error("setPosition");

}

Graph newTrie(long int v, long int e)
{

	Graph aut;

   	aut = newAutomaton(v, e);
   	memset(aut->target, UNDEFINED, e * sizeof(long int));
   	aut->suffixLink = (long int* )calloc(v, sizeof(long int));
   	if (aut->suffixLink == NULL)
      	error("newTrie");
   	aut->length = (long int* )calloc(v, sizeof(long int));
   	if (aut->length == NULL)
      	error("newTrie");
   	aut->position = (long int* )calloc(v, sizeof(long int));
   	if (aut->position == NULL)
      	error("newTrie");
   	aut->shift = (long int* )calloc(e, sizeof(long int));
   	if (aut->shift == NULL)
      	error("newTrie");

   	return(aut);

}

long int getShift(Graph g, long int v, unsigned char c)
{

	if (g != NULL && g->shift != NULL &&
       	v < g->vertexNumber && v * c < g->edgeNumber)
      	return(g->shift[v * (g->edgeNumber / g->vertexNumber) +
               c]);
   	error("getShift");

}

void setShift(Graph g, long int v, unsigned char c, long int s)
{

	if (g != NULL && g->shift != NULL &&
       	v < g->vertexNumber && v * c <= g->edgeNumber)
      	g->shift[v * (g->edgeNumber / g->vertexNumber) + c] = s;
   	else
      	error("setShift");
}

void copyVertex(Graph g, long int target, long int source)
{

	if (g != NULL && target < g->vertexNumber &&
       	source < g->vertexNumber)
       	{
      	if (g->target != NULL)
         	memcpy(g->target +
                	target * (g->edgeNumber / g->vertexNumber),
                	g->target +
                	source * (g->edgeNumber / g->vertexNumber),
                			 (g->edgeNumber / g->vertexNumber) *
                	sizeof(long int));
      	if (g->shift != NULL)
        	memcpy(g->shift +
			                target * (g->edgeNumber / g->vertexNumber),
			                g->shift +
			                source * (g->edgeNumber / g->vertexNumber),
			                g->edgeNumber/g->vertexNumber * sizeof(long int));
      	if (g->terminal != NULL)
         	g->terminal[target] = g->terminal[source];
      	if (g->suffixLink != NULL)
         	g->suffixLink[target] = g->suffixLink[source];
      	if (g->length != NULL)
         	g->length[target] = g->length[source];
      	if (g->position != NULL)
         	g->position[target] = g->position[source];
   	}
   	else
      	error("copyVertex");

}

void preAut(const unsigned char* const x, uli m, Graph aut)
{

	long int i = 0;
   	long int state = 0;
   	long int target = 0;
   	long int oldTarget = 0;

   	for (state = getInitial(aut), i = 0; i < m; ++i)
   	{
      	oldTarget = getTarget(aut, state, x[i]);
      	target = newVertex(aut);
      	setTarget(aut, state, x[i], target);
      	copyVertex(aut, target, oldTarget);
      	state = target;
   	}
   	setTerminal(aut, state);

   	return;

}

void findDFA(const unsigned char* const lpattern, uli lslenP,
		       const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nDFA function 'funcDFA()' start.");
	fprintf(lfpL, "\n\nDFA function 'funcDFA()' start.");

	/*uli res = 0;*/
	long int state = 0;
	long int j = 0;
	Graph aut;
   	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
   	aut = newAutomaton(lslenP + 1, (lslenP + 1) * (maxAlf + 1));
   	preAut(lpattern, lslenP, aut);

	tstartn = clock();

   	/* Searching */
   	for (state = getInitial(aut), j = 0; j < lslenT; ++j)
   	{
		state = getTarget(aut, state, ltext[j]);
   	   	if (isTerminal(aut, state))
   	   	{
   	      	ttime = clock();

   	      	printf(" %li (%.8lf sec.) ", (j - lslenP + 1), (double)(ttime - tstartn)/CLOCKS_PER_SEC);
			fprintf(lfpL, " %li (%.8lf sec.) ", (j - lslenP + 1), (double)(ttime - tstartn)/CLOCKS_PER_SEC);
	  	}
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findDFA()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findDFA()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findDFA()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findDFA()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findDFA()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findDFA()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	return;

}

/*---------------------------------------------------------------------------*/

long int maxSuf(const unsigned char* const x, uli m, uli* p)
{

	long int ms = 0;
	long int j = 0;
	long int k = 0;
   	unsigned char a = '\0';
   	unsigned char b = '\0';

   	ms = -1;
   	j = 0;
   	k = *p = 1;
   	while (j + k < m)
   	{
      	a = x[j + k];
      	b = x[ms + k];
      	if (a < b)
      	{
         	j += k;
         	k = 1;
         	*p = j - ms;
     	}
      	else
         	if (a == b)
            	if (k != *p)
               		++k;
            	else
            	{
               		j += *p;
               		k = 1;
            	}
         	else
         	{ /* a > b */
            	ms = j;
            	j = ms + 1;
            	k = *p = 1;
         	}
   	}

   	return(ms);

}

long int maxSufTilde(const unsigned char* const x, uli m, uli* p)
{
	long int ms = 0;
	long int j = 0;
	long int k = 0;
	unsigned char a = '\0';
   	unsigned char b = '\0';

   	ms = -1;
   	j = 0;
   	k = *p = 1;
   	while (j + k < m)
   	{
      	a = x[j + k];
      	b = x[ms + k];
      	if (a > b)
      	{
         	j += k;
         	k = 1;
         	*p = j - ms;
      	}
      	else
         	if (a == b)
            	if (k != *p)
               		++k;
            	else
            	{
               		j += *p;
               		k = 1;
            	}
         	else
         	{ /* a < b */
            	ms = j;
            	j = ms + 1;
            	k = *p = 1;
         	}
   	}

   	return(ms);

}

void findTW(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL)
{

	printf("\n\nTW function 'funcTW()' start.");
	fprintf(lfpL, "\n\nTW function 'funcTW()' start.");

	/*uli res = 0;*/
	long int ell = 0;
	long int j = 0;
	long int i = 0;
	long int memory = 0;
	long int per = 0;
	long int q = 0;
	long int p = 0;
   	printf("\nPossition = ");
	fprintf(lfpL, "\nPossition = ");

	clock_t tstart = 0;
	clock_t tend = 0;
	clock_t tstartn = 0;
	clock_t ttime = 0;
	tstart = clock();

	/* Preprocessing */
	i = maxSuf(lpattern, lslenP, &p);
   	j = maxSufTilde(lpattern, lslenP, &q);
   	if (i > j)
   	{
      	ell = i;
      	per = p;
   	}
   	else
   	{
      	ell = j;
      	per = q;
   	}

	tstartn = clock();

   	/* Searching */
	if (memcmp(lpattern, lpattern + per, ell + 1) == 0)
	{
		j = 0;
      	memory = -1;
      	while (j <= lslenT - lslenP)
      	{
        	i = MAX(ell, memory) + 1;
         	while (i < lslenP && lpattern[i] == ltext[i + j])
            	++i;
         	if (i >= lslenP)
         	{
            	i = ell;
            	while (i > memory && lpattern[i] == ltext[i + j])
               		--i;
            	if (i <= memory)
            	{
					ttime = clock();
					printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
					fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
				}
            	j += per;
            	memory = lslenP - per - 1;
         	}
         	else
         	{
            	j += (i - ell);
            	memory = -1;
         	}
      	}
   	}
   	else
   	{
    	per = MAX(ell + 1, lslenP - ell - 1) + 1;
      	j = 0;
      	while (j <= lslenT - lslenP)
      	{
         	i = ell + 1;
         	while (i < lslenP && lpattern[i] == ltext[i + j])
            	++i;
         	if (i >= lslenP)
         	{
            	i = ell;
            	while (i >= 0 && lpattern[i] == ltext[i + j])
               		--i;
            	if (i < 0)
            	{
               		ttime = clock();
					printf(" %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
					fprintf(lfpL, " %li (%.8lf sec.) ", j, (double)(ttime - tstartn)/CLOCKS_PER_SEC);
				}
            	j += per;
         	}
         	else
            	j += (i - ell);
      	}
   	}

	tend = clock();
	printf("\n%.8lf seconds for `findTW()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findTW()` preprocessing.",
		   (double)(tstartn - tstart)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findTW()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findTW()` searching.",
		   (double)(tend - tstartn)/CLOCKS_PER_SEC);
	printf("\n%.8lf seconds for `findTW()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	fprintf(lfpL, "\n%.8lf seconds for `findTW()`.\n",
		   (double)(tend - tstart)/CLOCKS_PER_SEC);
	/*printf("\nCount of comparisons = %li.\n", res);
	fprintf(lfpL, "\nCount of comparisons = %li.\n", res);*/

	return;

}

/*---------------------------------------------------------------------------*/
