#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "headers/functions_headers.h"
#include "headers/local_var_struct.h"
#include "headers/remove_spaces.h"
#include "headers/substring.h"

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

		if (strchr(buf, '=') != NULL)
		{
			local = assign_local_variables(buf, local);
			continue;
		}
		else if (strcmp(buf, "set") == 0)
		{
			print_local_variables(local);
			continue;
		}
		else if (strstr(buf, "export"))
		{
			export_local_variables(buf, local);			
			continue;
		}

		int ret_pid = fork();

		if(ret_pid < 0)
		{
			printf("Fork Failed\n");
		}
		else if (ret_pid > 0)
		{
			int status;
			wait(&status);

		}
		else if (ret_pid == 0)
		{
			if (strchr(buf, '>') != NULL)
			{
				int count = 0;
				while(buf[count] != '>')
				{
					count ++;
				}
				char global[10];
				substring(buf, global, count+1, strlen(buf));
				remove_spaces(global);

				int dest_fd = open(global, O_CREAT | O_WRONLY, 0644);
				if (dest_fd == -1)
				{
					printf("Error msg: Failed to create and open the file\n");
				}
				dup2(dest_fd,1); // 1 pour STDOUT
				close(dest_fd);
				
				char global2[40];
				substring(buf, global2, 0, count);
				strcpy(buf, global2);
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
			if (strcmp(newargv[0],"cat") == 0 && (newargv[1][0] != '.' && newargv[1][0] != '/'))
			{
				char dest[] = "./";
				strcat(dest, newargv[1]);
				strcpy(newargv[1], dest);
				remove_spaces(newargv[1]);
			}

			newargv[arg] = NULL;
			execvp(newargv[0], newargv);
			printf("Exec Failed\n");
			return 9;
		}

	}
	return 0;
}
