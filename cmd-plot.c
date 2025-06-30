/**************************************************************
***************************************************************
*** 
***   cmd-plot.c
***
***   Jason Olejarz
***   2011-01-27
***
***   This file contains graphics commands.
***
***************************************************************
**************************************************************/

void cmd_plotrect()
{
	short int data_index_parameters=arg_short_int[0];
	int nx=arg_int[0];
	int ny=arg_int[1];
	
	static struct run_parameters *parameters;
	static int *parameters_size;
	
	// Allocate a block of memory to store parameter values.
	if (data_input(data, data_parameters, &parameters, &parameters_size, data_index_parameters, data_num)==1) return result_error;

	FILE *plot;
	
	plot=fopen(arg_string[0], "w");

	plot_rect(parameters->X_int, nx, ny, plot);
	
	fclose(plot);
	
	return;
}

