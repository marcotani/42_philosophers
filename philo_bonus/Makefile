# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtani <mtani@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 11:30:11 by mtani             #+#    #+#              #
#    Updated: 2024/03/19 10:52:13 by mtani            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = ./philo_bonus.c ./philo_utils_bonus.c ./ft_init_bonus.c ./ft_dinnertime_bonus.c ./ft_checker_bonus.c \
	./personal_sem_utils_bonus.c ./ft_itoa_bonus.c ./ft_init_sems_bonus.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@gcc -g -Wall -Wextra -Werror -o $(NAME) $(OBJS) -lpthread

%.o: %.c
	cc -Wall -Wextra -Werror -g -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
