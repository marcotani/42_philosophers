/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:01:26 by mtani             #+#    #+#             */
/*   Updated: 2024/03/06 11:30:58 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_threads(t_philo *philo, pthread_mutex_t *forks, t_main *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			ft_error(NULL, 7);
		i++;
	}
	i = 0;
	while (i < info->philo_num)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	unlock_all(forks, info);
	while (i < info->philo_num)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->death);
	pthread_mutex_destroy(&info->meal);
}

void	init_forks(pthread_mutex_t *forks, t_philo *philo, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		philo[i].left_fork = &forks[i];
		if (i == philo_num - 1)
			philo[i].right_fork = &forks[0];
		else
			philo[i].right_fork = &forks[i + 1];
		i++;
	}
}

void	init_info(t_main *info, int argc, char **argv)
{
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->start_time = get_time();
	info->n_meals = -1;
	if (argc == 6)
		info->n_meals = ft_atoi(argv[5]);
	info->death_flag = 0;
	info->meal_limit = 0;
	if (argc == 6)
		info->meal_limit = 1;
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->death, NULL);
	pthread_mutex_init(&info->meal, NULL);
}

void	init_philo(t_philo *philo, t_main *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		philo[i].info = info;
		philo[i].id = i + 1;
		philo[i].last_meal = info->start_time;
		philo[i].is_eating = 0;
		philo[i].is_sleeping = 0;
		philo[i].is_thinking = 0;
		philo[i].n_meals = info->n_meals;
		philo[i].print = &info->print;
		philo[i].death = &info->death;
		philo[i].meal = &info->meal;
		if (pthread_mutex_init(&philo[i].eating, NULL) != 0)
			ft_error(NULL, 8);
		i++;
	}
}
