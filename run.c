/**************************************************************
***************************************************************
*** 
***   run.c
***
***   Jason Olejarz
***   2011-01-25
***
***   This file contains the core calculations for evolving the interfaces.
***
***************************************************************
**************************************************************/

#include "includes.h"

short int run (short int (*step[])(), short int step_size, void *data[], void *data_parameters[], short int data_size, struct run_parameters *parameters)
{
	// Load all parameter values.
	struct rng_struct *rng_struct=parameters->rng_struct;
	int *X_total_int=parameters->X_total_int;
	int *X_initial_int=parameters->X_initial_int;
	int *X_int=parameters->X_int;
	double *X_initial=parameters->X_initial;
	double *X=parameters->X;
	int N=parameters->N;
	double eta=parameters->eta;
	double phi=parameters->phi;
	double pDXZ=parameters->pDXZ;
	double mu=parameters->mu;
	double w=parameters->w;
	double fDX=parameters->fDX;
	double fDZ=parameters->fDZ;
	double fYX=parameters->fYX;
	double fYZ=parameters->fYZ;
	double gXX=parameters->gXX;
	double gXZ=parameters->gXZ;
	double gZZ=parameters->gZZ;
	double *u=parameters->u;
	double *u_sum=parameters->u_sum;
	short int repopulation=parameters->repopulation;

	short int result, step_index=0, evolve_continue=1;

        double random_number;

	int i, j, k;

	int n;

	i=parameters->number_of_variables;
	if (3*N>i) i=3*N;

	double *prob=(double*)malloc (sizeof(double)*i);

	double prob_sum;

	int genotype_1, genotype_2;
	int allele_1, allele_2;

	int population_1_not_extinct, population_2_not_extinct, population_3_not_extinct, population_4_not_extinct, population_5_not_extinct;

	population_1_not_extinct=1;
	population_2_not_extinct=1;
	population_3_not_extinct=1;
	population_4_not_extinct=1;
	population_5_not_extinct=1;

	memcpy (X_int, X_initial_int, sizeof(int)*7*N);
	memcpy (X, X_initial, sizeof(double)*7*N);

	memset (X_int+7*N, 0, sizeof(int)*4*N);
	memset (X+7*N, 0, sizeof(double)*4*N);

	parameters->X_all=0;

	for (i=0; i<N; i++)
	{
		*(X_total_int+i)=0;
	}

	for (i=0; i<7*N; i++)
	{
		(parameters->X_all)+=*(X_int+i);
		*(X_total_int+i/7)+=*(X_int+i);

		if (i%7==0) {*(X_int+7*N+4*(i/7)+0)+=*(X_int+i); *(X_int+7*N+4*(i/7)+2)+=*(X_int+i);}
		else if (i%7==1) {*(X_int+7*N+4*(i/7)+0)+=*(X_int+i); *(X_int+7*N+4*(i/7)+3)+=*(X_int+i);}
		else if (i%7==2) {*(X_int+7*N+4*(i/7)+1)+=*(X_int+i); *(X_int+7*N+4*(i/7)+2)+=*(X_int+i);}
		else if (i%7==3) {*(X_int+7*N+4*(i/7)+1)+=*(X_int+i); *(X_int+7*N+4*(i/7)+3)+=*(X_int+i);}
		else if (i%7==4) *(X_int+7*N+4*(i/7)+2)+=2*(*(X_int+i));
		else if (i%7==5) {*(X_int+7*N+4*(i/7)+2)+=*(X_int+i); *(X_int+7*N+4*(i/7)+3)+=*(X_int+i);}
		else *(X_int+7*N+4*(i/7)+3)+=2*(*(X_int+i));
	}

	for (i=0; i<4*N; i++)
	{
		*(X+7*N+i)=(double)(*(X_int+7*N+i));
	}

	parameters->resistance_1=0;
	parameters->resistance_2=0;

	parameters->population_1_extinct=0;
	if (N>=2) parameters->population_2_extinct=0;
	if (N>=3) parameters->population_3_extinct=0;
	if (N>=4) parameters->population_4_extinct=0;
	if (N>=5) parameters->population_5_extinct=0;

	parameters->steps=0;
	parameters->time=0;
	
	// Send 'begin' to all functions in 'step'.
	if (step!=0)
	{
		while (step[step_index]!=0 && step_index<step_size)
		{
			if (step[step_index++](command_begin, 0, data, data_parameters, data_size, parameters)==result_error) return result_error;
		}
		step_index=0;
	}

	// If 'Nt' is zero, then there is nothing to do.
//	if (parameters->maxsteps==0) return 0;
	
	do
	{
		pDXZ=parameters->pDXZ;

		parameters->new_resistance_1=0;
		parameters->new_resistance_2=0;

		for (i=0; i<N; i++)
		{
			*(prob+3*i) = (fDX*(*(X_int+7*i))+fDZ*(*(X_int+7*i+1))+fYX*(*(X_int+7*i+2))+fYZ*(*(X_int+7*i+3))) * (gXX*(*(X_int+7*i+4))+gXZ*(*(X_int+7*i+5))+gZZ*(*(X_int+7*i+6))) / ( 1 + eta * ( fDX*(*(X_int+7*i))+fDZ*(*(X_int+7*i+1))+fYX*(*(X_int+7*i+2))+fYZ*(*(X_int+7*i+3)) ) * ( gXX*(*(X_int+7*i+4))+gXZ*(*(X_int+7*i+5))+gZZ*(*(X_int+7*i+6)) ) ) ;

			*(prob+3*i+1) = phi * ( (*(X_int+7*i))+(*(X_int+7*i+1))+(*(X_int+7*i+2))+(*(X_int+7*i+3))+(*(X_int+7*i+4))+(*(X_int+7*i+5))+(*(X_int+7*i+6)) ) ;

			*(prob+3*i+2) = *(u_sum+i) * ( (*(X_int+7*i))+(*(X_int+7*i+1))+(*(X_int+7*i+2))+(*(X_int+7*i+3))+(*(X_int+7*i+4))+(*(X_int+7*i+5))+(*(X_int+7*i+6)) ) ;
		}

		// Increment the number of steps.
		(parameters->steps)++;

		prob_sum=0;
		for (k=0; k<3*N; k++)
		{
			prob_sum+=*(prob+k);
		}

		// Update the time elapsed.
		(parameters->time)+=1/prob_sum;

		for (i=1; i<3*N; i++)
		{
			*(prob+i)+=*(prob+i-1);
		}

		for (i=0; i<3*N-1; i++)
		{
			*(prob+i)=*(prob+i)/(*(prob+3*N-1));
		}
		*(prob+3*N-1)=1;

		rng_struct->rng_next(rng_struct);
		random_number=(rng_struct->current_double);

		for (i=0; i<3*N; i++)
		{
			if (*(prob+i)>random_number) break;
		}

		n=i/3;

		if (i%3==0)
		{
			*(prob+0) = fDX*(*(X_int+7*n+0)) ;
			*(prob+1) = fDZ*(*(X_int+7*n+1)) ;
			*(prob+2) = fYX*(*(X_int+7*n+2)) ;
			*(prob+3) = fYZ*(*(X_int+7*n+3)) ;

			for (k=1; k<4; k++)
			{
				*(prob+k)+=*(prob+k-1);
			}

			for (k=0; k<3; k++)
			{
				*(prob+k)=*(prob+k)/(*(prob+3));
			}
			*(prob+3)=1;

			rng_struct->rng_next(rng_struct);
			random_number=(rng_struct->current_double);

			for (genotype_1=0; genotype_1<4; genotype_1++)
			{
				if (*(prob+genotype_1)>random_number) break;
			}

			*(prob+0) = gXX*(*(X_int+7*n+4)) ;
			*(prob+1) = gXZ*(*(X_int+7*n+5)) ;
			*(prob+2) = gZZ*(*(X_int+7*n+6)) ;

			for (k=1; k<3; k++)
			{
				*(prob+k)+=*(prob+k-1);
			}

			for (k=0; k<2; k++)
			{
				*(prob+k)=*(prob+k)/(*(prob+2));
			}
			*(prob+2)=1;

			rng_struct->rng_next(rng_struct);
			random_number=(rng_struct->current_double);

			for (genotype_2=0; genotype_2<3; genotype_2++)
			{
				if (*(prob+genotype_2)>random_number) break;
			}
			genotype_2+=4;

			rng_struct->rng_next(rng_struct);
			random_number=(rng_struct->current_double);

			if (genotype_1==0)
			{
				if (random_number<0.5+0.5*(1-pDXZ)) allele_1=0;
				else {allele_1=3; parameters->new_resistance_1=1;}

				parameters->resistance_1+=0.5;
			}
			else if (genotype_1==1)
			{
				if (random_number<0.5) allele_1=0;
				else allele_1=3;
			}
			else if (genotype_1==2)
			{
				if (random_number<0.5) allele_1=1;
				else
				{
					rng_struct->rng_next(rng_struct);
					random_number=(rng_struct->current_double);

					if (random_number<mu) {allele_1=3; parameters->new_resistance_2=1;}
					else allele_1=2;
				}

				parameters->resistance_2+=0.5;
			}
			else
			{
				if (random_number<0.5) allele_1=1;
				else allele_1=3;
			}

			rng_struct->rng_next(rng_struct);
			random_number=(rng_struct->current_double);

			if (genotype_2==4)
			{
				rng_struct->rng_next(rng_struct);
				random_number=(rng_struct->current_double);

				if (random_number<mu) {allele_2=3; parameters->new_resistance_2=1;}
				else allele_2=2;

				parameters->resistance_2+=1;
			}
			else if (genotype_2==5)
			{
				if (random_number<0.5)
				{
					rng_struct->rng_next(rng_struct);
					random_number=(rng_struct->current_double);

					if (random_number<mu) {allele_2=3; parameters->new_resistance_2=1;}
					else allele_2=2;
				}
				else allele_2=3;

				parameters->resistance_2+=0.5;
			}
			else allele_2=3;

			if (allele_1==0 && allele_2==2) {(*(X_int+7*n+0))++; (*(X+7*n+0))=(double)(*(X_int+7*n+0));}
			else if (allele_1==0 && allele_2==3) {(*(X_int+7*n+1))++; (*(X+7*n+1))=(double)(*(X_int+7*n+1));}
			else if (allele_1==1 && allele_2==2) {(*(X_int+7*n+2))++; (*(X+7*n+2))=(double)(*(X_int+7*n+2));}
			else if (allele_1==1 && allele_2==3) {(*(X_int+7*n+3))++; (*(X+7*n+3))=(double)(*(X_int+7*n+3));}
			else if (allele_1==2 && allele_2==2) {(*(X_int+7*n+4))++; (*(X+7*n+4))=(double)(*(X_int+7*n+4));}
			else if ((allele_1==2 && allele_2==3) || (allele_1==3 && allele_2==2)) {(*(X_int+7*n+5))++; (*(X+7*n+5))=(double)(*(X_int+7*n+5));}
			else {(*(X_int+7*n+6))++; (*(X+7*n+6))=(double)(*(X_int+7*n+6));}

			(*(X_total_int+n))++;

			(parameters->X_all)++;

			if (allele_1==0) (*(X_int+7*N+4*n+0))++;
			else if (allele_1==1) (*(X_int+7*N+4*n+1))++;
			else if (allele_1==2) (*(X_int+7*N+4*n+2))++;
			else (*(X_int+7*N+4*n+3))++;

			if (allele_2==2) (*(X_int+7*N+4*n+2))++;
			else (*(X_int+7*N+4*n+3))++;

			*(X+7*N+4*n+0)=(double)(*(X_int+7*N+4*n+0));
			*(X+7*N+4*n+1)=(double)(*(X_int+7*N+4*n+1));
			*(X+7*N+4*n+2)=(double)(*(X_int+7*N+4*n+2));
			*(X+7*N+4*n+3)=(double)(*(X_int+7*N+4*n+3));
		}
		else if (i%3==1)
		{
			*(prob+0) = (*(X_int+7*n+0)) ;
			*(prob+1) = (*(X_int+7*n+1)) ;
			*(prob+2) = (*(X_int+7*n+2)) ;
			*(prob+3) = (*(X_int+7*n+3)) ;
			*(prob+4) = (*(X_int+7*n+4)) ;
			*(prob+5) = (*(X_int+7*n+5)) ;
			*(prob+6) = (*(X_int+7*n+6)) ;

			for (k=1; k<7; k++)
			{
				*(prob+k)+=*(prob+k-1);
			}

			for (k=0; k<6; k++)
			{
				*(prob+k)=*(prob+k)/(*(prob+6));
			}
			*(prob+6)=1;

			rng_struct->rng_next(rng_struct);
			random_number=(rng_struct->current_double);

			for (k=0; k<7; k++)
			{
				if (*(prob+k)>random_number) break;
			}

			{(*(X_int+7*n+k))--; (*(X+7*n+k))=(double)(*(X_int+7*n+k));}

			(*(X_total_int+n))--;

			(parameters->X_all)--;

			if (k==0) {(*(X_int+7*N+4*n+0))--; (*(X_int+7*N+4*n+2))--;}
			else if (k==1) {(*(X_int+7*N+4*n+0))--; (*(X_int+7*N+4*n+3))--;}
			else if (k==2) {(*(X_int+7*N+4*n+1))--; (*(X_int+7*N+4*n+2))--;}
			else if (k==3) {(*(X_int+7*N+4*n+1))--; (*(X_int+7*N+4*n+3))--;}
			else if (k==4) *(X_int+7*N+4*n+2)-=2;
			else if (k==5) {(*(X_int+7*N+4*n+2))--; (*(X_int+7*N+4*n+3))--;}
			else *(X_int+7*N+4*n+3)-=2;

			*(X+7*N+4*n+0)=(double)(*(X_int+7*N+4*n+0));
			*(X+7*N+4*n+1)=(double)(*(X_int+7*N+4*n+1));
			*(X+7*N+4*n+2)=(double)(*(X_int+7*N+4*n+2));
			*(X+7*N+4*n+3)=(double)(*(X_int+7*N+4*n+3));
		}
		else
		{
			for (j=0; j<N-1; j++)
			{
				*(prob+j)=*(u+(N-1)*n+j);
			}

			for (j=1; j<N-1; j++)
			{
				*(prob+j)+=*(prob+j-1);
			}

			for (j=0; j<N-2; j++)
			{
				*(prob+j)=*(prob+j)/(*(prob+N-2));
			}
			*(prob+N-2)=1;

			rng_struct->rng_next(rng_struct);
			random_number=(rng_struct->current_double);

			for (j=0; j<N-1; j++)
			{
				if (*(prob+j)>random_number) break;
			}

			if (j>=n) j++;

			if (repopulation>0 || *(X_total_int+j)>0)
			{
				do
				{
					*(prob+0) = (*(X_int+7*n+0)) ;
					*(prob+1) = (*(X_int+7*n+1)) ;
					*(prob+2) = (*(X_int+7*n+2)) ;
					*(prob+3) = (*(X_int+7*n+3)) ;
					*(prob+4) = (*(X_int+7*n+4)) ;
					*(prob+5) = (*(X_int+7*n+5)) ;
					*(prob+6) = (*(X_int+7*n+6)) ;

					for (k=1; k<7; k++)
					{
						*(prob+k)+=*(prob+k-1);
					}

					for (k=0; k<6; k++)
					{
						*(prob+k)=*(prob+k)/(*(prob+6));
					}
					*(prob+6)=1;

					rng_struct->rng_next(rng_struct);
					random_number=(rng_struct->current_double);

					for (k=0; k<7; k++)
					{
						if (*(prob+k)>random_number) break;
					}

					{(*(X_int+7*n+k))--; (*(X+7*n+k))=(double)(*(X_int+7*n+k));}
					{(*(X_int+7*j+k))++; (*(X+7*j+k))=(double)(*(X_int+7*j+k));}

					(*(X_total_int+n))--;
					(*(X_total_int+j))++;

					if (k==0)
					{
						(*(X_int+7*N+4*n+0))--;
						(*(X_int+7*N+4*n+2))--;
						(*(X_int+7*N+4*j+0))++;
						(*(X_int+7*N+4*j+2))++;
					}
					else if (k==1)
					{
						(*(X_int+7*N+4*n+0))--; 
						(*(X_int+7*N+4*n+3))--;
						(*(X_int+7*N+4*j+0))++; 
						(*(X_int+7*N+4*j+3))++;
					}
					else if (k==2)
					{
						(*(X_int+7*N+4*n+1))--;
						(*(X_int+7*N+4*n+2))--;
						(*(X_int+7*N+4*j+1))++;
						(*(X_int+7*N+4*j+2))++;
					}
					else if (k==3)
					{
						(*(X_int+7*N+4*n+1))--;
						(*(X_int+7*N+4*n+3))--;
						(*(X_int+7*N+4*j+1))++;
						(*(X_int+7*N+4*j+3))++;
					}
					else if (k==4)
					{
						*(X_int+7*N+4*n+2)-=2;
						*(X_int+7*N+4*j+2)+=2;
					}
					else if (k==5)
					{
						(*(X_int+7*N+4*n+2))--;
						(*(X_int+7*N+4*n+3))--;
						(*(X_int+7*N+4*j+2))++;
						(*(X_int+7*N+4*j+3))++;
					}
					else
					{
						*(X_int+7*N+4*n+3)-=2;
						*(X_int+7*N+4*j+3)+=2;
					}

					*(X+7*N+4*n+0)=(double)(*(X_int+7*N+4*n+0));
					*(X+7*N+4*n+1)=(double)(*(X_int+7*N+4*n+1));
					*(X+7*N+4*n+2)=(double)(*(X_int+7*N+4*n+2));

					*(X+7*N+4*j+0)=(double)(*(X_int+7*N+4*j+0));
					*(X+7*N+4*j+1)=(double)(*(X_int+7*N+4*j+1));
					*(X+7*N+4*j+2)=(double)(*(X_int+7*N+4*j+2));

					rng_struct->rng_next(rng_struct);
					random_number=(rng_struct->current_double);
				}
				while (random_number<w && *(X_total_int+n)>0);
			}
		}

		if (population_1_not_extinct==1 && *X_total_int==0)
		{
			(parameters->population_1_extinct)++;
			population_1_not_extinct=0;
		}
		else if (population_1_not_extinct==0 && *X_total_int>0)
		{
			population_1_not_extinct=1;
		}

		if (N>=2 && population_2_not_extinct==1 && *(X_total_int+1)==0)
		{
			(parameters->population_2_extinct)++;
			population_2_not_extinct=0;
		}
		else if (N>=2 && population_2_not_extinct==0 && *(X_total_int+1)>0)
		{
			population_2_not_extinct=1;
		}

		if (N>=3 && population_3_not_extinct==1 && *(X_total_int+2)==0)
		{
			(parameters->population_3_extinct)++;
			population_3_not_extinct=0;
		}
		else if (N>=3 && population_3_not_extinct==0 && *(X_total_int+2)>0)
		{
			population_3_not_extinct=1;
		}

		if (N>=4 && population_4_not_extinct==1 && *(X_total_int+3)==0)
		{
			(parameters->population_4_extinct)++;
			population_4_not_extinct=0;
		}
		else if (N>=4 && population_4_not_extinct==0 && *(X_total_int+3)>0)
		{
			population_4_not_extinct=1;
		}

		if (N>=5 && population_5_not_extinct==1 && *(X_total_int+4)==0)
		{
			(parameters->population_5_extinct)++;
			population_5_not_extinct=0;
		}
		else if (N>=5 && population_5_not_extinct==0 && *(X_total_int+4)>0)
		{
			population_5_not_extinct=1;
		}

		// Do intermediate processing.
		if (step!=0)
		{
			while (step[step_index]!=0 && step_index<step_size)
			{
				result=step[step_index++](command_run, 0, data, data_parameters, data_size, parameters);
				if (result==result_error) return result_error;
				else if (result==result_done) {evolve_continue=0; break;}
			}
			step_index=0;
		}
	}
	while (evolve_continue==1 && parameters->time<parameters->maxtime && parameters->X_all>0);

	// Send 'end' to all functions in 'step'.
	if (step!=0)
	{
		while (step[step_index]!=0 && step_index<step_size)
		{
			if (step[step_index++](command_end, 0, data, data_parameters, data_size, parameters)==result_error) return result_error;
		}
		step_index=0;
	}

	return 0;
}
