#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Max input size for user commands */
#define MAX_INPUT_SIZE 1024

/* Max number of arguments a command can take */
#define MAX_ARGS 64

/* The size of the read buffer for input */
#define READ_BUF_SIZE 1024

/* size of the write buffer for output */
#define WRITE_BUF_SIZE 1024

/* special value to indicate flushing the buffer */
#define BUF_FLUSH -1

/*prototype for "  Betty would be proud" */
int _putchar(char c);

/*task 1 protypes */
typedef struct shell_data {
    int read_fd;
} shell_data_t;

int checkInteractive(shell_data_t *shell_data);
int isSeparator(char character, char *separators);
int isAlpha(int c);
int stringToInt(char *input);

#endif
