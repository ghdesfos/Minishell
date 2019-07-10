/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:55:59 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:07:57 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <limits.h>
# include <signal.h>

/*
** BELOW part corresponding to the get_next_line header
*/

# include <fcntl.h>

# define BUFF_SIZE 4

typedef struct		s_file
{
	char			*content;
	int				fd;
	struct s_file	*next;
}					t_file;

int					get_next_line(const int fd, char **line);

/*
** BELOW normal header
*/

void				the_free_function(char **tab, char *str);
void				built_in_exec(char **ins, char ***environ);
int					test_built_in(char **ins);
void				execute_instructions(char **ins, char ***environ);

void				sigint_handler(int signum);
void				handle_signals(void);

char				*move_to_next_word(char *str);
char				*move_to_char_after_end_of_word(char *str);
int					word_length(char *str);
int					count_words(char *str);
char				**parse_words(char *str);

char				*get_binary_paths(char *env_path, int start);
char				*check_all_binary_folders(char *binary, char *env_path);
void				binary_exec(char **ins, char **environ);

void				built_in_env(char **ins, char **environ);
char				**add_new_variable_to_environ(char **environ, \
					char *variable, char *value);
void				built_in_setenv_sub(char **ins, char ***environ);
void				built_in_setenv(char **ins, char ***environ);
void				built_in_unsetenv(char **ins, char **environ);

void				update_oldpwd_environ_variable(char ***environ);
void				change_current_directory(char ***environ, char *new_path);
void				built_in_cd_sub(char **ins, char ***environ);
void				built_in_cd(char **ins, char ***environ);

void				built_in_echo(char **ins, char **environ);
void				built_in_exit(char **ins, char **environ);

char				*manage_expansion_dollar(char **environ, char *str);
char				*manage_expansion_tilde(char **environ, char *str);
char				*manage_expansions(char **environ, char *str);
void				put_null_elements_to_the_tab_end(char **tab, int n);
void				apply_expansions_to_instructions(char **ins, \
					char **environ);

void				ft_putchar(char c);
void				ft_putstr(char *str);
int					ft_strlen(char *str);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strdup_max(char *str, int max);

char				*concat_strings_basic(char *s1, char *s2);
char				*concat_strings_with_separator(char *s1, char *s2, \
					char *separator);
int					search_env_variables_for_specific_one(char **environ, \
					char *variable);
char				*ft_strdup(char *str);
char				*get_env_variable_value(char **environ, char *variable);

char				**ft_tab2dup(char **tab);
void				print_tab2(char **tab, int max);
char				*ft_itoa(int n);

#endif
