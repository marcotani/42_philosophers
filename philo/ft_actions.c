/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:54:16 by mtani             #+#    #+#             */
/*   Updated: 2024/02/10 11:54:17 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_think(t_philo *philo)
{
	ft_print(philo, "is thinking");
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->input->time_to_sleep);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->eating);
	philo->last_meal = ft_get_time();
	philo->n_meals++;
	pthread_mutex_unlock(&philo->eating);
	ft_print(philo, "is eating");
	ft_usleep(philo->input->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->input->n_meals != -1 && philo->n_meals >= philo->input->n_meals)
	{
		pthread_mutex_lock(&philo->input->meals);
		philo->input->n_full++;
		pthread_mutex_unlock(&philo->input->meals);
		return (1);
	}
	return (0);
}
