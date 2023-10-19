#include "shell.h"

/**
 * history_dis - displays the history of the  user input
 * @c:Parsed Command into the  shell
 * @s:Statue Of Last Excution in the shell
 *
 * Return: 0 on Success -1  on Failure
 */

int history_dis(__attribute__((unused))char **c, __attribute__((unused))int s)
{
	char *filename = ".simple_shell_history";
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;
	char *er;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return (-1);
	}

	while ((getline(&line, &len, fp)) != -1)
	{
		counter++;
		er = _itoa(counter);
		PRINTER(er);
		free(er);
		PRINTER(" ");
		PRINTER(line);

	}

	if (line)
		free(line);
	fclose(fp);
	return (0);
}

/**
 * print_echo - Excute  the normal echo command
 * @cmd: Parsed Command into the shelll
 * Return: 0 on Success -1 on faiuree
 */

int print_echo(char **cmd)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)

	{
	if (execve("/bin/echo", cmd, environ) == -1)
	{
		return (-1);
	}
		exit(EXIT_FAILURE);
	}

	else if (pid < 0)
	{
		return (-1);
	}

	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
