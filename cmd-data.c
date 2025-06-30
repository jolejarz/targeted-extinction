/**************************************************************
***************************************************************
*** 
***   cmd-data.c
***
***   Jason Olejarz
***   2011-01-26
***
***   This file contains commands for manipulating data.
***
***************************************************************
**************************************************************/

void cmd_cnt()
{
        short int data_index=arg_short_int[0];
        double min=arg_double[0];
        double max=arg_double[1];

        double *data_list_double;

        int *data_list_parameters;

        int data_number, i;

        int count=0;

        if (data_input(data, data_parameters, &data_list_double, &data_list_parameters, data_index, data_num)==1) return;
        data_number=*data_list_parameters/sizeof(double);

        for (i=0; i<data_number; i++)
        {
                if (*(data_list_double+i)>=min && *(data_list_double+i)<=max) count++;
        }

	printf("%d\n", count);

	return;
}

void cmd_dd()
{
	data_delete(data, data_parameters, arg_short_int[0], data_num);
	return;
}

void cmd_disp()
{
	short int data_index=arg_short_int[0];
	int min=arg_int[0];
	int max=arg_int[1];
	
	double *data_list_double;
	
	void *data_list_parameters;
	
	if (data_input(data, data_parameters, &data_list_double, &data_list_parameters, data_index, data_num)==1) return;
	
	int i;
	
	for (i=min; i<=max; i++)
	{
		printf("%.10lf\n", *(data_list_double+i));
	}
	
	return;
}

void cmd_dt()
{
	// Delete all entries from the tag list
	tag(0, 0, 0, data_num);
	return;
}

void cmd_flt()
{
        short int data_index=arg_short_int[0];
        double min=arg_double[0];
        double max=arg_double[1];

        double *input[data_num/2], *output[data_num/2];
        int *input_size[data_num/2], *output_size[data_num/2];

        struct tag_data a=tag(2, 0, 0, data_num);

        int i, j, k, output_index=0, count=0;

        for (i=0; i<data_num/2; i++)
        {
                if (a.data_input[i]!=a.data_output[i])
                {
                        if (data_input(data, data_parameters, &input[i], &input_size[i], a.data_input[i], data_num)==1) return;
                        if (data_output(data, data_parameters, &output[i], &output_size[i], *input_size[i], sizeof(int), a.data_output[i], data_num)==1) return;

                        *output_size[i]=*input_size[i];

                        if (a.data_input[i]==data_index) j=i;

                        count++;
                }
                else break;
        }

        for (i=1; i<count; i++)
        {
                if (*input_size[i]!=*input_size[i-1])
                {
                        printf("The sizes of all tagged input arrays must be the same.\n");
                        return;
                }
        }

        int data_number_input=*input_size[j]/sizeof(double);

        for (i=0; i<data_number_input; i++)
        {
                if (*(input[j]+i)>=min && *(input[j]+i)<=max)
                {
                        for (k=0; k<count; k++)
                        {
                                *(output[k]+output_index)=*(input[k]+i);
                        }
                        output_index++;
                }
        }

        int data_number_output=output_index*sizeof(double);

        for (i=0; i<count; i++)
        {
                *output_size[i]=data_number_output;
        }

        printf("%d numbers were written to each of the output data blocks.\n", output_index);

        return;
}

void cmd_minmax()
{
        short int data_index=arg_short_int[0];

        double *input;
        int *input_size;
        int data_number;

        if (data_input(data, data_parameters, &input, &input_size, data_index, data_num)==1) return;
        data_number=*input_size/sizeof(double);

        double min;
        double max;

        int i;

        min=*input;
        max=*input;
        for (i=1; i<data_number; i++)
        {
                if (*(input+i)<min) min=*(input+i);
                if (*(input+i)>max) max=*(input+i);
        }

        printf("min=%lf, max=%lf\n", min, max);

        return;
}

void cmd_sd()
{
	int i;
	
	for (i=0; i<data_num; i++)
	{
		printf("%d  ", i);
		if (data[i]!=0) printf("occupied\n"); else printf("free\n");
	}
	
	return;
}

void cmd_tag()
{
        short int data_index_input=arg_short_int[0];
        short int data_index_output=arg_short_int[1];
    
        // Add the data block to the tag list.
        tag(1, data_index_input, data_index_output, data_num);
    
        return;
}

