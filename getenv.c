#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * _getenv - ooo
 * @name: gg
 *
 * Return: char *
 */
char *_getenv(const char *name)
{
	extern char **environ;
	int i, len;
	char *token, *resu, *string=NULL;

	for (i = 0; environ[i]; i++)
	{
		len = strlen(environ[i]);
		string = malloc(len * sizeof(char));
		if (string == NULL)
		{
			write(1, "Error_malloc_string\n", 20);
			return (NULL);
		}
	
		strcpy(string, environ[i]);
		token = strtok(string, "=");
		/*printf("name = %s & token = %s\n", name, token);*/
		if (!(strcmp(name, token)))
		{
			resu = strchr(environ[i], '=');
			free(string);
			return (strchr(resu, resu[1]));
		}
		else
			free(string);

	}
	return (NULL);
}

void printenv_var(const char *name)
{
	printf("%s = %s\n", name, _getenv(name));
}

int pathdirs(void)
{
	char *var = _getenv("PATH"), *token;

	token = strtok(var, ":");
	while (token)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}
	return (0);
}

int _setenv(const char *name, const char *value, int overwrite)
{
	extern char **environ;
	int i = 0, len;
	char *buff, *token, *namer, *string;

	for (i = 0; environ[i]; i++)
	{
		len = strlen(environ[i]);
		string = malloc(len * sizeof(char));
		if (string == NULL)
		{
			write(1, "Error_malloc_string\n", 20);
			return (-1);
		}
	
		strcpy(string, environ[i]);
		token = strtok(string, "=");
		printf("name = %s & token = %s\n", name, token);
		if (!(strcmp(environ[i], name)))
		{
			printf("name exists !\n");
			if (overwrite != 0)
			{
				namer = strchr(name, name[0]);
				buff = strcat(namer, "=");
				buff = strcat(buff, value);
				strcpy(environ[i], buff);
				printf("update: %s\n", environ[i]);
			}
			free(string);
			return (0);
		}
		free(string);
	}
	printf("yooo\n");
	namer = strchr(name, name[0]);
	buff = strcat(namer, "=");
	buff = strcat(buff, value);
	strcpy(environ[i], buff);
	printf("update: %s\n", environ[i]);
	printf("yess!\n");

	environ[i + 1] = NULL;
	return (0);
}

int main(void)
{

	/*printenv_var("LANG");
	printenv_var("PwD");
	printenv_var("OLDPWD");
	printenv_var("PATH");
	pathdirs();*/
	printf("ret = %d\n", _setenv("NAME", "MINRV", 0));

	return (0);
}
