void remove_spaces(char buffer[])
{
	// remove spaces from the buffer
	int count = 0;
	for(int i=0; i < buffer[i]; i++)
		if(buffer[i] != ' ')
			buffer[count++] = buffer[i];
	buffer[count] = '\0';
}
