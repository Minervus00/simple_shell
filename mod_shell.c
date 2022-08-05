#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int _printenv(void);
char *_getenv(const char *name);


char *check_cmd(char *command)
{
	struct stat st;
	char *sample, *path, *compy;

	printf("INN\n");
	if (stat(command, &st) == 0)
		return (command);
	
	printf("not first\n");
	path = _getenv("PATH");
	compy = malloc(strlen(command));
	strcpy(compy, command);
	sample = strtok(path, ":");
	command = strcat(strcat(sample, "/"), compy);
	while(sample)
	{
		if (stat(command, &st) != 0)
		{
			sample = strtok(NULL, ":");
			if (sample == NULL)
				command = NULL;
			else
			{
				command = strcat(strcat(sample, "/"), compy);
			}
		}
		else
			break;
	}
	free(compy);
	return (command);
}

void print_error(void)
{
	write(1, "./shell: No such file or directory\n", 35);
}

int main(void)
{
	size_t size = 10, bytes_read;
	char *comd, *token, **argv;
	int i, j, n, status;
	pid_t r_pid;

	comd = malloc(size);
	if (comd == NULL)
	{
		puts("Error !");
		return (1);
	}
	while (1)
	{
		i = 0;
		n = 10;
		printf("#cisfun$ ");
		bytes_read = getline(&comd, &size, stdin);
		if (bytes_read == (long unsigned int) -1)
			printf("ERROR_getline !\n");

		else
		{
			comd = strtok(comd, "\n");
			token = strtok(comd, " ");
			printf("Check_cmd\n");
			token = check_cmd(token);
			if (token != NULL)
			{
				argv = malloc(n * sizeof(char *));
				/*argv[0] = malloc(strlen(token));
				argv[0] = token;*/
			}

			else
			{
				print_error();
				continue;
			}

			/*argv[i] = ((i == 0) ? strcat("/bin/", token) : token);*/
			if (i == n)
			{
				n += 5;
				argv = realloc(argv, n * sizeof(char *));
			}
			
			while (token)
			{
				size = strlen(token);
				argv[i] = malloc(size);
				argv[i] = token;
				token = strtok(NULL, " ");
				i++;
			}
			argv = realloc(argv, (i + 1) * sizeof(char *));
			argv[i] = NULL;
			/*printf("argv[0] = %s\n", argv[0]);*/

			for (j = 0; j <= i; j++)
			{
				printf("%s\n", ((argv[j] == NULL) ? "(nil)" : argv[j]));
			}
			
			/**1. Add getenv function above before testing**/
			/**2. Check if command is unique (i == 1) and implement exit and printenv commands before execve !**/
			if (i == 1)
			{
				if (!(strcmp(argv[0], "exit")))
					return (0);
				else if (!(strcmp(argv[0], "env")))
				{
					_printenv();
					free(argv);
					continue;
				}
			}

			r_pid = fork();
			if (r_pid == -1)
			{
				write(1, "Error_fork\n", 11);
				return (-1);
			}

			else if (r_pid == 0)
			{
				if (execve(argv[0], argv, NULL) == -1)
				{
					print_error();
				}
			}
	
			else
				wait(&status);
		}
	}
	free(comd);
	return (0);
}
