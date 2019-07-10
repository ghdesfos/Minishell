/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:42:14 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:41:26 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	the_free_function(char **tab, char *str)
{
	int n;

	n = -1;
	if (tab)
		while (tab[++n])
			free(tab[n]);
	free(tab);
	free(str);
}

void	built_in_exec(char **ins, char ***environ)
{
	if (ft_strcmp(ins[0], "echo") == 0)
		built_in_echo(ins, *environ);
	else if (ft_strcmp(ins[0], "cd") == 0)
		built_in_cd(ins, environ);
	else if (ft_strcmp(ins[0], "setenv") == 0)
		built_in_setenv(ins, environ);
	else if (ft_strcmp(ins[0], "unsetenv") == 0)
		built_in_unsetenv(ins, *environ);
	else if (ft_strcmp(ins[0], "env") == 0)
		built_in_env(ins, *environ);
	else if (ft_strcmp(ins[0], "exit") == 0)
		built_in_exit(ins, *environ);
}

int		test_built_in(char **ins)
{
	if (ft_strcmp(ins[0], "echo") == 0)
		return (1);
	if (ft_strcmp(ins[0], "cd") == 0)
		return (1);
	if (ft_strcmp(ins[0], "setenv") == 0)
		return (1);
	if (ft_strcmp(ins[0], "unsetenv") == 0)
		return (1);
	if (ft_strcmp(ins[0], "env") == 0)
		return (1);
	if (ft_strcmp(ins[0], "exit") == 0)
		return (1);
	return (0);
}

/*
**	There are 2 types of commands in this minishell:
**	- built_in executables: commands that are (re)coded inside this program
**	- binary executables: commands that already exist inside the shell
**	In the case of the binary executables, a fork() and execve() are necessary \
**	as we launch a new process.
*/

void	execute_instructions(char **ins, char ***environ)
{
	pid_t father;

	if (ins && *ins)
	{
		if (test_built_in(ins))
			built_in_exec(ins, environ);
		else
		{
			father = fork();
			if (father == -1)
			{
				ft_putstr("Issue with the fork\n");
				exit(0);
			}
			else if (father == 0)
				binary_exec(ins, *environ);
			else
				wait(NULL);
		}
	}
}

/*
**	In case of a control + D signal, the get_next_line function returns NULL. \
**	In this case we exit the minishell.
*/

int		main(void)
{
	extern char	**environ;
	char		**new_environ;
	char		*str;
	char		**ins;

	handle_signals();
	new_environ = ft_tab2dup(environ);
	while (1)
	{
		ft_putstr("$> ");
		get_next_line(0, &str);
		if (!str)
		{
			the_free_function(new_environ, NULL);
			return (-1);
		}
		ins = parse_words(str);
		apply_expansions_to_instructions(ins, new_environ);
		execute_instructions(ins, &new_environ);
		the_free_function(ins, str);
	}
	return (0);
}
