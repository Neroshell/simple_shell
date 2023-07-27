#include "shell.h"

/**
 * historian - displays history
 * @info: Structure that contains potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int historian(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * remove_alias - removes ll alias from list
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *str)
{
	char *equal_sign_pos, original_char;
	int result;

	equal_sign_pos = _strchr(str, '=');
	if (!equal_sign_pos)
		return (1);
	original_char = *equal_sign_pos;
	*equal_sign_pos = 0;
	result = delete_node_at_index(&(info->alias),
				      get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*equal_sign_pos = original_char;
	return (result);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *equal_sign_pos;

	equal_sign_pos = _strchr(str, '=');
	if (!equal_sign_pos)
		return (1);
	if (!*++equal_sign_pos)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * display_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int display_alias(list_t *node)
{
	char *equal_sign_pos = NULL, *alias = NULL;

	if (node)
	{
		equal_sign_pos = _strchr(node->str, '=');
		for (alias = node->str; alias <= equal_sign_pos; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(equal_sign_pos + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * personal_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int personal_alias(info_t *info)
{
	int i = 0;
	char *equal_sign_pos = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_sign_pos = _strchr(info->argv[i], '=');
		if (equal_sign_pos)
			set_alias(info, info->argv[i]);
		else
			display_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
