/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoibarki <yoibarki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:08:09 by yoibarki          #+#    #+#             */
/*   Updated: 2023/08/27 17:35:13 by yoibarki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_routine(void *philo)
{
	t_philo	*ptr;
	int		i;

	i = 0;
	ptr = (t_philo *)philo;
	if (ptr->id_philo % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&(ptr->fork));
		ft_printf("has taken a fork", ptr);
		pthread_mutex_lock(ptr->next_fork);
		ft_printf("has taken a fork", ptr);
		ft_printf("is eating", ptr);
		ft_usleep(ptr->info->time_eat);
		pthread_mutex_lock(&(ptr->info->protect_end_eating));
		ptr->end_eating = get_time();
		pthread_mutex_unlock(&(ptr->info->protect_end_eating));
		pthread_mutex_unlock(&(ptr->fork));
		pthread_mutex_unlock(ptr->next_fork);
		ft_printf("is sleeping", ptr);
		ft_usleep(ptr->info->time_sleep);
		ft_printf("is thinking", ptr);
	}
	return (0);
}

int	ft_check_arg(int ac, char **av, t_shared_info *info)
{
	if (ft_check_int(av) == 0)
		return (0);
	info->start_time = get_time();
	info->nbr_philo = ft_atoi(av[1]);
	info->time_die = ft_atoi(av[2]);
	info->time_eat = ft_atoi(av[3]);
	info->time_sleep = ft_atoi(av[4]);
	info->nbr_philo_must_eat = -1;
	if (ac == 6)
		info->nbr_philo_must_eat = ft_atoi(av[5]);
	return (1);
}

void	ft_thread_creat(t_shared_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->nbr_philo)
	{
		pthread_create(&philo[i].threads_id, NULL, ft_routine, &philo[i]);
		philo[i].flag = 0;
	}
}

void	ft_free(t_shared_info *info, t_philo *philo)
{
	if (info)
		free(info);
	if (philo)
		free(philo);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_shared_info	*info;

	if (ac == 5 || ac == 6)
	{
		info = malloc(sizeof(t_shared_info));
		if (!info)
			return (0);
		if (ft_check_arg(ac, av, info) == 0 || info->nbr_philo == 0)
			return (ft_free(info, NULL), 0);
		philo = malloc(sizeof(t_philo) * info->nbr_philo);
		if (!philo)
			return (0);
		if (ft_mutex(philo, info) == 0)
			return (ft_free(info, philo), 0);
		ft_get_next_fork(philo, info);
		ft_thread_creat(info, philo);
		if (ft_check_death(info, philo) == 0 || ft_check_meal(info, philo) == 0)
		{
			ft_destroy_mutex(philo, info);
			return (ft_free(info, philo), 0);
		}
	}
	else
		return (0);
}
