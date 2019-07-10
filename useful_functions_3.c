/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:03:35 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:42:13 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tab2dup(char **tab)
{
	char	**new;
	int		n;
	int		i;

	n = 0;
	while (tab[n])
		n++;
	new = NULL;
	if (!(new = (char**)malloc(sizeof(char*) * (n + 1))))
		return (NULL);
	i = -1;
	while (++i < n)
		new[i] = ft_strdup(tab[i]);
	new[n] = NULL;
	return (new);
}

void	print_tab2(char **tab, int max)
{
	int n;

	n = 0;
	while (tab[n] || n < max)
	{
		ft_putstr(tab[n]);
		ft_putchar('\n');
		n++;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		tmp;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = (n < 0) ? 2 : 1;
	tmp = n;
	while (tmp /= 10)
		len++;
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n < 0 && (str[0] = '-') == '-')
		n = -n;
	str[len] = 0;
	while (n)
	{
		str[--len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
