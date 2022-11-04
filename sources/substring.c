#include <string.h>

void substring(char orig[], char substr[], int index, int length)
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
