/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:27:06 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/27 18:41:49 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*move_to_next_word(char *str)
{
	while (*str == 9 || *str == 11 || *str == 32)
		str++;
	return (str);
}

char	*move_to_char_after_end_of_word(char *str)
{
	while (*str && *str != 9 && *str != 11 && *str != 32)
		str++;
	return (str);
}

int		word_length(char *str)
{
	int n;

	n = 0;
	while (*str && *str != 9 && *str != 11 && *str != 32)
	{
		n++;
		str++;
	}
	return (n);
}

int		count_words(char *str)
{
	int n;

	n = 0;
	str = move_to_next_word(str);
	while (*str)
	{
		if (*str && *str != 9 && *str != 11 && *str != 32)
			n++;
		str = move_to_char_after_end_of_word(str);
		str = move_to_next_word(str);
	}
	return (n);
}

char	**parse_words(char *str)
{
	char	**words;
	int		words_nb;
	int		i;
	int		j;
	int		word_len;

	words_nb = count_words(str);
	if (!(words = (char**)malloc(sizeof(char*) * (words_nb + 1))))
		return (NULL);
	words[words_nb] = NULL;
	str = move_to_next_word(str);
	i = -1;
	while (++i < words_nb)
	{
		word_len = word_length(str);
		if (!(words[i] = (char*)malloc(sizeof(char) * (word_len + 1))))
			return (NULL);
		j = -1;
		while (++j < word_len)
			words[i][j] = str[j];
		words[i][word_len] = 0;
		str = move_to_char_after_end_of_word(str);
		str = move_to_next_word(str);
	}
	return (words);
}
