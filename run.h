/**************************************************************
***************************************************************
*** 
***   run.h
***
***   Jason Olejarz
***   2011-01-26
***
***   This is the header file for run.c.
***
***************************************************************
**************************************************************/

struct run_parameters
{
	struct rng_struct *rng_struct;
	unsigned long int maxsteps;
	double maxtime;
	double delta_t;
	unsigned long int steps;
	double time;
	int Nx;
	double dx;
	double D;
	short int repopulation;
	int N;
	double mu;
	double w;
	double *u;
	double *u_sum;
	double eta;
	double phi;
	int number_of_variables;
	double pDWR;
	double pDXZ;
	double fDX;
	double fDZ;
	double fYX;
	double fYZ;
	double fXX;
	double fXZ;
	double fZZ;
	double gXX;
	double gXZ;
	double gZZ;
	double fDD;
	double fDW;
	double fDR;
	double fWW;
	double fWR;
	double fRR;
	double gDW;
	double gDR;
	double gWW;
	double gWR;
	double gRR;
	double resistance_1;
	double resistance_2;
	int new_resistance_1;
	int new_resistance_2;
	int population_1_extinct;
	int population_2_extinct;
	int population_3_extinct;
	int population_4_extinct;
	int population_5_extinct;
	int X_all_moves;
	int X_all;
	int *X_total_int;
	int *X_initial_int;
	int *X_int;
	double *X_initial;
	double *X;
	double *X_new;
	double *RK_k_current;
	double *RK_k;
};

short int run (short int (*step[])(), short int step_size, void *data[], void *data_parameters[], short int data_size, struct run_parameters *parameters);
