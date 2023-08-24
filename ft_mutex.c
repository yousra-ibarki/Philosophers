/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoibarki <yoibarki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:09:39 by yoibarki          #+#    #+#             */
/*   Updated: 2023/08/24 12:15:49 by yoibarki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_get_next_fork(t_philo *philo, t_shared_info info)
{
	int	i;

	i = -1;
	while (++i < info.nbr_philo)
	{
		if (i == info.nbr_philo)
			info.nbr_philo = 0;
		philo[i].next_fork = &(philo[i + 1].fork);
		philo[i].end_eating = get_time();
	}
}

int	ft_mutex(t_philo *philo, t_shared_info info)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&(info.lock_print), NULL) != 0)
		return (0);
	while (++i < info.nbr_philo)
	{
		if (pthread_mutex_init(&(philo[i].fork), NULL) != 0)
			return (0);
		philo[i].id_philo = i + 1;
		philo[i].info = info;
	}
	return (1);
}
