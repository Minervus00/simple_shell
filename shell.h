#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define TOK_DELIM " \t\r\n\v\a"
extern char **environ;
/**
* struct list_path - singly linked list
* @dir: string - (malloc'ed string)
* @next: points to the next node
*
* Description: singly linked list node structure
* for directories of PATH
*/
typedef struct list_path
{
	char *dir;
	struct list_path *next;
} list_p;

/*Functions of the shell*/
int execute_line(char **av, char *comd, int count, char **env, int *exit_st);
char **split_line(char *line);
list_p *list_path(char **env);
char *_which(char **commands, char **env);
void built_exit(char *line, char **arg, int *exit_st, int count);
void built_env(char **arg, char **env, int *exit_st);
char *_getenv(const char *name, char **env);
void _error(char **argv, char *first, int count, int **exit_st);
void print_num(int count);
int func_separator(char **av, char *comd);
int special_case(char *line, ssize_t line_len, int *exit_st);

/*useful functions*/
int _strlen(char *s);
void add_node_end(list_p **head, const char *str);
char *_strcat(char *s1, char *s2);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
void free_loop(char **arr);
void free_list(list_p *head);
char *_strncpy(char *dest, char *src, int n);
char *_strcpy(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strstr(char *hay, char *need);
int _strcmpi(char *s1, const char *s2);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char **_strtok(char *line, char *delim);
char *_strtoki(char *str, const char *delimitador);
int _cd(char **args);
#endif /* SHELL_H*/
