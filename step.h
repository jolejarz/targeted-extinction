/**************************************************************
***************************************************************
*** 
***   step.h
***
***   Jason Olejarz
***   2011-01-27
***
***   This is the header file for step.c.
***
***************************************************************
**************************************************************/

struct step_X_data
{
	short int data_index_parameters;
	short int data_index_trigger;
	short int data_index_X;
	int num;
};
struct step_X_parameters
{
	int size;
	int index;
};

struct step_mutation_data
{
	short int data_index_rng;
	short int data_index_parameters;
	double time;
};
struct step_mutation_parameters
{
	int size;
	int index;
};

struct step_resistance_data
{
	short int data_index_parameters;
	short int data_index_trigger;
	short int data_index_resistance;
};
struct step_resistance_parameters
{
	int size;
	int index;
};

struct step_no_D_data
{
	short int data_index_parameters;
	double extra_time;
};
struct step_no_D_parameters
{
	int size;
	int index;
};

struct step_energy_data
{
	short int data_index_parameters;
	short int data_index_trigger;
	short int data_index_energy;
};
struct step_energy_parameters
{
	int size;
	int index;
};

struct step_flips_data
{
	short int data_index_parameters;
	short int data_index_flips;
	int steps;
};
struct step_flips_parameters
{
	int size;
	int index;
};

struct step_mag_data
{
	short int data_index_parameters;
	short int data_index_trigger;
	short int data_index_mag;
};
struct step_mag_parameters
{
	int size;
	int index;
};

struct step_pop_data
{
	short int data_index_parameters;
	short int data_index_trigger;
	short int data_index_s;
	short int data_index_x;
	short int data_index_w;
	short int data_index_r;
};
struct step_pop_parameters
{
	int size;
	int index;
};

struct step_extinction_data
{
	short int data_index_parameters;
	short int data_index_trigger;
	short int data_index_extinction;
	int number;
};
struct step_extinction_parameters
{
	int size;
	int index;
};

struct step_animate_rect_data
{
	short int data_index_parameters;
	short int data_index_trigger;
	int nx;
	int ny;
};
struct step_animate_rect_parameters
{
	int size;
	int index;
};

struct step_time_data
{
	short int data_index_parameters;
	short int data_index_trigger;
	short int data_index_time;
};
struct step_time_parameters
{
	int size;
	int index;
};

struct step_trigger_steps_data
{
	short int data_index_parameters;
	short int data_index_trigger;
	unsigned long int steps_interval;
	short int progress;
};
struct step_trigger_time_data
{
	short int data_index_parameters;
	short int data_index_trigger;
	double time_interval;
	short int progress;
};
struct step_trigger_time_once_data
{
	short int data_index_parameters;
	short int data_index_trigger;
	double time;
	int runs;
};
// The parameters data index for a trigger is the same whether the trigger is after a number of steps
// have elapsed or after an amount of time has elapsed.
struct step_trigger_parameters
{
	int total;
	int current;
	unsigned long int steps;
	double time;
};

short int step_X(short int command, struct step_X_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int step_no_D_X(short int command, struct step_no_D_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int step_pop(short int command, struct step_pop_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int step_extinction(short int command, struct step_extinction_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int step_animate_rect(short int command, struct step_animate_rect_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int step_time(short int command, struct step_time_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int step_trigger_steps(short int command, struct step_trigger_steps_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int step_trigger_time(short int command, struct step_trigger_time_data *command_data, void *data[], void *data_parameters[], short int data_size);
short int step_trigger_time_once(short int command, struct step_trigger_time_once_data *command_data, void *data[], void *data_parameters[], short int data_size);

