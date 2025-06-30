/**************************************************************
***************************************************************
*** 
***   step.c
***
***   Jason Olejarz
***   2011-01-27
***
***   This file contains the routines used by 'evolve' for intermediate processing.
***
***************************************************************
**************************************************************/

#include "includes.h"

short int step_X(short int command, struct step_X_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct step_X_data cmd_data;
	
	static struct run_parameters *p;
	static int *p_size;
	static short int *trigger;
	static struct step_trigger_parameters *trigger_parameters;
	static double **X;
	static struct step_X_parameters **X_parameters;
	
	static int i;

	switch (command)
	{
		case command_info: {printf("step_X\n"); return result_continue;}
		case command_insert:
		{
			memcpy (&cmd_data, command_data, sizeof(struct step_X_data));

			if (data_input(data, data_parameters, &p, &p_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_input(data, data_parameters, &trigger, &trigger_parameters, cmd_data.data_index_trigger, data_size)==1) return result_error;

			X=(double**)malloc (sizeof(double*)*cmd_data.num);
			X_parameters=(struct step_x_parameters**)malloc (sizeof(struct step_x_parameters*)*cmd_data.num);

			for (i=0; i<cmd_data.num; i++)
			{
				if (data_output(data, data_parameters, X+i, X_parameters+i, sizeof(double)*((trigger_parameters->total)+1), sizeof(struct step_X_parameters), cmd_data.data_index_X+i, data_size)==1) return result_error;
				
				(*X_parameters)->size=0;
				(*X_parameters)->index=0;
			}
			
			return result_continue;
		}
		case command_begin:
		{
			for (i=0; i<cmd_data.num; i++)
			{
				*(*(X+i)+((*(X_parameters+i))->index))=*(p->X+i);

				((*(X_parameters+i))->size)+=sizeof(double);
				((*(X_parameters+i))->index)++;
			}

			return result_continue;
		}
		case command_run:
		{
			if (*trigger==1)
			{
				for (i=0; i<cmd_data.num; i++)
				{
					*(*(X+i)+((*(X_parameters+i))->index))=*(p->X+i);
					
					((*(X_parameters+i))->size)+=sizeof(double);
					((*(X_parameters+i))->index)++;
				}
			}

			return result_continue;
		}
		default: return result_continue;
	}
}

short int step_no_D_X(short int command, struct step_no_D_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct step_no_D_data cmd_data;
	
	static struct run_parameters *p;
	static int *p_size;
	
	static int i;

	static short int end_simulation;

	static short int counting;

	static double time_start;

	switch (command)
	{
		case command_info: {printf("step_no_D_X\n"); return result_continue;}
		case command_insert:
		{
			memcpy (&cmd_data, command_data, sizeof(struct step_no_D_data));

			if (data_input(data, data_parameters, &p, &p_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			
			return result_continue;
		}
		case command_begin:
		{
			counting=0;

			return result_continue;
		}
		case command_run:
		{
			if (counting==0)
			{
				end_simulation=1;

				for (i=0; i<(p->N); i++)
				{
					if (*(p->X_int+7*i+0)>0 || *(p->X_int+7*i+1)>0) {end_simulation=0; break;}
				}

				if (end_simulation==1) {time_start=p->time; counting=1;}
			}
			else if (p->time-time_start>cmd_data.extra_time) return result_done;

			return result_continue;
		}
		default: return result_continue;
	}
}

short int step_pop(short int command, struct step_pop_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct step_pop_data cmd_data;
	
	static struct run_parameters *p;
	static int *p_size;
	static short int *trigger;
	static struct step_trigger_parameters *trigger_parameters;
	static double *num_s;
	static struct step_pop_parameters *num_s_parameters;
	static double *num_x;
	static struct step_pop_parameters *num_x_parameters;
	static double *num_w;
	static struct step_pop_parameters *num_w_parameters;
	static double *num_r;
	static struct step_pop_parameters *num_r_parameters;

	static int i, count_s, count_x, count_w, count_r;
	
	switch (command)
	{
		case command_info: {printf("step_pop\n"); return result_continue;}
		case command_insert:
		{
			memcpy (&cmd_data, command_data, sizeof(struct step_pop_data));

			if (data_input(data, data_parameters, &p, &p_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_input(data, data_parameters, &trigger, &trigger_parameters, cmd_data.data_index_trigger, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &num_s, &num_s_parameters, sizeof(double)*((trigger_parameters->total)+1), sizeof(struct step_pop_parameters), cmd_data.data_index_s, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &num_x, &num_x_parameters, sizeof(double)*((trigger_parameters->total)+1), sizeof(struct step_pop_parameters), cmd_data.data_index_x, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &num_w, &num_w_parameters, sizeof(double)*((trigger_parameters->total)+1), sizeof(struct step_pop_parameters), cmd_data.data_index_w, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &num_r, &num_r_parameters, sizeof(double)*((trigger_parameters->total)+1), sizeof(struct step_pop_parameters), cmd_data.data_index_r, data_size)==1) return result_error;
			
			num_s_parameters->size=0;
			num_s_parameters->index=0;

			num_x_parameters->size=0;
			num_x_parameters->index=0;

			num_w_parameters->size=0;
			num_w_parameters->index=0;

			num_r_parameters->size=0;
			num_r_parameters->index=0;

			return result_continue;
		}
		case command_begin:
		{
			count_s=0; count_x=0; count_w=0; count_r=0;
			for (i=0; i<p->N; i++)
			{
				if (*(p->X+7*i+0)==0 &&
				    *(p->X+7*i+1)==0 &&
				    *(p->X+7*i+2)==0 &&
				    *(p->X+7*i+3)==0 &&
				    *(p->X+7*i+4)==0 &&
				    *(p->X+7*i+5)==0 &&
				    *(p->X+7*i+6)==0) count_x++;
				else if (*(p->X+7*i+1)>0 ||
				         *(p->X+7*i+3)>0 ||
				         *(p->X+7*i+5)>0 ||
				         *(p->X+7*i+6)>0) count_r++;
				else if (*(p->X+7*i+0)>0 ||
				         *(p->X+7*i+1)>0) count_s++;
				else count_w++;
			}

			*(num_s+(num_s_parameters->index))=count_s;
			
			(num_s_parameters->size)+=sizeof(double);
			(num_s_parameters->index)++;

			*(num_x+(num_x_parameters->index))=count_x;
			
			(num_x_parameters->size)+=sizeof(double);
			(num_x_parameters->index)++;

			*(num_w+(num_w_parameters->index))=count_w;
			
			(num_w_parameters->size)+=sizeof(double);
			(num_w_parameters->index)++;

			*(num_r+(num_r_parameters->index))=count_r;
			
			(num_r_parameters->size)+=sizeof(double);
			(num_r_parameters->index)++;

			return result_continue;
		}
		case command_run:
		{
			if (*trigger==1)
			{
				count_s=0; count_x=0; count_w=0; count_r=0;
				for (i=0; i<p->N; i++)
				{
					if (*(p->X+7*i+0)==0 &&
					    *(p->X+7*i+1)==0 &&
					    *(p->X+7*i+2)==0 &&
					    *(p->X+7*i+3)==0 &&
					    *(p->X+7*i+4)==0 &&
					    *(p->X+7*i+5)==0 &&
					    *(p->X+7*i+6)==0) count_x++;
					else if (*(p->X+7*i+1)>0 ||
						 *(p->X+7*i+3)>0 ||
						 *(p->X+7*i+5)>0 ||
						 *(p->X+7*i+6)>0) count_r++;
					else if (*(p->X+7*i+0)>0 ||
						 *(p->X+7*i+1)>0) count_s++;
					else count_w++;
				}

				*(num_s+(num_s_parameters->index))=count_s;
				
				(num_s_parameters->size)+=sizeof(double);
				(num_s_parameters->index)++;

				*(num_x+(num_x_parameters->index))=count_x;
				
				(num_x_parameters->size)+=sizeof(double);
				(num_x_parameters->index)++;

				*(num_w+(num_w_parameters->index))=count_w;
				
				(num_w_parameters->size)+=sizeof(double);
				(num_w_parameters->index)++;

				*(num_r+(num_r_parameters->index))=count_r;
				
				(num_r_parameters->size)+=sizeof(double);
				(num_r_parameters->index)++;
			}

			return result_continue;
		}
		default: return result_continue;
	}
}

short int step_extinction(short int command, struct step_extinction_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct step_extinction_data cmd_data;
	
	static struct run_parameters *p;
	static int *p_size;
	static short int *trigger;
	static struct step_trigger_parameters *trigger_parameters;
	static double *extinction;
	static struct step_extinction_parameters *extinction_parameters;
	
	static int *subpopulation_status;
	static int extinction_count;

	static int i;

	switch (command)
	{
		case command_info: {printf("step_extinction\n"); return result_continue;}
		case command_insert:
		{
			memcpy (&cmd_data, command_data, sizeof(struct step_extinction_data));

			if (data_input(data, data_parameters, &p, &p_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_input(data, data_parameters, &trigger, &trigger_parameters, cmd_data.data_index_trigger, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &extinction, &extinction_parameters, sizeof(double)*((trigger_parameters->total)+1), sizeof(struct step_extinction_parameters), cmd_data.data_index_extinction, data_size)==1) return result_error;
			
			extinction_parameters->size=0;
			extinction_parameters->index=0;

			subpopulation_status=(int*)malloc (sizeof(int)*(p->N));

			return result_continue;
		}
		case command_begin:
		{
			extinction_count=0;

			for (i=0; i<(p->N); i++)
			{
				if (*(p->X_total_int+i)==0) {extinction_count++; *(subpopulation_status+i)=0;}
				else *(subpopulation_status+i)=1;
			}

			*(extinction+(extinction_parameters->index))=extinction_count;
			
			(extinction_parameters->size)+=sizeof(double);
			(extinction_parameters->index)++;

			return result_continue;
		}
		case command_run:
		{
			for (i=0; i<(p->N); i++)
			{
				if (*(subpopulation_status+i)==1 && *(p->X_total_int+i)==0) {extinction_count++; *(subpopulation_status+i)=0;}
				else if (*(subpopulation_status+i)==0 && *(p->X_total_int+i)>cmd_data.number) *(subpopulation_status+i)=1;
			}

			if (*trigger==1)
			{
				*(extinction+(extinction_parameters->index))=extinction_count;
				
				(extinction_parameters->size)+=sizeof(double);
				(extinction_parameters->index)++;
			}

			return result_continue;
		}
		default: return result_continue;
	}
}

short int step_animate_rect(short int command, struct step_animate_rect_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct step_animate_rect_data cmd_data;
	
	static struct run_parameters *p;
	static int *p_size;
	static short int *trigger;
	static struct step_trigger_parameters *trigger_parameters;
	
	static FILE *plot;
	static FILE *plot2;
	static FILE *plot3;
	static FILE *compile;

	static int i;

	static char plot_file[9];
	static char plot_file_2[13];
	static char plot_file_3[12];

	switch (command)
	{
		case command_info: {printf("step_animate_rect\n"); return result_continue;}
		case command_insert:
		{
			memcpy (&cmd_data, command_data, sizeof(struct step_animate_rect_data));

			if (data_input(data, data_parameters, &p, &p_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_input(data, data_parameters, &trigger, &trigger_parameters, cmd_data.data_index_trigger, data_size)==1) return result_error;
			
			return result_continue;
		}
		case command_begin:
		{
			compile=fopen("compile.sh", "w");

			i=0;

			sprintf (plot_file, "%0.4d.eps", i);
			sprintf (plot_file_2, "crop%0.4d.tex", i);
			sprintf (plot_file_3, "fig%0.4d.tex", i);

			plot=fopen(plot_file, "w");
			plot2=fopen(plot_file_2, "w");
			plot3=fopen(plot_file_3, "w");

			plot_rect(p->X_int, cmd_data.nx, cmd_data.ny, plot);

			fprintf(plot2, "\\documentclass[12pt]{article}\n");
			fprintf(plot2, "\n");
			fprintf(plot2, "\\usepackage[margin=1in]{geometry}\n");
			fprintf(plot2, "\\usepackage{amsmath}\n");
			fprintf(plot2, "\\usepackage{amssymb}\n");
			fprintf(plot2, "\\usepackage{graphicx}\n");
			fprintf(plot2, "\\usepackage{subcaption}\n");
			fprintf(plot2, "\\usepackage{xcolor}\n");
			fprintf(plot2, "\\usepackage{nopageno}\n");
			fprintf(plot2, "\\usepackage{helvet}\n");
			fprintf(plot2, "\n");
			fprintf(plot2, "\\definecolor{PaleTurquoise}{HTML}{E1F0F5}\n");
			fprintf(plot2, "\n");
			fprintf(plot2, "\\setlength{\\fboxsep}{0pt}\n");
			fprintf(plot2, "\n");
			fprintf(plot2, "\\begin{document}\n");
			fprintf(plot2, "\n");
			fprintf(plot2, "\\begin{figure}\n");
			fprintf(plot2, "\\includegraphics[width=.9\\linewidth]{%0.4d.eps}\n", i);
			fprintf(plot2, "\\end{figure}\n");
			fprintf(plot2, "\n");
			fprintf(plot2, "\\end{document}\n");
			
			fprintf(plot3, "\\documentclass[12pt]{article}\n");
			fprintf(plot3, "\n");
			fprintf(plot3, "\\usepackage[margin=1in]{geometry}\n");
			fprintf(plot3, "\\usepackage{amsmath}\n");
			fprintf(plot3, "\\usepackage{amssymb}\n");
			fprintf(plot3, "\\usepackage{graphicx}\n");
			fprintf(plot3, "\\usepackage{subcaption}\n");
			fprintf(plot3, "\\usepackage{xcolor}\n");
			fprintf(plot3, "\\usepackage{nopageno}\n");
			fprintf(plot3, "\\usepackage{helvet}\n");
			fprintf(plot3, "\\usepackage{overpic}\n");
			fprintf(plot3, "\n");
			fprintf(plot3, "\\definecolor{PaleTurquoise}{HTML}{E1F0F5}\n");
			fprintf(plot3, "\n");
			fprintf(plot3, "\\setlength{\\fboxsep}{0pt}\n");
			fprintf(plot3, "\n");
			fprintf(plot3, "\\begin{document}\n");
			fprintf(plot3, "\n");
			fprintf(plot3, "\\includegraphics[scale=10]{crop%0.4d.eps}\n", i);
			fprintf(plot3, "\n");
			fprintf(plot3, "\\end{document}\n");
			
			fclose(plot3);
			fclose(plot2);
			fclose(plot);

			fprintf(compile, "pdflatex crop%0.4d.tex\n", i);
			fprintf(compile, "pdfcrop crop%0.4d.pdf crop%0.4d.pdf\n", i, i);
			fprintf(compile, "pdftops -eps crop%0.4d.pdf crop%0.4d.eps\n", i, i);
			fprintf(compile, "pdflatex fig%0.4d.tex\n", i);
			fprintf(compile, "pdfcrop fig%0.4d.pdf fig%0.4d.pdf\n", i, i);
			fprintf(compile, "pdftops -eps fig%0.4d.pdf fig%0.4d.eps\n", i, i);
			fprintf(compile, "convert fig%0.4d.eps fig%0.4d.jpg\n", i, i);
			fprintf(compile, "rm fig%0.4d.pdf\n", i);
			fprintf(compile, "rm fig%0.4d.eps\n", i);

			i++;

			return result_continue;
		}
		case command_run:
		{
			if (*trigger==1)
			{
				sprintf (plot_file, "%0.4d.eps", i);
				sprintf (plot_file_2, "crop%0.4d.tex", i);
				sprintf (plot_file_3, "fig%0.4d.tex", i);

				plot=fopen(plot_file, "w");
				plot2=fopen(plot_file_2, "w");
				plot3=fopen(plot_file_3, "w");

				plot_rect(p->X_int, cmd_data.nx, cmd_data.ny, plot);
				
				fprintf(plot2, "\\documentclass[12pt]{article}\n");
				fprintf(plot2, "\n");
				fprintf(plot2, "\\usepackage[margin=1in]{geometry}\n");
				fprintf(plot2, "\\usepackage{amsmath}\n");
				fprintf(plot2, "\\usepackage{amssymb}\n");
				fprintf(plot2, "\\usepackage{graphicx}\n");
				fprintf(plot2, "\\usepackage{subcaption}\n");
				fprintf(plot2, "\\usepackage{xcolor}\n");
				fprintf(plot2, "\\usepackage{nopageno}\n");
				fprintf(plot2, "\\usepackage{helvet}\n");
				fprintf(plot2, "\n");
				fprintf(plot2, "\\definecolor{PaleTurquoise}{HTML}{E1F0F5}\n");
				fprintf(plot2, "\n");
				fprintf(plot2, "\\setlength{\\fboxsep}{0pt}\n");
				fprintf(plot2, "\n");
				fprintf(plot2, "\\begin{document}\n");
				fprintf(plot2, "\n");
				fprintf(plot2, "\\begin{figure}\n");
				fprintf(plot2, "\\includegraphics[width=.9\\linewidth]{%0.4d.eps}\n", i);
				fprintf(plot2, "\\end{figure}\n");
				fprintf(plot2, "\n");
				fprintf(plot2, "\\end{document}\n");
				
				fprintf(plot3, "\\documentclass[12pt]{article}\n");
				fprintf(plot3, "\n");
				fprintf(plot3, "\\usepackage[margin=1in]{geometry}\n");
				fprintf(plot3, "\\usepackage{amsmath}\n");
				fprintf(plot3, "\\usepackage{amssymb}\n");
				fprintf(plot3, "\\usepackage{graphicx}\n");
				fprintf(plot3, "\\usepackage{subcaption}\n");
				fprintf(plot3, "\\usepackage{xcolor}\n");
				fprintf(plot3, "\\usepackage{nopageno}\n");
				fprintf(plot3, "\\usepackage{helvet}\n");
				fprintf(plot3, "\\usepackage{overpic}\n");
				fprintf(plot3, "\n");
				fprintf(plot3, "\\definecolor{PaleTurquoise}{HTML}{E1F0F5}\n");
				fprintf(plot3, "\n");
				fprintf(plot3, "\\setlength{\\fboxsep}{0pt}\n");
				fprintf(plot3, "\n");
				fprintf(plot3, "\\begin{document}\n");
				fprintf(plot3, "\n");
				fprintf(plot3, "\\includegraphics[scale=10]{crop%0.4d.eps}\n", i);
				fprintf(plot3, "\n");
				fprintf(plot3, "\\end{document}\n");
			
				fclose(plot3);
				fclose(plot2);
				fclose(plot);

				fprintf(compile, "pdflatex crop%0.4d.tex\n", i);
				fprintf(compile, "pdfcrop crop%0.4d.pdf crop%0.4d.pdf\n", i, i);
				fprintf(compile, "pdftops -eps crop%0.4d.pdf crop%0.4d.eps\n", i, i);
				fprintf(compile, "pdflatex fig%0.4d.tex\n", i);
				fprintf(compile, "pdfcrop fig%0.4d.pdf fig%0.4d.pdf\n", i, i);
				fprintf(compile, "pdftops -eps fig%0.4d.pdf fig%0.4d.eps\n", i, i);
				fprintf(compile, "convert fig%0.4d.eps fig%0.4d.jpg\n", i, i);
				fprintf(compile, "rm fig%0.4d.pdf\n", i);
				fprintf(compile, "rm fig%0.4d.eps\n", i);

				i++;
			}

			return result_continue;
		}
		case command_end:
		{
			fclose(compile);

			return result_continue;
		}
		default: return result_continue;
	}
}

short int step_time(short int command, struct step_time_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct step_time_data cmd_data;
	
	static struct run_parameters *p;
	static int *p_size;
	static short int *trigger;
	static struct step_trigger_parameters *trigger_parameters;
	static double *time;
	static struct step_time_parameters *time_parameters;
	
	switch (command)
	{
		case command_info: {printf("step_time\n"); return result_continue;}
		case command_insert:
		{
			memcpy (&cmd_data, command_data, sizeof(struct step_time_data));

			if (data_input(data, data_parameters, &p, &p_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_input(data, data_parameters, &trigger, &trigger_parameters, cmd_data.data_index_trigger, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &time, &time_parameters, sizeof(double)*((trigger_parameters->total)+1), sizeof(struct step_time_parameters), cmd_data.data_index_time, data_size)==1) return result_error;
			
			time_parameters->size=0;
			time_parameters->index=0;

			return result_continue;
		}
		case command_begin:
		{
			*(time+(time_parameters->index))=p->time;
			
			(time_parameters->size)+=sizeof(double);
			(time_parameters->index)++;

			return result_continue;
		}
		case command_run:
		{
			if (*trigger==1)
			{
				*(time+(time_parameters->index))=p->time;
				
				(time_parameters->size)+=sizeof(double);
				(time_parameters->index)++;
			}

			return result_continue;
		}
		default: return result_continue;
	}
}

short int step_trigger_steps(short int command, struct step_trigger_steps_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
/*
	static struct step_trigger_steps_data cmd_data;
	
	static struct run_parameters *p;
	static int *p_size;
	static short int *trigger;
	static struct step_trigger_parameters *trigger_parameters;
	
	switch (command)
	{
		case command_begin:
		{
			if (cmd_data.progress==1)
			{
				printf("Processing...      ");
				fflush(stdout);
			}
			return result_continue;
		}
		case command_end:
		{
			if (cmd_data.progress==1)
			{
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bDone                    \n");
				fflush(stdout);
			}
			return result_continue;
		}
		case command_info: {printf("step_trigger_steps\n"); return result_continue;}
		case command_insert:
		{
			memcpy (&cmd_data, command_data, sizeof(struct step_trigger_steps_data));

			if (data_input(data, data_parameters, &p, &p_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &trigger, &trigger_parameters, sizeof(short int), sizeof(struct step_trigger_parameters), cmd_data.data_index_trigger, data_size)==1) return result_error;
			
			trigger_parameters->total=(p->Nt)/cmd_data.steps_interval;
			trigger_parameters->current=0;
			trigger_parameters->steps=0;
			
			return result_continue;
		}
		case command_run:
		{
			if ((p->steps)%cmd_data.steps_interval==0)
			{
				*trigger=1;
				(trigger_parameters->current)++;
				trigger_parameters->steps=p->steps;

				if (cmd_data.progress==1)
				{
					printf("\b\b\b\b\b");
					printf("%4.1lf%%", 100*(trigger_parameters->current)/(double)(trigger_parameters->total));
					fflush(stdout);
				}
			}
			else *trigger=0;

			return result_continue;
		}
		default: return result_continue;
	}
*/
}

short int step_trigger_time(short int command, struct step_trigger_time_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct step_trigger_time_data cmd_data;
	
	static struct run_parameters *p;
	static int *p_size;
	static short int *trigger;
	static struct step_trigger_parameters *trigger_parameters;
	
	static double time_elapsed;
	
	switch (command)
	{
		case command_begin:
		{
			if (cmd_data.progress==1)
			{
				printf("Processing...      ");
				fflush(stdout);
			}
			return result_continue;
		}
		case command_end:
		{
			if (cmd_data.progress==1)
			{
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bDone                    \n");
				fflush(stdout);
			}
			return result_continue;
		}
		case command_info: {printf("step_trigger_time\n"); return result_continue;}

		case command_insert:
		{
			memcpy (&cmd_data, command_data, sizeof(struct step_trigger_time_data));

			if (data_input(data, data_parameters, &p, &p_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &trigger, &trigger_parameters, sizeof(short int), sizeof(struct step_trigger_parameters), cmd_data.data_index_trigger, data_size)==1) return result_error;
			
			trigger_parameters->total=(int)((p->maxtime)/cmd_data.time_interval);
			trigger_parameters->current=0;
			trigger_parameters->time=0;
			
			time_elapsed=0;
			
			return result_continue;
		}
		case command_run:
		{
			if (p->time-time_elapsed>cmd_data.time_interval)
			{
				*trigger=1;
				(trigger_parameters->current)++;
				time_elapsed+=cmd_data.time_interval;
				trigger_parameters->time=time_elapsed;

				if (cmd_data.progress==1)
				{
					printf("\b\b\b\b\b");
					printf("%4.1lf%%", 100*(trigger_parameters->current)/(double)(trigger_parameters->total));
					fflush(stdout);
				}
			}
			else *trigger=0;

			return result_continue;
		}
		default: return result_continue;
	}
}

short int step_trigger_time_once(short int command, struct step_trigger_time_once_data *command_data, void *data[], void *data_parameters[], short int data_size)
{
	static struct step_trigger_time_once_data cmd_data;
	
	static struct run_parameters *p;
	static int *p_size;
	static short int *trigger;
	static struct step_trigger_parameters *trigger_parameters;
	
	static short int already_triggered;

	switch (command)
	{
		case command_info: {printf("step_trigger_time_once\n"); return result_continue;}
		case command_insert:
		{
			memcpy (&cmd_data, command_data, sizeof(struct step_trigger_time_once_data));

			if (data_input(data, data_parameters, &p, &p_size, cmd_data.data_index_parameters, data_size)==1) return result_error;
			if (data_output(data, data_parameters, &trigger, &trigger_parameters, sizeof(short int), sizeof(struct step_trigger_parameters), cmd_data.data_index_trigger, data_size)==1) return result_error;
			
			trigger_parameters->total=cmd_data.runs;
			trigger_parameters->current=0;
			
			return result_continue;
		}
		case command_begin:
		{
			already_triggered=0;
			
			return result_continue;
		}
		case command_run:
		{
			if (p->time>=cmd_data.time && already_triggered==0)
			{
				*trigger=1;
				(trigger_parameters->current)++;

				already_triggered=1;
			}
			else *trigger=0;

			return result_continue;
		}
		default: return result_continue;
	}
}

