/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dinnertime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:54:10 by mtani             #+#    #+#             */
/*   Updated: 2024/03/06 15:46:02 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->eating);
	if (ft_get_time() - philo->last_meal > philo->input->time_to_die)
	{
		pthread_mutex_unlock(&philo->eating);
		return (1);
	}
	pthread_mutex_unlock(&philo->eating);
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->input->death);
		if (philo->input->over || (philo->input->n_meals != -1
				&& philo->input->n_full == philo->input->n_philo))
			return (pthread_mutex_unlock(&philo->input->death), NULL);
		if (check_death(philo) == 1)
		{
			pthread_mutex_lock(&philo->input->print);
			printf("%d %d died\n", ft_get_time() - philo->input->start,
				philo->id);
			philo->input->over = 1;
			pthread_mutex_unlock(&philo->input->print);
			pthread_mutex_unlock(&philo->input->death);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->input->death);
	}
}

int	not_over(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->input->death);
	pthread_mutex_lock(&philo->input->meals);
	if (philo->input->over || (philo->input->n_meals != -1
			&& philo->input->n_full == philo->input->n_philo))
		ret = 0;
	else
		ret = 1;
	pthread_mutex_unlock(&philo->input->meals);
	pthread_mutex_unlock(&philo->input->death);
	return (ret);
}

void	*dinnertime(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (pthread_mutex_init(&philo->eating, NULL))
		return (NULL);
	if (philo->id % 2)
		ft_usleep(100);
	while (not_over(philo))
	{
		if (ft_eat(philo))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
		if (ft_think(philo))
			return (NULL);
	}
	return (NULL);
}
