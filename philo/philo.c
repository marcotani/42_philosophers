/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:42:29 by mtani             #+#    #+#             */
/*   Updated: 2024/02/10 11:42:29 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print(t_philo *philo, char *str)
{
	int	time;

	pthread_mutex_lock(&philo->input->death);
	if (philo->input->over)
	{
		pthread_mutex_unlock(&philo->input->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->input->death);
	pthread_mutex_lock(&philo->input->print);
	time = ft_get_time() - philo->input->start;
	printf("%d %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->input->print);
	return (0);
}

void	free_all(t_input *input)
{
	int	i;

	i = 0;
	ft_usleep(500);
	while (i < input->n_philo)
	{
		pthread_mutex_destroy(&input->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&input->print);
	pthread_mutex_unlock(&input->death);
	pthread_mutex_destroy(&input->death);
	pthread_mutex_destroy(&input->meals);
	free(input->forks);
	free(input->philos);
}

int	ft_start_sim(t_input *input)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < input->n_philo)
	{
		if (pthread_create(&input->philos[i].thread, NULL,
				&dinnertime, &input->philos[i]))
			return (1);
		if (pthread_create(&monitor, NULL, &ft_monitor, &input->philos[i]))
			return (1);
		pthread_detach(monitor);
		i++;
	}
	i = 0;
	while (i < input->n_philo)
	{
		if (pthread_join(input->philos[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_input	input;

	if (argc != 5 && argc != 6)
		return (ft_error("Error: wrong number of arguments\n"));
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (ft_error("Error: invalid number of philos\n"));
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (ft_error("Error: invalid time\n"));
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (ft_error("Error: invalid number of meals\n"));
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(ft_atoi(argv[2]));
		printf("%d 1 has died\n", ft_atoi(argv[2]));
		return (0);
	}
	if (ft_init_input(&input, argc, argv))
		return (ft_error("Error: invalid arguments\n"));
	if (ft_init_philos(&input))
		return (ft_error("Error: failed to initialize philos\n"));
	if (ft_start_sim(&input))
		return (ft_error("Error: failed to start threads\n"));
	free_all(&input);
}
