/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_others.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 22:36:46 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:40:54 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_echo(char **ins, char **environ)
{
	int i;

	i = 1;
	while (ins[i])
	{
		ft_putstr(ins[i]);
		if (ins[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	(void)environ;
}

void	built_in_exit(char **ins, char **environ)
{
	the_free_function(ins, NULL);
	the_free_function(environ, NULL);
	exit(0);
}
