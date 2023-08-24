/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoibarki <yoibarki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:09:13 by yoibarki          #+#    #+#             */
/*   Updated: 2023/08/18 15:09:39 by yoibarki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_check_int(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check(t_shared_info info, t_philo *philo)
{
	int	i;
	int	j;

	j = 0;
	while (1)
	{
		i = -1;
		while (++i < info.nbr_philo)
		{
			if (philo[i].info.nbr_philo_must_eat == philo[i].nbr_of_meals
				&& philo[i].flag == 0)
			{
				philo[i].flag = 1;
				j++;
				if (j == info.nbr_philo)
					return (0);
			}
			if ((get_time() - philo[i].end_eating) >=
				(unsigned long)philo[i].info.time_die)
			{
				ft_printf("died", &philo[i]);
				return (0);
			}
		}
	}
}