/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:44:33 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:42:01 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	if (str == NULL)
		ft_putstr("(null)\n");
	else
	{
		while (*str)
		{
			ft_putchar(*str);
			str++;
		}
	}
}

int		ft_strlen(char *str)
{
	int len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strdup_max(char *str, int max)
{
	char	*new;
	int		str_len;
	int		i;

	if (!str)
		return (NULL);
	str_len = 0;
	while (str[str_len])
		str_len++;
	if (max > str_len)
		max = str_len;
	if (!(new = (char*)malloc(sizeof(char) * (max + 1))))
		return (NULL);
	i = 0;
	while (i < max)
	{
		new[i] = str[i];
		i++;
	}
	new[max] = 0;
	return (new);
}
