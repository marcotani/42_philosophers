/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:54:04 by mtani             #+#    #+#             */
/*   Updated: 2024/02/10 11:55:33 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philos(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->n_philo)
	{
		input->philos[i].id = i + 1;
		input->philos[i].input = input;
		input->philos[i].last_meal = input->start;
		input->philos[i].n_meals = 0;
		if (pthread_mutex_init(&input->forks[i], NULL))
			return (1);
		input->philos[i].left_fork = &input->forks[i];
		if (i == input->n_philo - 1)
			input->philos[i].right_fork = &input->forks[0];
		else
			input->philos[i].right_fork = &input->forks[i + 1];
		i++;
	}
	return (0);
}

int	ft_init_input(t_input *input, int argc, char **argv)
{
	input->n_philo = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	input->n_meals = -1;
	if (argc == 6)
		input->n_meals = ft_atoi(argv[5]);
	input->n_full = 0;
	input->start = ft_get_time();
	input->over = 0;
	input->philos = NULL;
	input->philos = malloc(sizeof(t_philo) * input->n_philo);
	if (!input->philos)
		return (1);
	input->forks = NULL;
	input->forks = malloc(sizeof(pthread_mutex_t) * input->n_philo);
	if (!input->forks)
	{
		free(input->philos);
		return (1);
	}
	pthread_mutex_init(&input->print, NULL);
	pthread_mutex_init(&input->death, NULL);
	pthread_mutex_init(&input->meals, NULL);
	return (0);
}
