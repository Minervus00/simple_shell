#include "shell.h"

/**
*_execute - function that executes in the main shell
*@argv: argument char-pointers array
*@commands: split arguments
*@count: count of commands that were run
*@env: the environment
*@exit_st: exit status
*@line: buffer of getline
*/
int execute_line(char *comd, int count,
		  char **env, int exit_s, int *exit_st)
{
	pid_t r_pid;
	int status;
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
            _error(argv, argv[0], count, &exit_st);
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
