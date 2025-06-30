/**************************************************************
***************************************************************
*** 
***   commands.h
***
***   Jason Olejarz
***   2011-01-25
***
***   This file sets up the command arrays.
***
***************************************************************
**************************************************************/

enum {type_double, type_int, type_short_int, type_string, type_unsigned_long_int};

double arg_double[64];
int arg_int[64];
short int arg_short_int[64];
char arg_string[64][64];
unsigned long int arg_unsigned_long_int[64];

// data
void cmd_cnt();
void cmd_dd();
void cmd_disp();
void cmd_dt();
void cmd_flt();
void cmd_minmax();
void cmd_sd();
void cmd_tag();
// file
void cmd_load();
void cmd_loadtext();
void cmd_save();
void cmd_savetext();
void cmd_xy();
// list
void cmd_dl();
void cmd_sl();
// loop
void cmd_lp();
void cmd_lpseed();
void cmd_tsc();
// plot
void cmd_plotrect();
// run
void cmd_run();
// save
void cmd_fs();
void cmd_ft();
void cmd_fextinct();
void cmd_fextinct1();
void cmd_fextinct2();
void cmd_svseed();
// set
void cmd_iXmult();
void cmd_iX();
void cmd_rnglcg();
void cmd_rngmt();
void cmd_seed();
void cmd_set();
void cmd_settsc();
void cmd_ucomp();
void cmd_urect();
void cmd_ustar();
void cmd_uexp();
void cmd_u2();
void cmd_u3();
void cmd_u4();
void cmd_u5();
// step
void cmd_X();
void cmd_noDX();
void cmd_pop();
void cmd_extinct();
void cmd_anrect();
void cmd_time();
void cmd_trigs();
void cmd_trigt();
void cmd_trigtonce();

int main();

