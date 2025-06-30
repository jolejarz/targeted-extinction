/**************************************************************
***************************************************************
*** 
***   cmd-step.c
***
***   Jason Olejarz
***   2011-01-27
***
***   This file contains commands for intermediate processing.
***
***************************************************************
**************************************************************/

void cmd_X()
{
	short int step_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_trigger=arg_short_int[2];
	short int data_index_X=arg_short_int[3];
	int num=arg_int[0];
	
	struct step_X_data command_data;
	
	command_data.data_index_parameters=data_index_parameters;
	command_data.data_index_trigger=data_index_trigger;
	command_data.data_index_X=data_index_X;
	command_data.num=num;
	
	step_X(command_insert, &command_data, data, data_parameters, data_num);
	
	list_insert(step, step_index, step_X, step_num);

	return;
}

void cmd_noDX()
{
	short int step_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	double extra_time=arg_double[0];
	
	struct step_no_D_data command_data;
	
	command_data.data_index_parameters=data_index_parameters;
	command_data.extra_time=extra_time;
	
	step_no_D_X(command_insert, &command_data, data, data_parameters, data_num);
	
	list_insert(step, step_index, step_no_D_X, step_num);

	return;

}

void cmd_pop()
{
	short int step_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_trigger=arg_short_int[2];
	short int data_index_s=arg_short_int[3];
	short int data_index_x=arg_short_int[4];
	short int data_index_w=arg_short_int[5];
	short int data_index_r=arg_short_int[6];
	
	struct step_pop_data command_data;
	
	command_data.data_index_parameters=data_index_parameters;
	command_data.data_index_trigger=data_index_trigger;
	command_data.data_index_s=data_index_s;
	command_data.data_index_x=data_index_x;
	command_data.data_index_w=data_index_w;
	command_data.data_index_r=data_index_r;
	
	step_pop(command_insert, &command_data, data, data_parameters, data_num);
	
	list_insert(step, step_index, step_pop, step_num);

	return;
}

void cmd_extinct()
{
	short int step_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_trigger=arg_short_int[2];
	short int data_index_extinction=arg_short_int[3];
	int number=arg_int[0];
	
	struct step_extinction_data command_data;
	
	command_data.data_index_parameters=data_index_parameters;
	command_data.data_index_trigger=data_index_trigger;
	command_data.data_index_extinction=data_index_extinction;
	command_data.number=number;
	
	step_extinction(command_insert, &command_data, data, data_parameters, data_num);
	
	list_insert(step, step_index, step_extinction, step_num);

	return;

}

void cmd_anrect()
{
	short int step_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_trigger=arg_short_int[2];
	int nx=arg_int[0];
	int ny=arg_int[1];
	
	struct step_animate_rect_data command_data;
	
	command_data.data_index_parameters=data_index_parameters;
	command_data.data_index_trigger=data_index_trigger;
	command_data.nx=nx;
	command_data.ny=ny;
	
	step_animate_rect(command_insert, &command_data, data, data_parameters, data_num);
	
	list_insert(step, step_index, step_animate_rect, step_num);

	return;

}

void cmd_time()
{
	short int step_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_trigger=arg_short_int[2];
	short int data_index_time=arg_short_int[3];
	
	struct step_time_data command_data;
	
	command_data.data_index_parameters=data_index_parameters;
	command_data.data_index_trigger=data_index_trigger;
	command_data.data_index_time=data_index_time;
	
	step_time(command_insert, &command_data, data, data_parameters, data_num);
	
	list_insert(step, step_index, step_time, step_num);

	return;

}

void cmd_trigs()
{
	short int step_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_trigger=arg_short_int[2];
	unsigned long int steps_interval=arg_unsigned_long_int[0];
	short int progress=arg_short_int[3];
	
	struct step_trigger_steps_data command_data;
	
	command_data.data_index_parameters=data_index_parameters;
	command_data.data_index_trigger=data_index_trigger;
	command_data.steps_interval=steps_interval;
	command_data.progress=progress;

	step_trigger_steps(command_insert, &command_data, data, data_parameters, data_num);
	
	list_insert(step, step_index, step_trigger_steps, step_num);
	
	return;
}

void cmd_trigt()
{
	short int step_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_trigger=arg_short_int[2];
	double time_interval=arg_double[0];
	short int progress=arg_short_int[3];
	
	struct step_trigger_time_data command_data;
	
	command_data.data_index_parameters=data_index_parameters;
	command_data.data_index_trigger=data_index_trigger;
	command_data.time_interval=time_interval;
	command_data.progress=progress;

	step_trigger_time(command_insert, &command_data, data, data_parameters, data_num);
	
	list_insert(step, step_index, step_trigger_time, step_num);

	return;
}

void cmd_trigtonce()
{
	short int step_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_trigger=arg_short_int[2];
	double time=arg_double[0];
	int runs=arg_int[0];
	
	struct step_trigger_time_once_data command_data;
	
	command_data.data_index_parameters=data_index_parameters;
	command_data.data_index_trigger=data_index_trigger;
	command_data.time=time;
	command_data.runs=runs;

	step_trigger_time_once(command_insert, &command_data, data, data_parameters, data_num);
	
	list_insert(step, step_index, step_trigger_time_once, step_num);
	
	return;
}

