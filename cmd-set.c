/**************************************************************
***************************************************************
*** 
***   cmd-set.c
***
***   Jason Olejarz
***   2011-01-26
***
***   This file contains commands for setting parameters.
***
***************************************************************
**************************************************************/

void cmd_iXmult()
{
	struct run_parameters *parameters;
	int *parameters_size;

	if (data_input(data, data_parameters, &parameters, &parameters_size, arg_short_int[0], data_num)==1) return result_error;

	set_init_X_mult(parameters, arg_short_int[1], arg_short_int[2], arg_short_int[3], arg_int[0]);

	return;
}

void cmd_iX()
{
	struct run_parameters *parameters;
	int *parameters_size;

	if (data_input(data, data_parameters, &parameters, &parameters_size, arg_short_int[0], data_num)==1) return result_error;

	set_init_X(parameters, arg_short_int[1], arg_int[0]);

	return;
}

void cmd_rnglcg()
{
	short int data_index=arg_short_int[0];
	
	struct rng_struct *rng_struct;
	int *rng_struct_size;
	
	// Allocate a block of memory to store info for the random number generator.
	if (data_output(data, data_parameters, &rng_struct, &rng_struct_size, sizeof(struct rng_struct), sizeof(int), data_index, data_num)==1) return result_error;
	
	rng_struct->rng_alloc=rng_alloc_lcg;
	rng_struct->rng_seed=rng_seed_lcg;
	rng_struct->rng_next=rng_next_lcg;

	rng_struct->rng_alloc(rng_struct);
	
	return;
}

void cmd_rngmt()
{
	short int data_index=arg_short_int[0];
	
	struct rng_struct *rng_struct;
	int *rng_struct_size;
	
	// Allocate a block of memory to store info for the random number generator.
	if (data_output(data, data_parameters, &rng_struct, &rng_struct_size, sizeof(struct rng_struct), sizeof(int), data_index, data_num)==1) return result_error;
	
	rng_struct->rng_alloc=rng_alloc_mt;
	rng_struct->rng_seed=rng_seed_mt;
	rng_struct->rng_next=rng_next_mt;

	rng_struct->rng_alloc(rng_struct);
	
	return;
}

void cmd_seed()
{
	set_seed(data[arg_short_int[0]], arg_double[0], arg_double[1]);

	return;
}

void cmd_set()
{
	short int data_index=arg_short_int[0];
	short int data_index_rng=arg_short_int[1];
	double maxtime=arg_double[0];
	int N=arg_int[0];
	double eta=arg_double[1];
	double phi=arg_double[2];
	double pDXZ=arg_double[3];
	double mu=arg_double[4];
	double w=arg_double[5];
	double fDX=arg_double[6];
	double fDZ=arg_double[7];
	double fYX=arg_double[8];
	double fYZ=arg_double[9];
	double gXX=arg_double[10];
	double gXZ=arg_double[11];
	double gZZ=arg_double[12];
	short int repopulation=arg_short_int[2];
	
	int i;

	static struct run_parameters *parameters;
	static int *parameters_size;
	
	// Allocate a block of memory to store parameter values.
	if (data_output(data, data_parameters, &parameters, &parameters_size, sizeof(struct run_parameters), sizeof(int), data_index, data_num)==1) return result_error;

	// Fill in the parameters.
	parameters->rng_struct=data[data_index_rng];
	parameters->maxtime=maxtime;
	parameters->N=N;
	parameters->eta=eta;
	parameters->phi=phi;
	parameters->pDXZ=pDXZ;
	parameters->mu=mu;
	parameters->w=w;
	parameters->fDX=fDX;
	parameters->fDZ=fDZ;
	parameters->fYX=fYX;
	parameters->fYZ=fYZ;
	parameters->gXX=gXX;
	parameters->gXZ=gXZ;
	parameters->gZZ=gZZ;
	parameters->repopulation=repopulation;

	parameters->number_of_variables=7;

	// Allocate memory.
	parameters->X_initial=(double*)malloc (sizeof(double)*7*N);
	parameters->X=(double*)malloc (sizeof(double)*11*N);
	parameters->X_initial_int=(int*)malloc (sizeof(int)*7*N);
	parameters->X_int=(int*)malloc (sizeof(int)*11*N);
	parameters->X_total_int=(int*)malloc (sizeof(int)*N);
	if (N>1)
	{
		parameters->u=(double*)malloc (sizeof(double)*N*(N-1));
		parameters->u_sum=(double*)malloc (sizeof(double)*N);
	}

	for (i=0; i<N; i++)
	{
		*(parameters->X_total_int+i)=0;
	}

	for (i=0; i<7*N; i++)
	{
		*(parameters->X_initial_int+i)=0;
		*(parameters->X_initial+i)=0;
	}

	for (i=0; i<11*N; i++)
	{
		*(parameters->X_int+i)=0;
		*(parameters->X+i)=0;
	}

	return;
}

