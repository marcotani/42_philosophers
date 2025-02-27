/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:28:47 by mtani             #+#    #+#             */
/*   Updated: 2024/04/15 08:53:33 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_threads(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->philo_num)
	{
		input->philos[i].pid = fork();
		if (input->philos[i].pid == 0)
		{
			dinnertime(&input->philos[i]);
			exit (0);
		}
		i++;
	}
}

int	init_philos(t_input *input)
{
	int	i;

	i = 0;
	input->start = ft_get_time();
	while (i < input->philo_num)
	{
		input->philos[i].id = i + 1;
		input->philos[i].last_meal = input->start;
		input->philos[i].n_meals = 0;
		input->philos[i].full = 0;
		input->philos[i].dead = 0;
		input->philos[i].start = input->start;
		input->philos[i].input = input;
		i++;
	}
	init_threads(input);
	return (0);
}

void	init_params(t_input *input, char **argv)
{
	input->personal_sem = NULL;
	input->philo_num = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	input->n_meals = -1;
}

int	init_input(t_input *input, int argc, char **argv)
{
	int	i;

	i = 0;
	init_params(input, argv);
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (1);
	if (argc == 6)
		input->n_meals = ft_atoi(argv[5]);
	input->philos = malloc(sizeof(t_philo) * input->philo_num);
	if (!input->philos)
		return (1);
	input->personal_sem = (sem_t **)ft_calloc(sizeof(sem_t *),
			input->philo_num);
	if (!input->personal_sem)
	{
		free(input->philos);
		return (1);
	}
	if (init_sems(input))
	{
		free(input->philos);
		return (1);
	}
	return (0);
}
