#include "shell.h"
/**
 * exit_bul - Exit the  Statue shell
 * @cmd: Parsed Command into shell
 * @input: User Input for  UID
 * @argv: argument veector
 * @c: Count
 * Return: Void (Exit Statue) success
 */

void  exit_bul(char **cmd, char *input, char **argv, int c)
{
	int statue, i = 0;

	if (cmd[1] == NULL)
	{
		free(input);
		free(cmd);
		exit(EXIT_SUCCESS);
	}

	while (cmd[1][i])
	{
		if (_isalpha(cmd[1][i++]) != 0)
		{
			_prerror(argv, c, cmd);
			break;
		}

		else
		{
			statue = _atoi(cmd[1]);
			free(input);
			free(cmd);
			exit(statue);
		}
	}
}


/**
 * change_dir - Change the working directory in the shell
 * @cmd: Parsed Command in the shell
 * @er: Statue Last command excecuted in the shell
 * Return: 0 on success 1 on failure
 */

int change_dir(char **cmd, __attribute__((unused))int er)
{
	int value = -1;
	char cwd[PATH_MAX];

	if (cmd[1] == NULL)
		value = chdir(getenv("HOME"));
	else if (_strcmp(cmd[1], "-") == 0)
	{
		value = chdir(getenv("OLDPWD"));
	}

	else
		value = chdir(cmd[1]);

	if (value == -1)
	{
		perror("hsh");
		return (-1);
	}

	else if (value != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}

	return (0);
}

/**
 * dis_env - Display the enviroment variable
 * @cmd:Parsed Command in the shell
 * @er:Statue of Last command excuted in the shell
 * Return:Always 0 success
 */

int dis_env(__attribute__((unused)) char **cmd, __attribute__((unused)) int er)
{
size_t i;
	int len;

	for (i = 0; environ[i] != NULL; i++)
	{
		len = _strlen(environ[i]);
		write(1, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}

	return (0);
}

/**
 * display_help - Displaying help for builtin
 * @cmd:Parsed Command in the shell
 * @er: Statue Of Last Command Excuted
 * Return: 0  on success -1 on failure
 */

int display_help(char **cmd, __attribute__((unused))int er)
{
	int fd, fw, rd = 1;
	char c;

	fd = open(cmd[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		return (0);
	}
	while (rd > 0)
	{
		rd = read(fd, &c, 1);
		fw = write(STDOUT_FILENO, &c, rd);
		if (fw < 0)
		{
			return (-1);
		}
	}
	_putchar('\n');
	return (0);
}

/**
 * echo_bul - Excute Echo Cases
 * @st:Statue Of Last Command excuted
 * in the shell
 * @cmd: Parsed Command uin the shell
 * Return: Always 0 Or Excute the echo
 */

int echo_bul(char **cmd, int st)
{
	char *path;
	unsigned int  pid = getppid();

	if (_strncmp(cmd[1], "$?", 2) == 0)
	{
		print_number_in(st);
		PRINTER("\n");
	}

	else if (_strncmp(cmd[1], "$$", 2) == 0)
	{
		print_number(pid);
		PRINTER("\n");

	}

	else if (_strncmp(cmd[1], "$PATH", 5) == 0)
	{
		path = _getenv("PATH");
		PRINTER(path);
		PRINTER("\n");
		free(path);

	}

	else
		return (print_echo(cmd));

	return (1);
}
