#include <stdio.h>
#include <string.h>

#include "../headers/local_var_struct.h"

void print_local_variables(int local)
{
	for(int i=0; i < local; i++)
	{
		printf("local_vars[%d]: %s = %s\n", i, locals[i].fist_operand, locals[i].second_operand);
	}
}
