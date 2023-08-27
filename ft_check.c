/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoibarki <yoibarki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:09:13 by yoibarki          #+#    #+#             */
/*   Updated: 2023/08/27 16:27:15 by yoibarki         ###   ########.fr       */
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
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_meal(t_shared_info *info, t_philo *philo)
{
	int	i;
	int	j;

	j = 0;
	if (info->nbr_philo_must_eat != -1)
	{
		while (1)
		{
			i = -1;
			while (++i < info->nbr_philo)
			{
				pthread_mutex_lock(&(info->protect_nbr_meals));
				if (philo[i].info->nbr_philo_must_eat == philo[i].nbr_of_meals
					&& philo[i].flag == 0)
				{
					philo[i].flag = 1;
					j++;
					if (j == info->nbr_philo)
						return (0);
				}
				pthread_mutex_unlock(&(info->protect_nbr_meals));
			}
		}
	}
	return (1);
}

int	ft_check_death(t_shared_info *info, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < info->nbr_philo)
		{
			pthread_mutex_lock(&(info->protect_end_eating));
			if ((get_time() - philo[i].end_eating) 
				>= (unsigned long)philo[i].info->time_die)
			{
				ft_printf("died", &philo[i]);
				return (0);
			}
			pthread_mutex_unlock(&(info->protect_end_eating));
		}
	}
}
