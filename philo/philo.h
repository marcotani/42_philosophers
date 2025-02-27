/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:42:35 by mtani             #+#    #+#             */
/*   Updated: 2024/02/10 11:42:35 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_input
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	int				n_full;
	int				start;
	int				over;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	meals;
}	t_input;

typedef struct s_philo
{
	int				id;
	int				n_meals;
	int				last_meal;
	pthread_t		thread;
	pthread_mutex_t	eating;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_input			*input;
}	t_philo;

// Utils
int		ft_error(char *str);
int		ft_get_time(void);
int		ft_atoi(char *str);
int		ft_usleep(int time);
int		ft_print(t_philo *philo, char *str);

// Init
int		ft_init_philos(t_input *input);
int		ft_init_input(t_input *input, int argc, char **argv);

// Dinnertime
void	*ft_monitor(void *arg);
void	*dinnertime(void *arg);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);

#endif