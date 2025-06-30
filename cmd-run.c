/**************************************************************
***************************************************************
*** 
***   cmd-run.c
***
***   Jason Olejarz
***   2011-01-25
***
***   This file contains the command for running the simulations.
***
***************************************************************
**************************************************************/

void cmd_run()
{
	short int parameters_data_index=arg_short_int[0];
	
	struct run_parameters *parameters;
	int *parameters_size;

	if (data_input(data, data_parameters, &parameters, &parameters_size, parameters_data_index, data_num)==1) return result_error;

	calc(loop, step, save, loop_num, step_num, save_num, data_num, data, data_parameters, run, parameters);

	return;
}
