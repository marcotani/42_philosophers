/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:19:16 by mtani             #+#    #+#             */
/*   Updated: 2024/02/10 12:19:16 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				n_meals;
	int				full;
	int				dead;
	int				start;
	pthread_t		thread;
	pid_t			pid;
	struct s_input	*input;
}	t_philo;

typedef struct s_input
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	int				n_full;
	int				start;
	t_philo			*philos;
	sem_t			**personal_sem;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*dead;
	sem_t			*last_meal;
	sem_t			*meals;
	sem_t			*waiter;
	sem_t			*check;
	pthread_t		*ender;
}	t_input;

// Utils
int		ft_error(char *str);
int		ft_get_time(void);
int		ft_atoi(char *str);
int		ft_usleep(int time);
int		ft_print(t_philo *philo, char *str);
int		ft_strlen(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_itoa(int n);
char	*ft_strjoin(char *s1, char *s2);

// Init
int		init_input(t_input *input, int argc, char **argv);
int		init_sems(t_input *input);
int		init_philos(t_input *input);
void	init_threads(t_input *input);
void	*sim_ender(void *arg);
int		init_sems(t_input *input);
void	unlink_all_sems(int flag, t_input *input);
void	close_all_sems(t_input *input);

// Dinnertime
void	dinnertime(void *arg);
void	*ft_checker(void *arg);
void	free_all(t_input *input);

#endif