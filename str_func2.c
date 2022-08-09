#include "shell.h"

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

/**
* _strcmpi - compares two strings
* @s1: string to compare
* @s2: string to compare
* Return: difference
*/
int _strcmpi(char *s1, const char *s2)
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