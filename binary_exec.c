/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:41:15 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:40:31 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function will return one by one the different paths contained inside \
**	the PATH variable.
**	The i variable keeps track of the offset at which the next path is.
*/

char	*get_binary_paths(char *env_path, int start)
{
	static int	i;
	int			path_len;
	char		*path;

	if (start == 0)
		i = 0;
	path_len = 0;
	while (env_path[i + path_len] && env_path[i + path_len] != ':')
		path_len++;
	if (path_len == 0)
		return (NULL);
	path = ft_strdup_max(env_path + i, path_len);
	while (env_path[i] && env_path[i] != ':')
		i++;
	if (env_path[i])
		i++;
	return (path);
}

/*
**	This function checks all pathes contained in the PATH variable and \
**	checks if one contains the binary executable.
*/

char	*check_all_binary_folders(char *binary, char *env_path)
{
	char			*path;
	int				start;
	DIR				*dirp;
	struct dirent	*direntp;

	start = 0;
	while ((path = get_binary_paths(env_path, start)) != NULL)
	{
		if ((dirp = opendir(path)) == NULL)
			free(path);
		else
		{
			while ((direntp = readdir(dirp)) != NULL)
			{
				if (ft_strcmp(binary, direntp->d_name) == 0)
					return (path);
			}
			free(path);
			if (closedir(dirp) == -1)
				return (NULL);
		}
		start++;
	}
	return (NULL);
}

/*
**	We check thanks to access() if we have execution rights on the binary.
*/

void	binary_exec_sub(char **ins, char **environ, char *folder)
{
	char	*command;

	command = concat_strings_with_separator(folder, ins[0], "/");
	if (access(command, X_OK) == -1)
	{
		ft_putstr("minishell: permission denied\n");
		exit(1);
	}
	else
	{
		if (execve(command, ins, environ) == -1)
		{
			ft_putstr("The execution of the command ");
			ft_putstr(ins[0]);
			ft_putstr(" has not worked\n");
			free(folder);
			free(command);
			exit(0);
		}
	}
}

/*
**	We first check if the binary exists in the current folder with access().
**	We search for the PATH environment variable, \
**	then we check if the binary executables is available in one of the paths, \
**	then we concatenate the path containing the binary with the binary \
**	and we do and execve.
*/

void	binary_exec(char **ins, char **environ)
{
	int		path_i;
	char	*folder;

	if (access(ins[0], F_OK) == 0 && ins[0][0] == '/')
		folder = ft_strdup("");
	else if (access(ins[0], F_OK) == 0 && ins[0][0] != '/')
		folder = ft_strdup(".");
	else
	{
		if ((path_i = search_env_variables_for_specific_one(environ, \
						"PATH")) == -1)
		{
			ft_putstr("There is no PATH environment variable\n");
			exit(0);
		}
		if ((folder = check_all_binary_folders(ins[0], \
						environ[path_i] + 5)) == NULL)
		{
			ft_putstr("This command is available in none of the PATH \
folders\n");
			free(folder);
			exit(0);
		}
	}
	binary_exec_sub(ins, environ, folder);
}