void cmd_settsc()
{
	set_settsc(data[arg_short_int[0]]);
	return;
}

void cmd_ucomp()
{
	struct run_parameters *parameters;
	int *parameters_size;

	if (data_input(data, data_parameters, &parameters, &parameters_size, arg_short_int[0], data_num)==1) return result_error;

	int i, j;

	for (i=0; i<(parameters->N); i++)
	{
		for (j=0; j<(parameters->N)-1; j++)
		{
			*(parameters->u+((parameters->N)-1)*i+j)=arg_double[0];
		}
		*(parameters->u_sum+i)=((parameters->N)-1)*arg_double[0];
	}

	return;
}

void cmd_urect()
{
	struct run_parameters *parameters;
	int *parameters_size;

	if (data_input(data, data_parameters, &parameters, &parameters_size, arg_short_int[0], data_num)==1) return result_error;

	int nx=arg_int[0];
	int ny=arg_int[1];

	int x, y;

	for (x=0; x<(nx*ny)*(nx*ny-1); x++)
	{
		*(parameters->u+x)=0;
	}

	for (y=0; y<ny; y++)
	{
		for (x=0; x<nx; x++)
		{
			*(parameters->u_sum+nx*y+x)=0;

			if (x>0) {*(parameters->u+(nx*ny-1)*(nx*y+x)+nx*y+(x-1))=arg_double[0]; *(parameters->u_sum+nx*y+x)+=arg_double[0];}
			if (x<nx-1) {*(parameters->u+(nx*ny-1)*(nx*y+x)+nx*y+(x+1)-1)=arg_double[0]; *(parameters->u_sum+nx*y+x)+=arg_double[0];}
			if (y>0) {*(parameters->u+(nx*ny-1)*(nx*y+x)+nx*(y-1)+x)=arg_double[0]; *(parameters->u_sum+nx*y+x)+=arg_double[0];}
			if (y<ny-1) {*(parameters->u+(nx*ny-1)*(nx*y+x)+nx*(y+1)+x-1)=arg_double[0]; *(parameters->u_sum+nx*y+x)+=arg_double[0];}
		}
	}

	return;
}

void cmd_ustar()
{
	struct run_parameters *parameters;
	int *parameters_size;

	if (data_input(data, data_parameters, &parameters, &parameters_size, arg_short_int[0], data_num)==1) return result_error;

	int nx=arg_int[0];

	int x;

	for (x=0; x<nx*(nx-1); x++)
	{
		*(parameters->u+x)=0;
	}

	for (x=0; x<nx-1; x++)
	{
		*(parameters->u_sum+x)=0;

		if (x>0) {*(parameters->u+(nx-1)*x+(x-1))=arg_double[0]; *(parameters->u_sum+x)+=arg_double[0];}
		if (x<nx-2) {*(parameters->u+(nx-1)*x+(x+1)-1)=arg_double[0]; *(parameters->u_sum+x)+=arg_double[0];}
	}

	*(parameters->u_sum+(nx-1))=0;

	{*(parameters->u+(nx-1)*(nx-2)+((nx-2)+1)-1)=arg_double[1]; *(parameters->u_sum+(nx-2))+=arg_double[1];}
	{*(parameters->u+(nx-1)*(nx-1)+((nx-1)-1))=arg_double[1]; *(parameters->u_sum+(nx-1))+=arg_double[1];}

	return;
}

