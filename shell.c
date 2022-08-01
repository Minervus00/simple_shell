#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
int init_shell(void)
{

}
*/
int main(void)
{
	size_t size = 10, bytes_read;
	char *comd, buff[20], *token, **argv;
	int i, j, n, status;
	pid_t r_pid;

	comd = malloc(size);
	if (comd == NULL)
	{
		puts("Error !");
		return (1);
	}
	while (size != 0)
	{
		r_pid = fork();
		if (r_pid == -1)
		{
			write(1, "Error_fork\n", 11);
			return (-1);
		}

		else if (r_pid == 0)
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
				argv = malloc(n * sizeof(char *));
				while(token != NULL)
				{
					/*argv[i] = ((i == 0) ? strcat("/bin/", token) : token);*/
					if (i == n)
					{
						n += 5;
						argv = realloc(argv, n * sizeof(char *));
					}

					size = strlen(token);
					if (i == 0)
					{
						argv[i] = malloc(size + 5) ;
						strcpy(buff, "/bin/");
						argv[i] = strcat(buff, token);
					}
					else
					{
						argv[i] = malloc(size);
						argv[i] = token;
					}
				
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

				if (execve(argv[0], argv, NULL) == -1)
				{
					write(1, "Error_exec !\n", 13);
				}
			}
		}
		else
			wait(&status);
	}
	free(comd);
	return (0);
}
