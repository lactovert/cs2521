// gen.c
// program for generating sortable data

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 10000000

#define swap(A,I,J)  { int tmp; tmp = A[(I)]; A[(I)] = A[(J)]; A[(J)] = tmp; }

char *progName;
void giveUp(char *);
void randString(char *, int);

int main(int argc, char **argv)
{
	int  N = 0;  // number of values of data produced
	int  order;  // ordering of data
	int  S = 0;  // seed for random #'s
	int  i;      // index
	int *values;
	progName = argv[0];

	if (argc < 3) { giveUp("Not enough arguments"); }

	// how much data
	// N = atoi(argv[1]);
	N = atoi(argv[1]);
	if (N < 2) { giveUp("Too few values\n"); }
	if (N > MAXLINES-1) { giveUp("Too many values"); }

	// determine ordering
	switch (argv[2][0]) {
	case 'A': case 'a': order = 'A';  break;
	case 'D': case 'd': order = 'D'; break;
	case 'R': case 'r': order = 'R'; break;
	default: giveUp("Invalid ordering"); break;
	}

	// set seed
	if (argc == 4 && order == 'R') {
		switch (order) {
		case 'A': S = 1; break;
		case 'D': S = N+1; break;
		case 'R': S = atoi(argv[3]); srand(S); break;
		}
	}

	if ((values = malloc(N*sizeof(int))) == NULL)
		giveUp("Can't allocate values[]");
	for (i = 0; i < N; i++) values[i] = i;
	switch (order) {
	case 'D':
		for (i = 0; i < N/2; i++)
			swap(values, i, N-i-1);
		break;
	case 'A':
		/* nothing to do */
		break;
	case 'R':
		for (i = 0; i < N; i++) {
			int j = rand()%N;
			swap(values,i,j);
		}
		break;
	}
        printf("%d\n",N);
	for (i = 0; i < N; i++)
		printf("%d\n",values[i]);

	exit(0);
}

void randString(char *ss, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		ss[i] = 'a' + rand()%26;
	}
	ss[i] = '\0';
}

void giveUp(char *message)
{
	fprintf(stderr, "%s\n", message);
	fprintf(stderr, "Usage: %s  N  A|D|R  [S]\n", progName);
	fprintf(stderr, "       N = number of values\n");
	fprintf(stderr, "       A|D|R = Ascending|Descending|Random\n");
	fprintf(stderr, "       S = seed for Random\n");
	exit(1); //don't distinguish different errors
}
