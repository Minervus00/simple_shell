#include "shell.h"

/**
*execute_line - function that executes a line
*@comd: argument char-pointers array
*@count: count of commands that were run
*@env: the environment
*@exit_st: exit status
*Return: int
*/
int execute_line(char **av, char *comd, int count,
		  char **env, int *exit_st)
{
	pid_t r_pid;
	int status;
    int exit_s = 0;
	char *full_path = NULL, **argv;

	argv = split_line(comd);
	count++;
	if (_strcmp("exit", *argv) == 0)
		built_exit(comd, argv, &exit_s, count);
	else if (_strcmp("env", *argv) == 0)
		built_env(argv, environ, &exit_s);
	else if (_strcmp("cd", argv[0]) == 0)
	{
		return (_cd(argv));
	}
	else
	{
		r_pid = fork();
		if (r_pid < 0)
			perror("Error:");
		if (r_pid == 0)
		{
			full_path = argv[0];
			if (**argv != '/' && _strcmp(argv[0], "..") != 0)
				full_path = _which(argv, env);
			if (full_path)
			{
				if (access(full_path, X_OK) == 0)
					execve(full_path, argv, env);
			}
			_error(av, argv[0], count, &exit_st);
            free(full_path);
			free_loop(argv);
			free(comd);
			exit(*exit_st);
		}
		else
		{
			wait(&status);
			free_loop(argv);
            *exit_st = WEXITSTATUS(status);
			if (*exit_st != 0)
				return (-1);
		}
	}
	return (0);
}
