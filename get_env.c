#include "shell.h"

/**
 * _getenv - gets an environment variable.
 * @name: name of the environment variable.
 * @env: environ.
 * Return: the value of the variable searched.
 */
char *_getenv(const char *name, char **env)
{
	char *comp = NULL;
	int i;

	if (env == NULL)
		return (NULL);
	for (i = 0; env[i]; i++)
	{
		comp = _strtok(env[i], "=")[0];
		if (_strcmpi(comp, name) == 0)
		{
			return (_strtok(_strtok(env[i], "=")[1], "\n")[0]);
		}
	}
	return (NULL);
}