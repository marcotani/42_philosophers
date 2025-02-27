/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_sems_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:47:14 by mtani             #+#    #+#             */
/*   Updated: 2024/03/19 10:52:58 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_all_sems(int flag, t_input *input)
{
	int		i;
	int		limit;
	char	*semname;
	char	*num;

	i = -1;
	if (flag == 1)
		limit = input->philo_num;
	else
		limit = 200;
	while (++i < limit)
	{
		num = ft_itoa(i + 1);
		semname = ft_strjoin("/personal_sem", num);
		sem_unlink(semname);
		free(semname);
		free(num);
	}
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/dead");
	sem_unlink("/last_meal");
	sem_unlink("/meals");
	sem_unlink("/waiter");
	sem_unlink("/check");
}

int	open_sems(t_input *input)
{
	input->forks = sem_open("/forks", O_CREAT, 0644, input->philo_num);
	input->print = sem_open("/print", O_CREAT, 0644, 1);
	input->dead = sem_open("/dead", O_CREAT, 0644, 1);
	input->last_meal = sem_open("/last_meal", O_CREAT, 0644, 1);
	input->meals = sem_open("/meals", O_CREAT, 0644, 1);
	input->waiter = sem_open("/waiter", O_CREAT, 0644, 1);
	input->check = sem_open("/check", O_CREAT, 0644, 0);
	if (input->forks == SEM_FAILED || input->print == SEM_FAILED
		|| input->dead == SEM_FAILED || input->check == SEM_FAILED
		|| input->meals == SEM_FAILED || input->last_meal == SEM_FAILED
		|| input->waiter == SEM_FAILED)
		return (1);
	return (0);
}

void	close_all_sems(t_input *input)
{
	int		i;

	i = 0;
	while (i < input->philo_num)
		sem_close(input->personal_sem[i++]);
	sem_close(input->print);
	sem_close(input->check);
	sem_close(input->dead);
	sem_close(input->last_meal);
	sem_close(input->meals);
	sem_close(input->waiter);
	sem_close(input->forks);
}

int	init_sems(t_input *input)
{
	int		i;
	char	*semname;
	char	*num;

	unlink_all_sems(0, input);
	i = 0;
	while (i < input->philo_num)
	{
		num = ft_itoa(i + 1);
		semname = ft_strjoin("/personal_sem", num);
		input->personal_sem[i] = sem_open(semname, O_CREAT, 0644, 0);
		free(semname);
		free(num);
		if (input->personal_sem[i] == SEM_FAILED)
			return (1);
		i++;
	}
	if (open_sems(input))
		return (1);
	return (0);
}
