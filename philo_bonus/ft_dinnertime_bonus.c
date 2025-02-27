/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dinnertime_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:23:46 by mtani             #+#    #+#             */
/*   Updated: 2024/03/15 14:07:10 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_think(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->input->time_to_sleep);
}

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->input->waiter);
	sem_wait(philo->input->forks);
	ft_print(philo, "has taken a fork");
	sem_wait(philo->input->forks);
	ft_print(philo, "has taken a fork");
	sem_post(philo->input->waiter);
	sem_wait(philo->input->last_meal);
	philo->last_meal = ft_get_time();
	sem_post(philo->input->last_meal);
	ft_print(philo, "is eating");
	ft_usleep(philo->input->time_to_eat);
	sem_wait(philo->input->meals);
	philo->n_meals++;
	sem_post(philo->input->meals);
	if (philo->input->n_meals != -1 && philo->n_meals == philo->input->n_meals)
		philo->full = 1;
	sem_post(philo->input->forks);
	sem_post(philo->input->forks);
}

int	loop_check(t_philo *philo)
{
	sem_wait(philo->input->dead);
	if (philo->dead == 1 || philo->full == 1)
	{
		sem_post(philo->input->dead);
		return (1);
	}
	sem_post(philo->input->dead);
	return (0);
}

void	dinnertime(void *arg)
{
	t_philo		*philo;
	pthread_t	ender;
	int			i;

	i = -1;
	philo = (t_philo *)arg;
	pthread_create(&philo->thread, NULL, ft_checker, (void *) philo);
	pthread_detach(philo->thread);
	pthread_create(&ender, NULL, sim_ender, (void *) philo);
	pthread_detach(ender);
	if (philo->id % 2 == 0)
		ft_usleep(philo->input->time_to_eat);
	while (loop_check(philo) == 0)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	sem_post(philo->input->personal_sem[philo->id - 1]);
	sem_post(philo->input->check);
	ft_usleep(philo->input->time_to_die);
	free_all(philo->input);
	exit (0);
}
