#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define TOK_DELIM " \t\r\n\v\a"


int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int token_len(char *str, char *delim)
{
	int index = 0, len = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		len++;
		index++;
	}

	return (len);
}

/**
 * count_tokens - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[index];
			index++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}

char **split_line(char *line)
{
	int j = 0;
	char *token;
	char *token_hash;
	char **word_arr;
	int len, i;

	len = strlen(line);

	word_arr = malloc(sizeof(char *) * (len + 1));
	if (word_arr == NULL)
		return (NULL);
	token_hash = strtok(line, "#");
	token = strtok(token_hash, TOK_DELIM);
	while (token != NULL)
	{
		word_arr[j] = malloc(strlen(token) + 1);
		if (word_arr[j] == NULL)
		{
            for (i = 0; word_arr[i]; i++)
			    free(word_arr[i]);
			return (NULL);
		}
		strncpy(word_arr[j], token, strlen(token) + 1);
		token = strtok(NULL, TOK_DELIM);
		j++;
	}
	word_arr[j] = NULL;
	return (word_arr);
}

int main(void)
{
    char **arg, **arv;
    int i;
    (void)arv;
    arg = _strtok("ls -l s", " ");
    //arv = split_line("ls");
    for (i = 0; arg[i]; i++)
    {
        printf("%s#\n", arg[i]);
    }

    /*for (i = 0; i< 2; i++)
    {
        printf("%s#\n", arv[i]);
    }*/
}