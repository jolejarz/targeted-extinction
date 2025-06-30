/**************************************************************
***************************************************************
*** 
***   save.c
***
***   Jason Olejarz
***   2010-07-21
***
***   This file contains the routines used by 'calc' to save data after each run of 'evolve'.
***
***************************************************************
**************************************************************/

#include "includes.h"

short int save_final_steps(short int command, struct save_final_steps_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct save_final_steps_data cmd_data;
	
	static double *final_steps;

	static struct run_parameters *parameters;
	static int *parameters_size;
	
	static struct save_final_steps_parameters *final_steps_parameters;

	static int i, mag;
	
	switch (command)
	{
		case command_info: {printf("save_final_steps\n"); return result_continue;}
		case command_insert:
		{
			memcpy(&cmd_data, command_data, sizeof(struct save_final_steps_data));
			
			return result_continue;
		}
		case command_begin:
		{
			if (data_input(data, data_parameters, &parameters, &parameters_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &final_steps, &final_steps_parameters, cmd_data.size*sizeof(double), sizeof(struct save_final_steps_parameters), cmd_data.data_index_final_steps, data_size)==1) return result_error;
			
			final_steps_parameters->index=0;
			final_steps_parameters->size=0;
			
			return result_continue;
		}
		case command_run:
		{
			*(final_steps+(final_steps_parameters->index))=(double)(parameters->steps);
			
			(final_steps_parameters->index)++;
			final_steps_parameters->size+=sizeof(double);

			return result_continue;
		}
		default: return result_continue;
	}
}

short int save_final_time(short int command, struct save_final_time_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct save_final_time_data cmd_data;
	
	static double *final_time;

	static struct run_parameters *parameters;
	static int *parameters_size;
	
	static struct save_final_time_parameters *final_time_parameters;

	static int i, mag;
	
	switch (command)
	{
		case command_info: {printf("save_final_time\n"); return result_continue;}
		case command_insert:
		{
			memcpy(&cmd_data, command_data, sizeof(struct save_final_time_data));
			
			return result_continue;
		}
		case command_begin:
		{
			if (data_input(data, data_parameters, &parameters, &parameters_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &final_time, &final_time_parameters, cmd_data.size*sizeof(double), sizeof(struct save_final_time_parameters), cmd_data.data_index_final_time, data_size)==1) return result_error;
			
			final_time_parameters->index=0;
			final_time_parameters->size=0;
			
			return result_continue;
		}
		case command_run:
		{
			*(final_time+(final_time_parameters->index))=parameters->time;
			
			(final_time_parameters->index)++;
			final_time_parameters->size+=sizeof(double);

			return result_continue;
		}
		default: return result_continue;
	}
}

short int save_final_extinct(short int command, struct save_final_extinct_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct save_final_extinct_data cmd_data;
	
	static double *final_extinct;

	static struct run_parameters *parameters;
	static int *parameters_size;
	
	static struct save_final_extinct_parameters *final_extinct_parameters;

	static int i, extinct;
	
	switch (command)
	{
		case command_info: {printf("save_final_extinct\n"); return result_continue;}
		case command_insert:
		{
			memcpy(&cmd_data, command_data, sizeof(struct save_final_extinct_data));
			
			return result_continue;
		}
		case command_begin:
		{
			if (data_input(data, data_parameters, &parameters, &parameters_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &final_extinct, &final_extinct_parameters, cmd_data.size*sizeof(double), sizeof(struct save_final_extinct_parameters), cmd_data.data_index_final_extinct, data_size)==1) return result_error;
			
			final_extinct_parameters->index=0;
			final_extinct_parameters->size=0;
			
			return result_continue;
		}
		case command_run:
		{
			extinct=1;

			for (i=0; i<7*(parameters->N); i++)
			{
				if (*(parameters->X_int+i)>0) {extinct=0; break;}
			}

			*(final_extinct+(final_extinct_parameters->index))=extinct;
			
			(final_extinct_parameters->index)++;
			final_extinct_parameters->size+=sizeof(double);

			return result_continue;
		}
		default: return result_continue;
	}
}

