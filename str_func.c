#include "shell.h"
/**
* _strlen - return length of a string
* @s: char type
* Return: length of string
*/
int _strlen(char *s)
{
		int len;

		len = 0;
		while (s[len] != '\0')
			len++;
		return (len);
}
/**
 * _strtr - clone of strstr
 * @haystack: string to be scanned
 * @needle: small string tobe searched in haystack
 *
 * Return: pointer to the first occurrence in haystack or NULL
 */
char *_strstr(char *hay, char *need)
{
	int i, j, lh = _strlen(hay), ln = _strlen(need);

	if (ln > lh)
		return (NULL);

	for (i = 0; i < lh; i++)
	{
		if ((int) hay[i] == (int) need[0])
		{
			for (j = 1; j < ln; j++)
			{
				if ((int) hay[i + j] != (int) need[j])
					break;
			}
			if (j == ln)
				return (hay + i);
		}
	}
	return (NULL);
}
/**
 *_strcat - concatenates two strings
 *@s1: point to string
 *@s2: point to string
 *Return: pointer to point a newly allocated
 */
char *_strcat(char *s1, char *s2)
{
		char *cat;
		int i, j, k;

		for (i = 0; s1 && s1[i]; ++i)
				;
		for (j = 0; s2 && s2[j]; ++j)
				;
		cat = (char *)malloc((i + j + 1) * sizeof(char));
		if (cat == NULL)
				return (NULL);
		k = 0;
		for (i = 0; s1 && s1[i]; ++i)
		{
				cat[k] = s1[i];
				++k;
		}
		for (j = 0; s2 && s2[j]; ++j)
		{
				cat[k] = s2[j];
				++k;
		}
		cat[k] = '\0';
		return (cat);
}
/**
*_strdup - returns a pointer to a newly allocated space in memory
*@str: string given as a parameter
*Return:  pointer to the duplicated string or NULL
*/
char *_strdup(char *str)
{
		int i, j;
		char *dup;

		if (str == NULL)
				return (NULL);
		for (i = 0; str[i]; i++)
				;
		dup = (char *)malloc((i + 1) * sizeof(char));
		if (dup == NULL)
				return (dup);
		for (j = 0; j <= i; ++j)
				dup[j] = str[j];
		return (dup);
}
/**
* _strcmp - compares two strings
* @s1: string to compare
* @s2: string to compare
* Return: difference
*/
int _strcmp(char *s1, char *s2)
{
		while (1)
		{
				if (*s1 != *s2)
						return (*s1 - *s2);
				if (*s1 == '\0')
						return (0);
				s1++;
				s2++;
		}
}
