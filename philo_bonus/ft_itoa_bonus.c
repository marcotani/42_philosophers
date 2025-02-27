/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:36:30 by mtani             #+#    #+#             */
/*   Updated: 2024/03/19 10:36:49 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_count_digits(int n)
{
	int			i;
	long long	num;

	num = (long long)n;
	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	long long		num;
	int				n_len;
	int				i;
	int				j;

	i = 0;
	n_len = ft_count_digits(n);
	j = n_len - 1;
	num = (long long)n;
	str = (char *)malloc(sizeof(char) * (n_len + 1));
	if (str == NULL)
		return (NULL);
	if (num < 0)
	{
		str[i++] = '-';
		num *= -1;
	}
	while (i++ < n_len)
	{
		str[j--] = (char)((num % 10) + 48);
		num /= 10;
	}
	str[i - 1] = '\0';
	return (str);
}
