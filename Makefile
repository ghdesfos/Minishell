# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/22 18:02:22 by ghdesfos          #+#    #+#              #
#    Updated: 2019/06/27 19:12:40 by ghdesfos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = binary_exec.c\
		get_next_line.c\
		main.c\
		parse_words.c\
		useful_functions.c\
		useful_functions_2.c\
		useful_functions_3.c\
		built_in_env.c\
		built_in_path.c\
		built_in_others.c\
		manage_expansions.c\
		handle_signals.c
OBJS = $(SRCS:.o=.c)
HDRS = minishell.h

FLAGS =-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) -o $@ $^ -I.

%.o: %.c $(HDRS)
	gcc $(FLAGS) -o $@ -c $< -I.

g: $(OBJS)
	gcc $(FLAGS) -o $(NAME) $^ -I. -g

gg: $(OBJS)
	gcc $(FLAGS) -o $(NAME) $^ -I. -g -fsanitize=address

val:
	valgrind --leak-check=full -v ./a.out

clean:
	/bin/rm -f *.o
	/bin/rm -f *.gch
	/bin/rm -rf *.dSYM

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
