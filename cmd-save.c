/**************************************************************
***************************************************************
*** 
***   cmd-save.c
***
***   Jason Olejarz
***   2011-03-09
***
***   This file contains commands for setting up postprocessing.
***
***************************************************************
**************************************************************/

void cmd_fs()
{
	short int save_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_final_steps=arg_short_int[2];
	int num=arg_int[0];
	
	struct save_final_steps_data finalstepsdata;

	finalstepsdata.data_index_parameters=data_index_parameters;
	finalstepsdata.data_index_final_steps=data_index_final_steps;
	finalstepsdata.size=num;
	save_final_steps(command_insert, &finalstepsdata, data, data_parameters, data_num);

	list_insert(save, save_index, save_final_steps, save_num);
	
	return;
}

void cmd_ft()
{
	short int save_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_final_time=arg_short_int[2];
	int num=arg_int[0];
	
	struct save_final_time_data finaltimedata;

	finaltimedata.data_index_parameters=data_index_parameters;
	finaltimedata.data_index_final_time=data_index_final_time;
	finaltimedata.size=num;
	save_final_time(command_insert, &finaltimedata, data, data_parameters, data_num);

	list_insert(save, save_index, save_final_time, save_num);
	
	return;
}

void cmd_fextinct()
{
	short int save_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_final_extinct=arg_short_int[2];
	int num=arg_int[0];
	
	struct save_final_extinct_data finalextinctdata;

	finalextinctdata.data_index_parameters=data_index_parameters;
	finalextinctdata.data_index_final_extinct=data_index_final_extinct;
	finalextinctdata.size=num;
	save_final_extinct(command_insert, &finalextinctdata, data, data_parameters, data_num);

	list_insert(save, save_index, save_final_extinct, save_num);
	
	return;
}

void cmd_fextinct1()
{
	short int save_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_final_extinct=arg_short_int[2];
	int num=arg_int[0];
	
	struct save_final_extinct_data finalextinctdata;

	finalextinctdata.data_index_parameters=data_index_parameters;
	finalextinctdata.data_index_final_extinct=data_index_final_extinct;
	finalextinctdata.size=num;
	save_final_extinct_1(command_insert, &finalextinctdata, data, data_parameters, data_num);

	list_insert(save, save_index, save_final_extinct_1, save_num);
	
	return;
}

void cmd_fextinct2()
{
	short int save_index=arg_short_int[0];
	short int data_index_parameters=arg_short_int[1];
	short int data_index_final_extinct=arg_short_int[2];
	int num=arg_int[0];
	
	struct save_final_extinct_data finalextinctdata;

	finalextinctdata.data_index_parameters=data_index_parameters;
	finalextinctdata.data_index_final_extinct=data_index_final_extinct;
	finalextinctdata.size=num;
	save_final_extinct_2(command_insert, &finalextinctdata, data, data_parameters, data_num);

	list_insert(save, save_index, save_final_extinct_2, save_num);
	
	return;
}

void cmd_svseed()
{
	short int save_index=arg_short_int[0];
	short int data_index_rng=arg_short_int[1];
	short int data_index_low=arg_short_int[2];
	short int data_index_high=arg_short_int[3];
	int num=arg_int[0];
	
	struct save_seed_data seeddata;

	seeddata.data_index_rng=data_index_rng;
	seeddata.data_index_low=data_index_low;
	seeddata.data_index_high=data_index_high;
	seeddata.size=num;
	save_seed(command_insert, &seeddata, data, data_parameters, data_num);

	list_insert(save, save_index, save_seed, save_num);
	
	return;
}