char *cmd_name[]=
{
	/* data */
	"cnt",
	"dd",
	"disp",
	"dt",
	"flt",
	"minmax",
	"sd",
	"tag",
	/* file */
	"load",
	"loadtext",
	"save",
	"savetext",
	"xy",
	/* list */
	"dl",
	"sl",
	/* loop */
	"lp",
	"lpseed",
	"tsc",
	/* plot */
	"plotrect",
	/* run */
	"run",
	/* save */
	"fs",
	"ft",
	"fextinct",
	"fextinct1",
	"fextinct2",
	"svseed",
	/* set */
	"iXmult",
	"iX",
	"rnglcg",
	"rngmt",
	"seed",
	"set",
	"settsc",
	"ucomp",
	"urect",
	"ustar",
	"uexp",
	"u2",
	"u3",
	"u4",
	"u5",
	/* step */
	"X",
	"noDX",
	"pop",
	"extinct",
	"anrect",
	"time",
	"trigs",
	"trigt",
	"trigtonce",
	/* exit / quit */
	"exit",
	"quit"
};
void (*functions[])()=
{
	/* data */
	cmd_cnt,
	cmd_dd,
	cmd_disp,
	cmd_dt,
	cmd_flt,
	cmd_minmax,
	cmd_sd,
	cmd_tag,
	/* file */
	cmd_load,
	cmd_loadtext,
	cmd_save,
	cmd_savetext,
	cmd_xy,
	/* list */
	cmd_dl,
	cmd_sl,
	/* loop */
	cmd_lp,
	cmd_lpseed,
	cmd_tsc,
	/* plot */
	cmd_plotrect,
	/* run */
	cmd_run,
	/* save */
	cmd_fs,
	cmd_ft,
	cmd_fextinct,
	cmd_fextinct1,
	cmd_fextinct2,
	cmd_svseed,
	/* set */
	cmd_iXmult,
	cmd_iX,
	cmd_rnglcg,
	cmd_rngmt,
	cmd_seed,
	cmd_set,
	cmd_settsc,
	cmd_ucomp,
	cmd_urect,
	cmd_ustar,
	cmd_uexp,
	cmd_u2,
	cmd_u3,
	cmd_u4,
	cmd_u5,
	/* step */
	cmd_X,
	cmd_noDX,
	cmd_pop,
	cmd_extinct,
	cmd_anrect,
	cmd_time,
	cmd_trigs,
	cmd_trigt,
	cmd_trigtonce,
	/* exit / quit */
	0,
	0
};
int num_args[]=
{
	/* data */
		/* cnt */	3,
		/* dd */	1,
		/* disp */	3,
		/* dt */	0,
		/* flt */	3,
		/* minmax */	1,
		/* sd */	0,
		/* tag */	2,
	/* file */
		/* load */	2,
		/* loadtext */	2,
		/* save */	2,
		/* savetext */	2,
		/* xy */	3,
	/* list */
		/* dl */	2,
		/* sl */	1,
	/* loop */
		/* lp */	3,
		/* lpseed */	5,
		/* tsc */	2,
	/* plot */
		/* plotrect */	4,
	/* run */
		/* run */	1,
	/* save */
		/* fs */	4,
		/* ft */	4,
		/* fextinct */	4,
		/* fextinct1 */	4,
		/* fextinct2 */	4,
		/* svseed */	5,
	/* set */
		/* iXmult */	5,
		/* iX */	3,
		/* rnglcg */	1,
		/* rngmt */	1,
		/* seed */	3,
		/* set */	17,
		/* settsc */	1,
		/* ucomp */	2,
		/* urect */	4,
		/* ustar */	4,
		/* uexp */	5,
		/* u2 */	3,
		/* u3 */	7,
		/* u4 */	13,
		/* u5 */	21,
	/* step */
		/* X */		5,
		/* noDX */	3,
		/* pop */	7,
		/* extinct */	5,
		/* anrect */	5,
		/* time */	4,
		/* trigs */	5,
		/* trigt */	5,
		/* trigtonce */	5,
	/* exit / quit */
		/* exit */	0,
		/* quit */	0
};
int arg_types[][64]=
{
	/* data */
		/* cnt */	{type_short_int, type_double, type_double},
		/* dd */	{type_short_int},
		/* disp */	{type_short_int, type_int, type_int},
		/* dt */	{},
		/* flt */	{type_short_int, type_double, type_double},
		/* minmax */	{type_short_int},
		/* sd */	{},
		/* tag */	{type_short_int, type_short_int},
	/* file */
		/* load */	{type_short_int, type_string},
		/* loadtext */	{type_short_int, type_string},
		/* save */	{type_short_int, type_string},
		/* savetext */	{type_short_int, type_string},
		/* xy */	{type_short_int, type_short_int, type_string},
	/* list */
		/* dl */	{type_short_int, type_short_int},
		/* sl */	{type_short_int},
	/* loop */
		/* lp */	{type_short_int, type_int, type_short_int},
		/* lpseed */	{type_short_int, type_short_int, type_short_int, type_short_int, type_int},
		/* tsc */	{type_short_int, type_short_int},
	/* plot */
		/* plotrect */	{type_short_int, type_int, type_int, type_string},
	/* run */
		/* run	*/	{type_short_int},
	/* save */
		/* fs */	{type_short_int, type_short_int, type_short_int, type_int},
		/* ft */	{type_short_int, type_short_int, type_short_int, type_int},
		/* fextinct */  {type_short_int, type_short_int, type_short_int, type_int},
		/* fextinct1 */ {type_short_int, type_short_int, type_short_int, type_int},
		/* fextinct2 */ {type_short_int, type_short_int, type_short_int, type_int},
		/* svseed */    {type_short_int, type_short_int, type_short_int, type_short_int, type_int},
	/* set */
		/* iXmult */	{type_short_int, type_short_int, type_short_int, type_short_int, type_int},
		/* iX */	{type_short_int, type_short_int, type_int},
		/* rnglcg */	{type_short_int},
		/* rngmt */	{type_short_int},
		/* seed */	{type_short_int, type_double, type_double},
		/* set */	{type_short_int, type_short_int, type_double, type_int, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_short_int},
		/* settsc */	{type_short_int},
		/* ucomp */	{type_short_int, type_double},
		/* urect */	{type_short_int, type_double, type_int, type_int},
		/* ustar */	{type_short_int, type_double, type_double, type_int},
		/* uexp */	{type_short_int, type_double, type_double, type_int, type_int},
		/* u2 */	{type_short_int, type_double, type_double},
		/* u3 */	{type_short_int, type_double, type_double, type_double, type_double, type_double, type_double},
		/* u4 */	{type_short_int, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double},
		/* u5 */	{type_short_int, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double, type_double},
	/* step */
		/* X */		{type_short_int, type_short_int, type_short_int, type_short_int, type_int},
		/* noDX */	{type_short_int, type_short_int, type_double},
		/* pop */	{type_short_int, type_short_int, type_short_int, type_short_int, type_short_int, type_short_int, type_short_int},
		/* extinct */	{type_short_int, type_short_int, type_short_int, type_short_int, type_int},
		/* anrect */	{type_short_int, type_short_int, type_short_int, type_int, type_int},
		/* time */	{type_short_int, type_short_int, type_short_int, type_short_int},
		/* trigs */	{type_short_int, type_short_int, type_short_int, type_unsigned_long_int, type_short_int},
		/* trigt */	{type_short_int, type_short_int, type_short_int, type_double, type_short_int},
		/* trigtonce */	{type_short_int, type_short_int, type_short_int, type_double, type_int},
	/* exit / quit */
		/* exit */	{},
		/* quit */	{}
};

