/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 15:45:09 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:41:39 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	We consider only the case where the $ is the first element \
**	of the instruction.
*/

char	*manage_expansion_dollar(char **environ, char *str)
{
	return (get_env_variable_value(environ, str + 1));
}

/*
**	We consider here only the case where the ~ is the first element \
**	of the path. In such a case, we replace it by the value contained \
**	in the HOME environment variable.
*/

char	*manage_expansion_tilde(char **environ, char *str)
{
	char	*tilde;
	char	*new_path;

	tilde = get_env_variable_value(environ, "HOME");
	new_path = concat_strings_with_separator(tilde, str + 1, "/");
	free(tilde);
	return (new_path);
}

char	*manage_expansions(char **environ, char *str)
{
	char	*tmp;
	char	*tmp2;

	if (str && str[0] == '$' && str[1] == '$')
	{
		tmp = str;
		tmp2 = ft_itoa(getpid());
		str = concat_strings_basic(tmp2, str + 2);
		free(tmp);
		free(tmp2);
	}
	else if (str && str[0] == '$')
	{
		tmp = str;
		str = manage_expansion_dollar(environ, str);
		free(tmp);
	}
	else if (str && str[0] == '~')
	{
		tmp = str;
		str = manage_expansion_tilde(environ, str);
		free(tmp);
	}
	return (str);
}

/*
**	After applying the expansions, there may be some fields of \
**	char **ins that are now NULL, we want to move all these NULL fields \
**	to the end of the ins table.
**	Such a case could happen for instance when an non-existing \
**	environment variable is referenced.
**	N.B.: we don't need a char ***tab (triple pointer), as we never \
**	change the place of the char* inside the char**, we only change \
**	the value they contain.
*/

void	put_null_elements_to_the_tab_end(char **tab, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1)
		{
			if (tab[j] == NULL && tab[j + 1] != NULL)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	apply_expansions_to_instructions(char **ins, char **environ)
{
	int		n;
	int		i;

	n = 0;
	if (!ins)
		return ;
	while (ins[n] != NULL)
		n++;
	i = -1;
	while (++i < n)
		ins[i] = manage_expansions(environ, ins[i]);
	put_null_elements_to_the_tab_end(ins, n);
}
