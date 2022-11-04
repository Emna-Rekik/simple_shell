#include <string.h>

#include "../headers/local_var_struct.h"
#include "../headers/remove_spaces.h"
#include "../headers/substring.h"

int assign_local_variables(char buffer[], int local)
{
	remove_spaces(buffer);

	int count = 0;
	while(buffer[count] != '=')
	{
		count ++;
	}
	substring(buffer, locals[local].fist_operand, 0, count);
	substring(buffer, locals[local].second_operand, count+1, strlen(buffer));
	local ++;
	
	return local;
}
