#include <shell.h>

int func_separator(char *comd)
{
	char *tok, sepa[3][2] = {";", "||", "&&"}, comds[10][100];
	int i = 0, j = 0, h = 0;

	for (i = 0; sepa[i]; i++)
	{
		tok = strtok(comd, sepa[i]);
		if (tok)
		{
			while (tok)
			{
				if (i == 0)
					execute_line(tok, 1, environ, h, &h);
				else if (i == 2)
				{
					/*Suppose que execute_line return 0 en cas de success
					  D'où en cas de suucès on arrête l'exécution*/
					if (!execute_line(tok, 1, environ, h, &h));
						return (1);
				}
				else
				{
					/*En cas d'erreur (execute_line return != 0) on arrête l'exécution*/
					if(execute_line(tok, environ, h, &h))
						return (1);
				}


				tok= strtok(NULL, sepa[i]);
				j++;
			}
			if (i == 0)
				return (1);
			break;
		}
	}
	return (0);
}	