/**************************************************************
***************************************************************
*** 
***   set.h
***
***   Jason Olejarz
***   2011-01-26
***
***   This is the header file for set.c.
***
***************************************************************
**************************************************************/

enum {set_error, set_ok};

short int set_init_X_mult(struct run_parameters *parameters, short int starting_X, short int multiple, short int number, int amount_X);
short int set_init_X(struct run_parameters *parameters, short int X, int amount_X);
short int set_seed(struct rng_struct *rng_struct, double seed_low, double seed_high);
short int set_settsc(struct rng_struct *rng_struct);

