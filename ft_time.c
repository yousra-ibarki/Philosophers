/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoibarki <yoibarki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:09:56 by yoibarki          #+#    #+#             */
/*   Updated: 2023/08/27 16:30:20 by yoibarki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned long	get_time(void)
{
	struct timeval	begin;

	gettimeofday(&begin, NULL);
	return ((begin.tv_sec * 1000) + (begin.tv_usec / 1000));
}

void	ft_usleep(int nbr)
{
	unsigned long	begin;

	begin = get_time() + nbr;
	while (get_time() < begin)
	{
		usleep(500);
	}
}

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_printf(char *str, t_philo *ptr)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(ptr->info->lock_print));
	printf("%lu %d %s\n", (get_time() - ptr->info->start_time), 
		ptr->id_philo, str);
	if (ft_strcmp(str, "died") != 0)
		pthread_mutex_unlock(&(ptr->info->lock_print));
	if (ft_strcmp(str, "is eating") == 0)
	{
		pthread_mutex_lock(&(ptr->info->protect_nbr_meals));
		ptr->nbr_of_meals++;
		pthread_mutex_unlock(&(ptr->info->protect_nbr_meals));
	}
}
