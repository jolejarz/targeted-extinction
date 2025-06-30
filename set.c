/**************************************************************
***************************************************************
*** 
***   set.c
***
***   Jason Olejarz
***   2011-01-26
***
***   This file contains the routines used to set the parameters for 'evolve'.
***
***************************************************************
**************************************************************/

#include "includes.h"

short int set_init_X_mult(struct run_parameters *parameters, short int starting_X, short int multiple, short int number, int amount_X)
{
	int i;
	
	for (i=0; i<number; i++)
	{
		*(parameters->X_initial_int+starting_X+i*multiple)=amount_X;
		*(parameters->X_initial+starting_X+i*multiple)=(double)amount_X;
	}

	return set_ok;
}

short int set_init_X(struct run_parameters *parameters, short int X, int amount_X)
{
	int i;
	
	*(parameters->X_initial_int+X)=amount_X;
	*(parameters->X_initial+X)=(double)amount_X;

	return set_ok;
}

short int set_seed(struct rng_struct *rng_struct, double seed_low, double seed_high)
{
	unsigned long int seed;
	
	seed=(unsigned long int)seed_high;
	seed*=(unsigned long int)pow(2,16);
	seed*=(unsigned long int)pow(2,16);
	seed+=(unsigned long int)seed_low;
	rng_struct->rng_seed(rng_struct, seed);

	return set_ok;
}

short int set_settsc(struct rng_struct *rng_struct)
{
	unsigned int low, high;
	unsigned long int seed;
	
	asm ("rdtsc" : "=a" (low), "=d" (high));
	seed=(unsigned long int)high;
	seed*=(unsigned long int)pow(2,16);
	seed*=(unsigned long int)pow(2,16);
	seed+=(unsigned long int)low;
	rng_struct->rng_seed(rng_struct, seed);
	
	return set_ok;
}

