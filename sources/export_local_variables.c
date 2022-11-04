#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/substring.h"
#include "../headers/remove_spaces.h"
#include "../headers/local_var_struct.h"

void export_local_variables(char buffer[], int local)
{
	int count = 0;
	while(buffer[count] != ' ')
	{
		count ++;
	}
	char global[20];
	substring(buffer, global, count+1, strlen(buffer));
	int exist = 0;
	int i =0;
	while(i < local && exist == 0)
	{
		if (strcmp(locals[i].fist_operand, global) == 0)
		{
			exist = 1;
		}
		i++;
	}
	if (exist)
	{
		setenv(locals[i-1].fist_operand, locals[i-1].second_operand, 1);
	}
	else
	{
		printf("Could not export [%s], variable does not exist!\n", global);
	}
}
