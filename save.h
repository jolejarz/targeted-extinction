/**************************************************************
***************************************************************
*** 
***   save.h
***
***   Jason Olejarz
***   2010-07-21
***
***   This is the header file for save.c.
***
***************************************************************
**************************************************************/

struct save_extinction_data
{
	short int data_index_parameters;
	short int data_index_extinction;
	int size;
};
struct save_extinction_parameters
{
	int size;
	int index;
};

struct save_final_steps_data
{
	short int data_index_parameters;
	short int data_index_final_steps;
	int size;
};
struct save_final_steps_parameters
{
	int size;
	int index;
};

struct save_final_time_data
{
	short int data_index_parameters;
	short int data_index_final_time;
	int size;
};
struct save_final_time_parameters
{
	int size;
	int index;
};

struct save_final_total_data
{
	short int data_index_parameters;
	short int data_index_final_total;
	int size;
};
struct save_final_total_parameters
{
	int size;
	int index;
};

struct save_final_X_data
{
	short int data_index_parameters;
	short int data_index_final_X;
	int num_X;
	int size;
};
struct save_final_X_parameters
{
	int size;
	int index;
};

struct save_final_extinct_data
{
	short int data_index_parameters;
	short int data_index_final_extinct;
	int size;
};
struct save_final_extinct_parameters
{
	int size;
	int index;
};

struct save_seed_data
{
	short int data_index_rng;
	short int data_index_low;
	short int data_index_high;
	int size;
};
struct save_seed_parameters
{
	int size;
	int index;
};

short int save_final_steps(short int command, struct save_final_steps_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int save_final_time(short int command, struct save_final_time_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int save_final_extinct(short int command, struct save_final_extinct_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int save_final_extinct_1(short int command, struct save_final_extinct_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int save_final_extinct_2(short int command, struct save_final_extinct_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int save_seed(short int command, struct save_seed_data *command_data, void *data[], void *data_parameters[], short int data_size);

