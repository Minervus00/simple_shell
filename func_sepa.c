#include "shell.h"

/**
 * func_separator - manage ; || &&
 * @comd: the whole command
 *
 * Return: 0 if there are no separators, 1 otherwise
 */
int func_separator(char *comd)
{
	char **tok, *sepa[] = {";", "||", "&&"};
	int i, j = 0, h = 0;

	for (i = 0; i < 3; i++)
	{
		if (_strstr(comd, sepa[i]))
		{
			tok = _strtok(comd, sepa[i]);
			while (tok[0])
			{
				if (i == 0)
					execute_line(tok[0], 1, environ, h, &h);
				else if (i == 1)
				{
					 /**
					  * Execute_line return 0 en cas de success
					  * D'où en cas de succès on arrête l'exécution
					  */
					if (execute_line(tok[0], 1, environ, h, &h) == 0)
						return (1);
				}
				else
				{
					/*En cas d'erreur (execute_line return != 0) on arrête l'exécution*/
					if (execute_line(tok[0], 1, environ, h, &h))
						return (1);
				}
				tok++;
				j++;
			}
			return (1);
		}
	}
	/*printf("func_nooo_sepa\n");*/
	return (0);
}
