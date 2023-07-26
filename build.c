#include "shell.h"

/**
 * custom_exit - This function exits the shell.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 *
 * Return: Exits with a given exit status (0) if info.argv[0] != "exit".
 */
int custom_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* Checking if there is an exit argument */
	{
		exitcheck = custom_atoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = custom_atoi(info->argv[1]);
		return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * custom_cd - This function changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 *
 * Return: Always 0.
 */
int custom_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = custom_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = custom_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (custom_strcmp(info->argv[1], "-") == 0)
	{
		if (!custom_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(custom_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
				chdir((dir = custom_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1)
	{
		print_error(info, "Unable to change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		custom_setenv(info, "OLDPWD", custom_getenv(info, "PWD="));
		custom_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 * custom_help - This function displays help information.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 *
 * Return: Always 0.
 */
int custom_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	/* This is a custom multiline comment */
	return (0);
}
