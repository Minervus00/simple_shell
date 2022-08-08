#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

void printenv(void)
{
	int i = 0;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * _getenv - ooo
 * @name: gg
 *
 * Return: char *
 */
char *_getenv(const char *name)
{
	int i;
	char *token, *resu, string[800];

	for (i = 0; environ[i]; i++)
	{
		strcpy(string, environ[i]);
		token = strtok(string, "=");
		/*printf("name = %s & token = %s\n", name, token);*/
		if (!(strcmp(name, token)))
		{
			resu = strchr(environ[i], '=');
			return (strchr(resu, resu[1]));
		}

	}
	return (NULL);
}

void printenv_var(const char *name)
{
	printf("%s = %s\n", name, _getenv(name));
}

int _setenv(const char *name, const char *value, int overwrite)
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
			printf("name exists !\n");
			if (overwrite != 0)
			{
				var = malloc(strlen(name) + strlen(value) + 2);
				if (var == NULL)
				{
					write(1, "Error_malloc_var\n", 17);
					return (-1);
				}
				strcpy(var, name);
				strcat(var, "=");
				strcat(var, value);

				envi[i] = malloc(strlen(name) + strlen(value) + 1);
				if (envi[i] == NULL)
				{
					write(1, "Err_malloc_setenv\n", 18);
					return (-1);
				}
				strcpy(envi[i], var);

				environ = envi;
				free(var);
				free(envi[i]);
			}
			return (0);
		}
	}

	printf("new_name !\n");
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
		write(1, "Error_malloc_envi\n", 18);
		return (-1);
	}
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
	
	free(envi);
	printf("oooo\n");
	/*free(envi[i]);
	printf("oooo\n");*/
	free(var);
	printf("oooo\n");
	return (0);
}

int _unsetenv(const char *name)
{
	char *token, **envi, string[800];
	int i;

	for (i = 0, envi = environ; envi[i]; i++)
	{
		strcpy(string, envi[i]);
		token = strtok(string, "=");
		if (!(strcmp(token, name)))
		{
			printf("name exists !\n");
			while (envi[i])
			{
				envi[i] = envi[i + 1];
				i++;
			}
			environ = envi;
			break;
		}
	}
	return (0);
}

int main(void)
{

	/*printenv_var("LANG");
	printenv_var("PwD");
	printenv_var("OLDPWD");
	printenv_var("USER");
	pathdirs();*/
	_setenv("A_NAME", "MINRV", 0);
	printenv();
	printenv_var("A_NAME");
	_setenv("A_NAME", "FUNNNyy", 1);
	printenv();
	/*printenv_var("A_NAME");
	_setenv("A_NAMEDD", "FUvvvvNyy", 1);
	printf("yyoo\n");
	printenv_var("A_NAMEDD");
	_unsetenv("A_NAME");
	printenv_var("A_NAME");
	printenv();*/
	return (0);
}
