/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:52:45 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:42:08 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_strings_basic(char *s1, char *s2)
{
	char	*new;
	int		l1;
	int		l2;
	int		i1;
	int		i2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
		return (ft_strdup((s1) ? s1 : s2));
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	new = NULL;
	if (!(new = (char*)malloc(sizeof(char) * (l1 + l2 + 1))))
		return (NULL);
	i1 = -1;
	while (++i1 < l1)
		new[i1] = s1[i1];
	i2 = -1;
	while (++i2 < l2)
		new[i1 + i2] = s2[i2];
	new[l1 + l2] = 0;
	return (new);
}

char	*concat_strings_with_separator(char *s1, char *s2, char *separator)
{
	char *new;
	char *tmp;

	tmp = concat_strings_basic(s1, separator);
	new = concat_strings_basic(tmp, s2);
	free(tmp);
	return (new);
}

int		search_env_variables_for_specific_one(char **environ, char *variable)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (environ[i])
	{
		len = ft_strlen(variable);
		j = 0;
		while (variable[j] == environ[i][j] && variable[j])
			j++;
		if (variable[j] == 0 && environ[i][j] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup(char *str)
{
	char	*new;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	new = NULL;
	len = ft_strlen(str);
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[len] = 0;
	return (new);
}

char	*get_env_variable_value(char **environ, char *variable)
{
	int		env_var;
	char	*new;

	env_var = search_env_variables_for_specific_one(environ, variable);
	if (env_var == -1)
		return (NULL);
	new = ft_strdup(environ[env_var] + ft_strlen(variable) + 1);
	return (new);
}
