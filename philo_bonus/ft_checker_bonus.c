/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:10:39 by mtani             #+#    #+#             */
/*   Updated: 2024/03/15 14:07:35 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_meals(t_philo *philo)
{
	int	i;

	i = 0;
	sem_wait(philo->input->meals);
	if (philo->input->n_meals != -1 && philo->n_meals == philo->input->n_meals)
		i = 1;
	sem_post(philo->input->meals);
	return (i);
}

void	manage_death(t_philo *philo)
{
	int	i;

	i = -1;
	sem_post(philo->input->last_meal);
	sem_wait(philo->input->print);
	if (philo->dead == 0)
		printf("%d %d died\n", ft_get_time()
			- philo->input->start, philo->id);
	sem_post(philo->input->print);
	philo->dead = 1;
	while (++i < philo->input->philo_num)
		sem_post(philo->input->personal_sem[i]);
	i = -1;
	while (++i < philo->input->philo_num * 2)
		sem_post(philo->input->check);
	sem_post(philo->input->dead);
	ft_usleep(5);
}

void	close_checker(t_philo *philo)
{
	sem_post(philo->input->last_meal);
	sem_post(philo->input->dead);
	ft_usleep(5);
}

void	*ft_checker(void *arg)
{
	t_philo	*philo;

	philo = arg;
	ft_usleep(philo->input->time_to_die);
	while (1)
	{
		sem_wait(philo->input->dead);
		sem_wait(philo->input->last_meal);
		if (ft_get_time() - philo->last_meal > philo->input->time_to_die
			&& philo->dead == 0)
		{
			manage_death(philo);
			break ;
		}
		else if (check_meals(philo) == 1 || philo->dead == 1)
		{
			close_checker(philo);
			break ;
		}
		close_checker(philo);
	}
	return (NULL);
}
