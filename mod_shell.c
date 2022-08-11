#include "shell.h"


/**
 * print_error - print an error
 */
void print_error(void)
{
	write(1, "./shell: No such file or directory\n", 35);
}

/**
 * signal_handler - handle signals
 */
void signal_handler(int signal __attribute__((unused)))
{
	write(STDOUT_FILENO, "\n$ ", 3);
}
/**
 * main - the main function
 * Return: int
 */

int main(int ac, char **av)
{
	size_t size = 1048576, bytes_read = 0, count = 0;
	char *comd = NULL;
	int exit_st = 0;
	(void)ac;

	comd = malloc(size);
	if (comd == NULL)
	{
		write(1, "Error !\n", 8);
		return (1);
	}

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "$ ", 3);
		signal(SIGINT, signal_handler);
		bytes_read = _getline(&comd, &size, stdin);
		/*if (bytes_read == (unsigned int long)-1)
			printf("ERROR_getline !\n");*/
		if (special_case(comd, bytes_read, &exit_st) == 3)
			continue;
		else
		{
			if (!func_separator(av,comd))
				execute_line(av,comd, count, environ, &exit_st);
		}
		fflush(stdin);
	}
	free(comd);
	return (0);
}
