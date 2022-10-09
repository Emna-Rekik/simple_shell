#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void substring(char *orig, char *substr, int index, int length);

struct local_var
{
	char fist_operand[20]; 
	char second_operand[20];
};
struct local_var locals[100]; 

int main()
{
	int local = 0;
	while(1)
	{
		char buf[100];
		printf("prompt > ");
		fgets(buf, 100, stdin);
		int len = strlen(buf);
		buf[len -1] =0;

		if(strlen(buf) == 0)
			continue;
			
		int ret_pid = fork();
		
		if(ret_pid < 0)
		{
			printf("Fork Failed\n");
		}
		else if (ret_pid > 0)
		{
			int status;
			wait(&status);
			if (WEXITSTATUS(status) == 1)
			{
				// remove spaces from the buffer
				int count = 0;
				for(int i=0; i < buf[i]; i++)
					if(buf[i] != ' ')
						buf[count++] = buf[i];
				buf[count] = '\0';
				
				count = 0;
				while(buf[count] != '=')
				{
					count ++;
				}
				substring(buf, locals[local].fist_operand, 0, count);
				substring(buf, locals[local].second_operand, count+1, strlen(buf));
				local ++;
			}
			else if (WEXITSTATUS(status) == 2)
			{
				for(int i=0; i < local; i++)
				{
					printf("local_vars[%d]: %s = %s\n", i, locals[i].fist_operand, locals[i].second_operand);
				}
			}
			else if (WEXITSTATUS(status) == 3)
			{
				int count = 0;
				while(buf[count] != ' ')
				{
					count ++;
				}
				char global[20];
				substring(buf, global, count+1, strlen(buf));
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
		}
		else if (ret_pid == 0)
		{
			if (strchr(buf, '=') != NULL)
			{
				return 1;
			}
			
			if (strcmp(buf, "set") == 0)
			{
				return 2;
			}
			
			if (strstr(buf, "export"))
			{
				return 3;
			}
			
			char *newargv[50];
			char args [50][50];
			int arg = 0;
			// Substring the arguments
			int new_arg = 0; //we mean it's false
			for (int i=0; i < strlen(buf); i++)
			{
				int tmp = i;
				if (buf[i] != ' ')
				{
					new_arg = 1; //we got a new argument
				}
				if (new_arg)
				{
					new_arg = 0;
					while(buf[i] != ' ' && i < strlen(buf))
					{
						i++;
					}
					substring(buf, args[arg], tmp, i-tmp);
					newargv[arg] = &*args[arg];
					arg ++;
				}
			}
			newargv[arg] = NULL;
			execvp(newargv[0], newargv);
			printf("Exec Failed\n");
			return 9;
		}
			
	}
	return 0;
}

void substring(char *orig, char *substr, int index, int length)
{
	if(index >= strlen(orig))
	{
		substr[0] = '\n';
		return;
	}
	int c = 0;
	while (c < length && orig[index + 1] != '\n')
	{
		substr[c] = orig[index+c];
		c++;
	}
}
