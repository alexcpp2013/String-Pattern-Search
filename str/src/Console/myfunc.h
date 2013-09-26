
/*-----------------------------------------------------------------------------

Melnyk O. V.
myfunc.h

-----------------------------------------------------------------------------*/

#ifndef MYFUNC_H
#define MYFUNC_H

#include "mydef.h"

/*---------------------------------------------------------------------------*/

static long int MAX(long int a, long int b);

static long int MIN(long int a, long int b);

/*---------------------------------------------------------------------------*/

/*strstr()*/
void findC(const unsigned char* const lpattern, uli lslenP,
		   const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*---------------------------------------------------------------------------*/

void preKmp(const unsigned char* const x, uli m, long int kmpNext[]);

/*Knuth-Morris-Pratt algorithm*/
void findKMP(const unsigned char* const lpattern, uli lslenP,
		     const unsigned char* const ltext, uli lslenT, FILE* lfpL);

void preMp(const unsigned char* const x, uli m, long int mpNext[]);

/*Morris-Pratt algorithm*/
void findMP(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*Apostolico-Crochemore algorithm*/
void findAC(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*---------------------------------------------------------------------------*/

/*Not So Naive algorithm*/
void findNSN(const unsigned char* const lpattern, uli lslenP,
		 const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*---------------------------------------------------------------------------*/

#define REHASH(a, b, h) ((((h) - (a) * d) << 1) + (b))

/*Karp-Rabin algorithm*/
void findKR(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*---------------------------------------------------------------------------*/

unsigned int preSo(const unsigned char* const x,
			       uli m, uli S[]);

/*Shift Or algorithm*/
void findSO(const unsigned char* const lpattern, uli lslenP,
		const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*---------------------------------------------------------------------------*/

/*Brute Force algorithm*/
void findBF(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL);

void findBFO(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*---------------------------------------------------------------------------*/

void preBmBc(const unsigned char* const x, uli m, long int bmBc[]);

void suffixes(const unsigned char* const x, uli m, long int* suff);

void preBmGs(const unsigned char* const x, uli m, long int bmGs[]);

/*Boyer-Moore algorithm*/
void findBM(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*Turbo BM algorithm*/
void findTBM(const unsigned char* const lpattern, uli lslenP,
		     const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*Tuned Boyer-Moore algorithm*/
void findTnBM(const unsigned char* const lpattern, uli lslenP,
		      const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*Horspool algorithm*/
void findH(const unsigned char* const lpattern, uli lslenP,
		   const unsigned char* const ltext, uli lslenT, FILE* lfpL);

void preZtBc(const unsigned char* const x, uli m,
			 long int ztBc[maxAlf + 1][maxAlf + 1]);

/*Zhu-Takaoka algorithm*/
void findZT(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL);

void preQsBc(const unsigned char* const x, uli m, uli qsBc[]);

/*Quick Search algorithm*/
void findQS(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*---------------------------------------------------------------------------*/

/* returns a new data structure for
   a graph with v vertices and e edges */
Graph newGraph(long int v, long int e);

/* returns a new data structure for
   a automaton with v vertices and e edges */
Graph newAutomaton(long int v, long int e);

/* returns a new data structure for
   a suffix automaton with v vertices and e edges */
Graph newSuffixAutomaton(long int v, long int e);

/* returns a new vertex for graph g */
long int newVertex(Graph g);

/* returns a new data structure for
   a trie with v vertices and e edges */
Graph newTrie(long int v, long int e);

/* returns the initial vertex of graph g */
long int getInitial(Graph g);

/* returns true if vertex v is terminal in graph g */
BOOLean isTerminal(Graph g, long int v);

/* set vertex v to be terminal in graph g */
void setTerminal(Graph g, long int v);

/* returns the target of edge from vertex v
   labelled by character c in graph g */
long int getTarget(Graph g, long int v, unsigned char c);

/* add the edge from vertex v to vertex t
   labelled by character c in graph g */
void setTarget(Graph g, long int v, unsigned char c, long int t);

/* returns the suffix link of vertex v in graph g */
long int getSuffixLink(Graph g, long int v);

/* set the suffix link of vertex v
   to vertex s in graph g */
void setSuffixLink(Graph g, long int v, long int s);

/* returns the length of vertex v in graph g */
long int getLength(Graph g, long int v);

/* set the length of vertex v to integer ell in graph g */
void setLength(Graph g, long int v, long int ell);

/* returns the position of vertex v in graph g */
long int getPosition(Graph g, long int v);

/* set the length of vertex v to integer ell in graph g */
void setPosition(Graph g, long int v, long int p);

/* returns the shift of the edge from vertex v
   labelled by character c in graph g */
long int getShift(Graph g, long int v, unsigned char c);

/* set the shift of the edge from vertex v
   labelled by character c to integer s in graph g */
void setShift(Graph g, long int v, unsigned char c, long int s);

/* copies all the characteristics of vertex source
   to vertex target in graph g */
void copyVertex(Graph g, long int target, long int source);

void preAut(const unsigned char* const x, uli m, Graph aut);

/*Deterministic Finite Automaton algorithm*/
void findDFA(const unsigned char* const lpattern, uli lslenP,
		     const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*---------------------------------------------------------------------------*/

long int maxSuf(const unsigned char* const x, uli m, uli* p);

long int maxSufTilde(const unsigned char* const x, uli m, uli* p);

/*Two Way algorithm*/
void findTW(const unsigned char* const lpattern, uli lslenP,
		    const unsigned char* const ltext, uli lslenT, FILE* lfpL);

/*---------------------------------------------------------------------------*/

#endif

/*---------------------------------------------------------------------------*/
