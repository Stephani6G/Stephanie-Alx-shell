#include "shell.h"


/**
 *  _prerror - a function that Print Custom error
 * @argv: name of the programme
 * @c:Error Count in program
 * @cmd:Commands in the shell
 * Return: Void success always
 */

void _prerror(char **argv, int c, char **cmd)
{
	char *er = _itoa(c);

	PRINTER(argv[0]);
	PRINTER(": ");
	PRINTER(er);
	PRINTER(": ");
	PRINTER(cmd[0]);
	PRINTER(": Illegal number: ");
	PRINTER(cmd[1]);
	PRINTER("\n");
	free(er);
}
