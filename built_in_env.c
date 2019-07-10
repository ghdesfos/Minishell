/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 21:37:17 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:40:47 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	prints all environement variables contained in char **environ.
*/

void	built_in_env(char **ins, char **environ)
{
	int i;

	i = 0;
	if (!ins[1])
		while (environ[i])
		{
			ft_putstr(environ[i]);
			ft_putchar('\n');
			i++;
		}
	else
	{
		ft_putstr("env: ");
		ft_putstr(ins[1]);
		ft_putstr(": No such file or directory");
		ft_putchar('\n');
	}
}

/*
**	This function adds a new variabe at the end of the char **environ. \
**	To be more precise, we allocate a new char** and we copy all elements \
**	of environ into new_environ, adding the new element at the end of \
**	new_environ.
*/

char	**add_new_variable_to_environ(char **environ, char *variable, \
										char *value)
{
	char	**new_environ;
	int		n;
	int		i;

	n = 0;
	while (environ[n])
		n++;
	new_environ = NULL;
	if (!(new_environ = (char**)malloc(sizeof(char*) * (n + 2))))
		return (NULL);
	i = -1;
	while (++i < n)
		new_environ[i] = environ[i];
	new_environ[n] = concat_strings_with_separator(variable, value, "=");
	new_environ[n + 1] = NULL;
	free(environ);
	return (new_environ);
}

/*
**	The 2 functions below change/add a new variable to \
**	the environ variable.
*/

void	built_in_setenv_sub(char **ins, char ***environ)
{
	int		env_var;

	if (ins[1] && ins[2] && !ins[3])
	{
		if ((env_var = search_env_variables_for_specific_one(*environ, \
																ins[1])) != -1)
		{
			free((*environ)[env_var]);
			(*environ)[env_var] = concat_strings_with_separator(ins[1], \
																ins[2], "=");
		}
		else
			*environ = add_new_variable_to_environ(*environ, ins[1], ins[2]);
	}
	else if (ins[1] && ins[2] && ins[3])
		ft_putstr("setenv: Too many arguments.\n");
}

/*
**	We check:
**	- first if there are no instruction
**	- then if we have just one, in which case, it will \
**	be the key and the value will be "".
**	- then if there are 2 instructions (see function above) \
**	we have first the key and then the value.
** 	- then if there are 3 instructions or more (see function above) \
**	we print an error message.
*/

void	built_in_setenv(char **ins, char ***environ)
{
	int		env_var;

	if (!ins[1])
		built_in_env(ins, *environ);
	else if (ins[1] && ins[1][0] == '=')
		ft_putstr("minishell: bad assignment\n");
	else if (ins[1] && !ins[2])
	{
		if ((env_var = search_env_variables_for_specific_one(*environ, \
																ins[1])) != -1)
		{
			free((*environ)[env_var]);
			(*environ)[env_var] = concat_strings_with_separator(ins[1], \
																NULL, "=");
		}
		else
			*environ = add_new_variable_to_environ(*environ, ins[1], NULL);
	}
	else if (ins[1] && ins[2])
		built_in_setenv_sub(ins, environ);
}

/*
**	For each ins parameters passed, we will check if it exists among \
**	the environment variables. And if so, we will free this variable \
**	and push its pointer to the end of the char **environ.
**	N.B.: we need to use the put_null_elements_to_the_tab_end \
**	after each removal of an environment variable as the \
**	search_env_variables_for_specific_one just looks up up to the first NULL \
**	elements in the researched tab.
**	We prevent the unsetenv on PWD and HOME as this can pause problem at some \
**	other points notably by having an exterior environment different from \
**	the one internal to this program (contained in the char **environ).
*/

void	built_in_unsetenv(char **ins, char **environ)
{
	int		env_len;
	int		env_var;
	int		n;

	if (!ins[1])
		ft_putstr("unsetenv: Too few arguments.\n");
	else
	{
		env_len = 0;
		while (environ[env_len])
			env_len++;
		n = 0;
		while (ins[++n])
		{
			if (ft_strcmp(ins[n], "PWD") != 0 && ft_strcmp(ins[n], "HOME") != 0
				&& ft_strcmp(ins[n], "OLDPWD") != 0 \
				&& (env_var = search_env_variables_for_specific_one(environ, \
																ins[n])) != -1)
			{
				free(environ[env_var]);
				environ[env_var] = NULL;
				put_null_elements_to_the_tab_end(environ, env_len);
			}
		}
	}
}
