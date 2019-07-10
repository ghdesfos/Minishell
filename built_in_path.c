/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 01:07:42 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:41:04 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd_environ_variable(char ***environ)
{
	char	*oldpwd;
	char	*ins_oldpwd[4];

	oldpwd = get_env_variable_value(*environ, "PWD");
	ins_oldpwd[0] = "setenv";
	ins_oldpwd[1] = "OLDPWD";
	ins_oldpwd[2] = oldpwd;
	ins_oldpwd[3] = NULL;
	built_in_setenv(ins_oldpwd, environ);
	free(oldpwd);
}

/*
**	In the function below, we need to change both the real environment \
**	of the process (done with chdir) which is used by the shell built-ins \
**	and the copied environment (contained in char **environ), which is \
**	used by the "binary executables" which are recoded built-ins inside \
**	this program.
*/

void	change_current_directory(char ***environ, char *new_path)
{
	char	buf[PATH_MAX + 2];
	char	*ins_pwd[4];

	if (chdir(new_path) == -1)
	{
		ft_putstr("Error with the change of cd command, \
no change of directory\n");
		free(new_path);
		return ;
	}
	free(new_path);
	update_oldpwd_environ_variable(environ);
	getcwd(buf, PATH_MAX + 1);
	ins_pwd[0] = "setenv";
	ins_pwd[1] = "PWD";
	ins_pwd[2] = buf;
	ins_pwd[3] = NULL;
	built_in_setenv(ins_pwd, environ);
}

/*
**	N.B.: In the case where the PWD variables from environ has been \
**	removed, then by default, the new value of PWD will be '/',
**	i.e. the base directory.
*/

void	built_in_cd_sub(char **ins, char ***environ)
{
	char	*new_path;
	char	*tmp;

	if (ins[1] && ins[1][0] == '-' && ins[1][1] == 0)
	{
		new_path = get_env_variable_value(*environ, "OLDPWD");
		change_current_directory(environ, new_path);
		return ;
	}
	else if (ins[1] && ins[1][0] == '/')
		change_current_directory(environ, ft_strdup(ins[1]));
	else if (ins[1] && ins[1][0] != '/')
	{
		tmp = get_env_variable_value(*environ, "PWD");
		new_path = concat_strings_with_separator(tmp, ins[1], "/");
		free(tmp);
		change_current_directory(environ, new_path);
	}
}

void	built_in_cd(char **ins, char ***environ)
{
	char *new_path;

	if (ins[1] && ins[2])
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putstr(ins[1]);
		ft_putstr("\n");
		return ;
	}
	else if (!ins[1])
	{
		new_path = get_env_variable_value(*environ, "HOME");
		change_current_directory(environ, new_path);
		return ;
	}
	built_in_cd_sub(ins, environ);
}
