#include "shell.h"

int _strleni(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}

char **_getenvi(const char *var)
{
	int index, len;

	len = _strleni(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}


int _setenv(char *name, char *value, int overwrite)
{
	char **envi;
	int i = 0;
	char *token, *var, string[800];

	for (i = 0, envi = environ; envi[i]; i++)
	{
		strcpy(string, envi[i]);
		token = strtok(string, "=");
		if (!(strcmp(token, name)))
		{
			write(STDOUT_FILENO,"name exists !\n", 15);
			if (overwrite != 0)
			{
				var = malloc(strlen(name) + strlen(value) + 2);
				if (var == NULL)
				{
                    free(var);
					write(1, "Error_malloc_var\n", 17);
					return (-1);
				}
				strcpy(var, name);
				strcat(var, "=");
				strcat(var, value);

				envi[i] = malloc(strlen(name) + strlen(value) + 1);
				if (envi[i] == NULL)
				{
                    free(envi[i]);
					write(1, "Err_malloc_setenv\n", 18);
					return (-1);
				}
				strcpy(envi[i], var);
                free_loop(environ);
				environ = envi;
				free(var);
				free(envi[i]);
			}
			return (0);
		}
	}

	write(STDOUT_FILENO,"new_name !\n", 12);
	var = malloc(strlen(name) + strlen(value) + 1);
	if (var == NULL)
	{
		write(1, "Error_malloc_var\n", 17);
		return (-1);
	}
	strcpy(var, name);
	strcat(var, "=");
	strcat(var, value);
	printf("var_set\n");
	envi = malloc((i + 1) * sizeof(char *));
	if (envi == NULL)
	{
        free_loop(envi);
		write(1, "Error_malloc_envi\n", 18);
		return (-1);
	}
    free_loop(environ);
	envi = environ;
	envi[i] = malloc(strlen(name) + strlen(value) + 1);
	if (envi[i] == NULL)
	{
		write(1, "Err_malloc_setenv\n", 18);
		return (-1);
	}
	strcpy(envi[i], var);

	envi[i + 1] = NULL;
	environ = envi;

	free_loop(envi);
	free(var);
	return (0);
}

/**
 * _setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int _setenvi(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (0);

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (0);
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenvi(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (0);
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}


/**
 * _cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int _cd(char **args)
{
	char **dir_info;//, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[1])
	{
		if (*(args[1]) == '-' || _strcmp(args[1], "--") == 0)
		{
			if ((args[1][1] == '-' && args[1][2] == '\0') ||
					args[1][1] == '\0')
			{
				if (_getenvi("OLDPWD") != NULL)
                {
                    write(STDOUT_FILENO, "€##", 6);
					(chdir(*_getenvi("OLDPWD") + 7));
                }
			}
			else
			{
				free(oldpwd);
				return (0);
			}
		}
		else
		{
			if (stat(args[1], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[1]);
			else
			{
				free(oldpwd);
				return (0);
			}
		}
	}
	else
	{
		if (_getenvi("HOME") != NULL)
			chdir(*(_getenvi("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	/*dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (_setenv(dir_info[0], dir_info[1], 1) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (_setenv(dir_info[0], dir_info[1], 1) == -1)
		return (-1);
	if (args[1] && args[1][1] == '-' && args[1][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);*/
	return (0);
}