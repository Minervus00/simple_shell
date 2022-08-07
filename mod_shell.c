#include "shell.h"

void print_error(void)
{
	write(1, "./shell: No such file or directory\n", 35);
}

int main()
{
	size_t size = 10, bytes_read, count = 0;
	char *comd;
	int exit_st = 0;
	

	comd = malloc(size);
	if (comd == NULL)
	{
		puts("Error !");
		return (1);
	}

	if (!isatty(STDIN_FILENO))
	{
		bytes_read = _getline(&comd, &size, stdin);
		if (bytes_read == (long unsigned int)-1)
			printf("ERROR_getline !\n");

		else
			execute_line(comd, count, environ, exit_st, &exit_st);
			
		return (0);
	}
		
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "#cisfun$ ", 10);
		bytes_read = _getline(&comd, &size, stdin);
		if (bytes_read == (long unsigned int)-1)
			printf("ERROR_getline !\n");

		else
			execute_line(comd, count, environ, exit_st, &exit_st);
	}
	free(comd);
	return (0);
}
