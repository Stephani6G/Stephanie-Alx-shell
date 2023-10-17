i#include "shell.h"

/**
 * read_input - Prompt the user for input and read it into the buffer
 * @input: The buffer to store the user's input
 *
 * Return: None success
 */

void read_input(char *input)
{
	write(STDOUT_FILENO, "SimpleShell > ",  strlen("SimpleShell > "));
	fgets(input, MAX_INPUT_SIZE, stdin);

	input[strcspn(input, "\n")] = '\0';
}

/**
 * parse_input - Parse a string into individual arguments
 * @input: input string to parse
 * @args:  array to store the parsed arguments
 *
 * Return: The number of argument, or -1 if there are too many arguments
 */

int parse_input(char *input, char *args[])
{
	int arg_count = 0;
	char *token = strtok(input, " ");

	while (token != NULL)
	{
		args[arg_count] = token;
		arg_count++;

		if (arg_count >= MAX_ARGS)
		{
			write(STDOUT_FILENO, "Too many arguments.\n", 20);
			return (-1);
		}

		token = strtok(NULL, " ");
	}

	args[arg_count] = NULL;
	return (arg_count);
}

int main(void)
{
	char input[MAX_INPUT_SIZE];
	char* args[MAX_ARGS];

	while (1)
	{
		read_input(input);

		if (strcmp(input, "exit") == 0)
		{
			 write(STDOUT_FILENO, "Exiting the custom shell.\n",
					 strlen("Exiting the custom shell.\n"));
			break;
		}

		int arg_count = parse_input(input, args);

		if (arg_count == -1)
		{
			continue;
		}

		pid_t pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
			exit(1);
		}
		else if (pid == 0)
		{
			/*Thhe Child process */
			if (execvp(args[0], args) == -1)
			{
				perror("Command execution failed");
				exit(1);
			}
		}
		else
		{
			/* Parent process */
			wait(NULL);
		}
	}

	return 0;
}
