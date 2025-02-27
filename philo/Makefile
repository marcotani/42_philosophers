# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtani <mtani@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 13:28:57 by mtani             #+#    #+#              #
#    Updated: 2024/02/03 14:11:47 by mtani            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./philo.c ./philo_utils.c ./ft_dinnertime.c ./ft_init.c ./ft_actions.c
	
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc -g -Wall -Wextra -Werror -pthread $(OBJS) -o $(NAME)

%.o: %.c
	cc -Wall -Wextra -Werror -g -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
