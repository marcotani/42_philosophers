/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:42:19 by mtani             #+#    #+#             */
/*   Updated: 2024/02/10 11:42:19 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	c;
	int	sign;
	int	result;

	c = 0;
	sign = 1;
	result = 0;
	while ((str[c] >= '\t' && str[c] <= '\r') || str[c] == ' ')
	{
		c++;
	}
	while (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			sign *= -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		result = (str[c] - '0') + (result * 10);
		c++;
	}
	return (result * sign);
}

int	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	ft_usleep(int time)
{
	int	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
	{
		usleep(100);
	}
	return (0);
}
