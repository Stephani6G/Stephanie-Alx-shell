#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* Interactive mode */
int interactive(info_t *);

/* Check if character is a delimiter */
int is_delim(char, char *);

/* Check if a character is alphabetical */
int _isalpha(int);

/* Convert a string to an integer */
int _atoi(char *);

/* Convert string to an integer with error handling */
int _erratoi(char *);

/* Print an error message */
void print_error(info_t *, char *);

/* Print integers with specified format */
int print_d(int, int);

/* Convert a long integer to a string */
char *convert_number(long int, int, int);

/* Remove comments from a string */
void remove_comments(char *);

/* Exit shell */
int _myexit(info_t *);

/* Change current directory */
int _mycd(info_t *);

/* Display shell help information */
int _myhelp(info_t *);

/* Display command history */
int _myhistory(info_t *);

/* Display alias information */
int _myalias(info_t *);

/* Get user input and process it */
ssize_t get_input(info_t *);

/* Get a line of input from the user */
int _getline(info_t *, char **, size_t *);

/* Handle SIGINT signal (Ctrl+C) */
void sigintHandler(int);

/* Clear info_t structure */
void clear_info(info_t *);

/* Set info_t structure */
void set_info(info_t *, char **);

/* Free info_t structure */
void free_info(info_t *, int);

/* Get environment variable */
char *_getenv(info_t *, const char *);

/* Display environment variables */
int _myenv(info_t *);

/* Set environment variable */
int _mysetenv(info_t *);

/* Unset environment variable */
int _myunsetenv(info_t *);

/* Populate environment list */
int populate_env_list(info_t *);

/* Get environment variables as array */
char **get_environ(info_t *);

/* Unset environment variable */
int _unsetenv(info_t *, char *);

/* Set or modify environment variable */
int _setenv(info_t *, char *, char *);

/* Get history file path */
char *get_history_file(info_t *info);

/* Write history data to a file */
int write_history(info_t *info);

/* Read history data from a file */
int read_history(info_t *info);

/* Build a history list from a buffer */
int build_history_list(info_t *info, char *buf, int linecount);

/* Renumber history entries */
int renumber_history(info_t *info);

/* Add a node to a linked list */
list_t *add_node(list_t **, const char *, int);

/* Add a node to the end of a linked list */
list_t *add_node_end(list_t **, const char *, int);

/* Print a linked list of strings */
size_t print_list_str(const list_t *);

/* Delete a node at a specified index in a linked list */
int delete_node_at_index(list_t **, unsigned int);

/* Free the memory of a linked list */
void free_list(list_t **);


/* list_len - Get the length of a linked list
 * This function calculates and returns the number of elements in the linked list.
 */
size_t list_len(const list_t *list);

/* list_to_strings - Convert a linked list to an array of strings
 * This function converts the elements of a linked list into an array of strings.
 */
char **list_to_strings(list_t *list);

/* print_list - Print the elements of a linked list
 * This function prints the elements of the linked list to the standard output.
 */
size_t print_list(const list_t *list);

/* node_starts_with - Find the first node that starts with a given character
 * This function searches for the first node in the list that starts with the specified character or string.
 */
list_t *node_starts_with(list_t *list, char *str, char c);

/* get_node_index - Get the index of a specific node in a linked list
 * This function determines the index (position) of a specific node in the linked list.
 */
ssize_t get_node_index(list_t *list, list_t *node);




/* is_chain - Check if a chain of variables exists
 * This function checks if a chain of variables exists in the provided character array.
 */
int is_chain(info_t *info, char *var, size_t *n);
/* check_chain - Check a chain of variables against given criteria
 * This function checks if a chain of variables meets certain size criteria.
 */
void check_chain(info_t *info, char *var, size_t *n, size_t min_size, size_t max_size);
/* replace_alias - Replace alias variables with their values
 * This function replaces alias variables in the info_t structure with their corresponding values.
 */
int replace_alias(info_t *info);
/* replace_vars - Replace variables with their values
 * This function replaces variables in the info_t structure with their corresponding values.
 */
int replace_vars(info_t *info);
/* replace_string - Replace all occurrences of a substring in an array of strings
 * This function replaces all occurrences of the target substring in each string of the array.
 */
int replace_string(char **array, char *target);


#endif
