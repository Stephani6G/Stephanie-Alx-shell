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

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* _myexit - Exit the shell
 * This function is used to exit the shell gracefully.
 */
int _myexit(info_t *info);
/* _mycd - Change the current directory
 * This function is used to change the current working directory.
 */
int _mycd(info_t *info);
/* _myhelp - Display shell help information
 * This function displays help information about the shell and its commands.
 */
int _myhelp(info_t *info);



/* _myhistory - Display command history
 * This function displays the command history from the info_t structure.
 */
int _myhistory(info_t *info);
/* _myalias - Display alias information
 * This function displays alias information stored in the info_t structure.
 */
int _myalias(info_t *info);



/* get_input - Get user input and process it
 * This function retrieves user input, processes it, and updates the info_t structure accordingly.
 */
ssize_t get_input(info_t *info);
/* _getline - Get a line of input from the user
 * This function reads a line of input from the user and stores it in the provided buffer.
 */
int _getline(info_t *info, char **line, size_t *n);
/* sigintHandler - Handle the SIGINT signal
 * This function is a signal handler for the SIGINT signal (Ctrl+C).
 */
void sigintHandler(int signo);


/* clear_info - Clear the content of an info_t structure
 * This function clears the content of the specified info_t structure.
 */
void clear_info(info_t *info);
/* set_info - Set the content of an info_t structure
 * This function sets the content of the info_t structure, including the environment variables.
 */
void set_info(info_t *info, char **environ);
/* free_info - Free the memory of an info_t structure
 * This function frees the memory of the specified info_t structure and its environment variables.
 */
void free_info(info_t *info, int free_environ);





/* _getenv - Get the value of an environment variable
 * This function retrieves the value of the specified environment variable.
 */
char *_getenv(info_t *info, const char *name);
/* _myenv - Display the environment variables
 * This function displays the environment variables contained in the info_t structure.
 */
int _myenv(info_t *info);
/* _mysetenv - Set an environment variable
 * This function allows setting or modifying environment variables using the info_t structure.
 */
int _mysetenv(info_t *info);
/* _myunsetenv - Unset an environment variable
 * This function allows unsetting (removing) environment variables using the info_t structure.
 */
int _myunsetenv(info_t *info);
/* populate_env_list - Populate an environment list from the system's environment
 * This function creates an environment list in the info_t structure based on the system's environment.
 */
int populate_env_list(info_t *info);




/* get_environ - Get the environment variables as an array of strings
 * This function retrieves the environment variables as an array of strings.
 */
char **get_environ(info_t *info);
/* _unsetenv - Unset an environment variable
 * This function unsets (removes) the specified environment variable.
 */
int _unsetenv(info_t *info, char *name);
/* _setenv - Set or modify an environment variable
 * This function sets or modifies the specified environment variable to the given value.
 */
int _setenv(info_t *info, char *name, char *value);



/* get_history_file - Get the history file path
 * This function returns the path to the history file associated with the info_t structure.
 */
char *get_history_file(info_t *info);
/* write_history - Write history data to a file
 * This function writes the history data from the info_t structure to a file.
 */
int write_history(info_t *info);
/* read_history - Read history data from a file
 * This function reads history data from a file and populates the info_t structure with it.
 */
int read_history(info_t *info);
/* build_history_list - Build a history list from a buffer
 * This function constructs a history list from the provided buffer and updates the info_t structure.
 */
int build_history_list(info_t *info, char *buf, int linecount);
/* renumber_history - Renumber history entries
 * This function renumbers history entries to ensure they are sequential.
 */
int renumber_history(info_t *info);




/* add_node - Add a new node at the beginning of a linked list
 * This function adds a new node with the specified string and length at the beginning of the linked list.
 */
list_t *add_node(list_t **head, const char *str, int len);
/* add_node_end - Add a new node at the end of a linked list
 * This function adds a new node with the specified string and length at the end of the linked list.
 */
list_t *add_node_end(list_t **head, const char *str, int len);

size_t print_list_str(const list_t *h);
/* delete_node_at_index - Delete a node at a specified index in a linked list
 * This function deletes the node at the specified index in the linked list.
 */
int delete_node_at_index(list_t **head, unsigned int index);
/* free_list - Free the memory of a linked list and its nodes
 * This function frees the memory allocated for the linked list and all of its nodes.
 */
void free_list(list_t **head);



/* list_len - Get the length of a linked list
 * This function calculates and returns the number of elements in the linked list.
 */
size_t list_len(const list_t *list);

/* list_to_strings - Convert a linked list to an array of strings
 * This function converts the elements of a linked list into an array of strings.
 */
char **list_to_strings(list_t *list);

/* print_list - Print the elements of a linked list
 */
size_t print_list(const list_t *list);

/* node_starts_with - Find the first node that starts with a given character
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
