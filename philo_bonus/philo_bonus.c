/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:19:08 by mtani             #+#    #+#             */
/*   Updated: 2024/02/10 12:19:08 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_print(t_philo *philo, char *str)
{
	sem_wait(philo->input->dead);
	if (philo->dead == 1 || philo->full == 1)
	{
		sem_post(philo->input->dead);
		return (1);
	}
	sem_post(philo->input->dead);
	sem_wait(philo->input->print);
	printf("%d %d %s\n", ft_get_time() - philo->input->start, philo->id, str);
	sem_post(philo->input->print);
	return (0);
}

void	*sim_ender(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->input->personal_sem[philo->id - 1]);
	sem_wait(philo->input->check);
	sem_wait(philo->input->dead);
	philo->dead = 1;
	sem_post(philo->input->dead);
	ft_usleep(100);
	return (NULL);
}

void	free_all(t_input *input)
{
	int	i;

	i = -1;
	ft_usleep(500);
	while (++i < input->philo_num)
		sem_close(input->personal_sem[i]);
	sem_close(input->forks);
	sem_close(input->print);
	sem_close(input->dead);
	sem_close(input->last_meal);
	sem_close(input->meals);
	sem_close(input->waiter);
	sem_close(input->check);
	free(input->philos);
	free(input->personal_sem);
}

void	wait_end(t_input *input)
{
	int		i;

	i = 0;
	while (i < input->philo_num)
		waitpid(input->philos[i++].pid, NULL, 0);
	ft_usleep(500);
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
	i = -1;
	unlink_all_sems(0, input);
	free(input->philos);
	free(input->personal_sem);
	exit (0);
}

int	main(int argc, char **argv)
{
	t_input	input;

	if (argc != 5 && argc != 6)
		return (ft_error("Error: wrong number of arguments\n"));
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (ft_error("Error: invalid number of philosophers\n"));
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (ft_error("Error: invalid time\n"));
	if (init_input(&input, argc, argv))
		return (ft_error("Error: invalid arguments\n"));
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(ft_atoi(argv[2]));
		printf("%d 1 has died\n", ft_atoi(argv[2]));
		return (0);
	}
	if (init_philos(&input))
	{
		free(input.philos);
		return (ft_error("Error: malloc failed\n"));
	}
	wait_end(&input);
	return (0);
}
