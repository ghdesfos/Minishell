/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 22:54:54 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:41:16 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	char *tmp;

	tmp = ft_itoa(getpid());
	ft_putstr("The process ID is: ");
	ft_putstr(tmp);
	ft_putstr("\n");
	free(tmp);
	(void)signum;
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
}