short int save_final_extinct_1(short int command, struct save_final_extinct_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct save_final_extinct_data cmd_data;
	
	static double *final_extinct;

	static struct run_parameters *parameters;
	static int *parameters_size;
	
	static struct save_final_extinct_parameters *final_extinct_parameters;

	static int i, extinct;
	
	switch (command)
	{
		case command_info: {printf("save_final_extinct_1\n"); return result_continue;}
		case command_insert:
		{
			memcpy(&cmd_data, command_data, sizeof(struct save_final_extinct_data));
			
			return result_continue;
		}
		case command_begin:
		{
			if (data_input(data, data_parameters, &parameters, &parameters_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &final_extinct, &final_extinct_parameters, cmd_data.size*sizeof(double), sizeof(struct save_final_extinct_parameters), cmd_data.data_index_final_extinct, data_size)==1) return result_error;
			
			final_extinct_parameters->index=0;
			final_extinct_parameters->size=0;
			
			return result_continue;
		}
		case command_run:
		{
			extinct=1;

			for (i=0; i<7; i++)
			{
				if (*(parameters->X_int+i)>0) {extinct=0; break;}
			}

			*(final_extinct+(final_extinct_parameters->index))=extinct;
			
			(final_extinct_parameters->index)++;
			final_extinct_parameters->size+=sizeof(double);

			return result_continue;
		}
		default: return result_continue;
	}
}

short int save_final_extinct_2(short int command, struct save_final_extinct_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct save_final_extinct_data cmd_data;
	
	static double *final_extinct;

	static struct run_parameters *parameters;
	static int *parameters_size;
	
	static struct save_final_extinct_parameters *final_extinct_parameters;

	static int i, extinct;
	
	switch (command)
	{
		case command_info: {printf("save_final_extinct_2\n"); return result_continue;}
		case command_insert:
		{
			memcpy(&cmd_data, command_data, sizeof(struct save_final_extinct_data));
			
			return result_continue;
		}
		case command_begin:
		{
			if (data_input(data, data_parameters, &parameters, &parameters_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &final_extinct, &final_extinct_parameters, cmd_data.size*sizeof(double), sizeof(struct save_final_extinct_parameters), cmd_data.data_index_final_extinct, data_size)==1) return result_error;
			
			final_extinct_parameters->index=0;
			final_extinct_parameters->size=0;
			
			return result_continue;
		}
		case command_run:
		{
			extinct=1;

			for (i=7; i<14; i++)
			{
				if (*(parameters->X_int+i)>0) {extinct=0; break;}
			}

			*(final_extinct+(final_extinct_parameters->index))=extinct;
			
			(final_extinct_parameters->index)++;
			final_extinct_parameters->size+=sizeof(double);

			return result_continue;
		}
		default: return result_continue;
	}
}

short int save_seed(short int command, struct save_seed_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct save_seed_data cmd_data;
	
	static double *seed_low;
	static double *seed_high;

	static unsigned long int num2pow32;

	static struct rng_struct *rng_struct;
	static int *rng_struct_size;
	
	static struct save_seed_parameters *seed_low_parameters;
	static struct save_seed_parameters *seed_high_parameters;

	switch (command)
	{
		case command_info: {printf("save_seed\n"); return result_continue;}
		case command_insert:
		{
			memcpy(&cmd_data, command_data, sizeof(struct save_seed_data));

			num2pow32=pow(2,16)*pow(2,16);

			return result_continue;
		}
		case command_begin:
		{
			if (data_input(data, data_parameters, &rng_struct, &rng_struct_size, cmd_data.data_index_rng, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &seed_low, &seed_low_parameters, cmd_data.size*sizeof(double), sizeof(struct save_seed_parameters), cmd_data.data_index_low, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &seed_high, &seed_high_parameters, cmd_data.size*sizeof(double), sizeof(struct save_seed_parameters), cmd_data.data_index_high, data_size)==1) return result_error;
			
			seed_low_parameters->index=0;
			seed_low_parameters->size=0;
			
			seed_high_parameters->index=0;
			seed_high_parameters->size=0;

			return result_continue;
		}
		case command_run:
		{
			*(seed_low+(seed_low_parameters->index))=(double)((rng_struct->seed)%num2pow32);
			*(seed_high+(seed_high_parameters->index))=(double)((rng_struct->seed)/num2pow32);
			
			(seed_low_parameters->index)++;
			(seed_high_parameters->index)++;
			
			seed_low_parameters->size+=sizeof(double);
			seed_high_parameters->size+=sizeof(double);

			return result_continue;
		}
		default: return result_continue;
	}
}

