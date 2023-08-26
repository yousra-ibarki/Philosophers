/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoibarki <yoibarki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:09:39 by yoibarki          #+#    #+#             */
/*   Updated: 2023/08/26 22:40:22 by yoibarki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_get_next_fork(t_philo *philo, t_shared_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_philo)
	{
		if (i == (info->nbr_philo - 1))
			philo[i].next_fork = &(philo[0].fork);
		else
			philo[i].next_fork = &(philo[i + 1].fork);
		philo[i].end_eating = get_time();
	}
}

int	ft_mutex(t_philo *philo, t_shared_info *info)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&(info->lock_print), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->protect_nbr_meals), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->protect_end_eating), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->lock_flag), NULL) != 0)
		return (0);
	while (++i < info->nbr_philo)
	{
		if (pthread_mutex_init(&(philo[i].fork), NULL) != 0)
			return (0);
		philo[i].id_philo = i + 1;
		philo[i].info = info;
	}
	return (1);
}