void cmd_uexp()
{
	struct run_parameters *parameters;
	int *parameters_size;

	if (data_input(data, data_parameters, &parameters, &parameters_size, arg_short_int[0], data_num)==1) return result_error;

	int nx=arg_int[0];
	int ny=arg_int[1];

	int i, j, x, y;

	for (j=0; j<ny; j++)
	{
		for (i=0; i<nx; i++)
		{
			*(parameters->u_sum+nx*j+i)=0;

			for (y=0; y<ny; y++)
			{
				for (x=0; x<nx; x++)
				{
					if (y!=j && x!=i)
					{
						if (nx*j+i>nx*y+x) *(parameters->u+(nx*ny-1)*(nx*j+i)+(nx*y+x))=arg_double[0]*exp(-arg_double[1]*sqrt((y-j)*(y-j)+(x-i)*(x-i)));
						else *(parameters->u+(nx*ny-1)*(nx*j+i)+(nx*y+x)-1)=arg_double[0]*exp(-arg_double[1]*sqrt((y-j)*(y-j)+(x-i)*(x-i)));

						*(parameters->u_sum+nx*j+i)+=arg_double[0]*exp(-arg_double[1]*sqrt((y-j)*(y-j)+(x-i)*(x-i)));
					}
				}
			}
		}
	}

	return;
}

void cmd_u2()
{
	struct run_parameters *parameters;
	int *parameters_size;

	if (data_input(data, data_parameters, &parameters, &parameters_size, arg_short_int[0], data_num)==1) return result_error;

	*(parameters->u+0)=arg_double[0];
	*(parameters->u+1)=arg_double[1];

	return;
}

void cmd_u3()
{
	struct run_parameters *parameters;
	int *parameters_size;

	if (data_input(data, data_parameters, &parameters, &parameters_size, arg_short_int[0], data_num)==1) return result_error;

	*(parameters->u+0)=arg_double[0];
	*(parameters->u+1)=arg_double[1];
	*(parameters->u+2)=arg_double[2];
	*(parameters->u+3)=arg_double[3];
	*(parameters->u+4)=arg_double[4];
	*(parameters->u+5)=arg_double[5];

	return;
}

void cmd_u4()
{
	struct run_parameters *parameters;
	int *parameters_size;

	if (data_input(data, data_parameters, &parameters, &parameters_size, arg_short_int[0], data_num)==1) return result_error;

	*(parameters->u+ 0)=arg_double[ 0];
	*(parameters->u+ 1)=arg_double[ 1];
	*(parameters->u+ 2)=arg_double[ 2];
	*(parameters->u+ 3)=arg_double[ 3];
	*(parameters->u+ 4)=arg_double[ 4];
	*(parameters->u+ 5)=arg_double[ 5];
	*(parameters->u+ 6)=arg_double[ 6];
	*(parameters->u+ 7)=arg_double[ 7];
	*(parameters->u+ 8)=arg_double[ 8];
	*(parameters->u+ 9)=arg_double[ 9];
	*(parameters->u+10)=arg_double[10];
	*(parameters->u+11)=arg_double[11];

	return;
}

void cmd_u5()
{
	struct run_parameters *parameters;
	int *parameters_size;

	if (data_input(data, data_parameters, &parameters, &parameters_size, arg_short_int[0], data_num)==1) return result_error;

	*(parameters->u+ 0)=arg_double[ 0];
	*(parameters->u+ 1)=arg_double[ 1];
	*(parameters->u+ 2)=arg_double[ 2];
	*(parameters->u+ 3)=arg_double[ 3];
	*(parameters->u+ 4)=arg_double[ 4];
	*(parameters->u+ 5)=arg_double[ 5];
	*(parameters->u+ 6)=arg_double[ 6];
	*(parameters->u+ 7)=arg_double[ 7];
	*(parameters->u+ 8)=arg_double[ 8];
	*(parameters->u+ 9)=arg_double[ 9];
	*(parameters->u+10)=arg_double[10];
	*(parameters->u+11)=arg_double[11];
	*(parameters->u+12)=arg_double[12];
	*(parameters->u+13)=arg_double[13];
	*(parameters->u+14)=arg_double[14];
	*(parameters->u+15)=arg_double[15];
	*(parameters->u+16)=arg_double[16];
	*(parameters->u+17)=arg_double[17];
	*(parameters->u+18)=arg_double[18];
	*(parameters->u+19)=arg_double[19];

	return;
}

