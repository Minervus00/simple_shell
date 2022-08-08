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

/**
*_strncpy - concatenates two strings
* @dest: string pointer
* @src: string pointer
* @n: bytes
* Return: pointer to the resulting string dest
*/
char *_strncpy(char *dest, char *src, int n)
{
		int i;

		for (i = 0; (i < n) && (*(src + i) != '\0'); i++)
				*(dest + i) = *(src + i);
		for (; i < n; i++)
				*(dest + i) = '\0';
		return (dest);
}

/**
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strncmp - Compare two strings.
 * @s1: Pointer to a string.
 * @s2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 *
 * Return: Less than 0 if s1 is shorter than s2.
 *         0 if s1 and s2 match.
 *         Greater than 0 if s1 is longer than s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}