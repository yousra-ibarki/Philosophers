/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoibarki <yoibarki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:08:09 by yoibarki          #+#    #+#             */
/*   Updated: 2023/08/24 12:24:58 by yoibarki         ###   ########.fr       */
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
		ptr->nbr_of_meals++;
		ft_usleep(ptr->info.time_eat);
		ptr->end_eating = get_time();
		pthread_mutex_unlock(&(ptr->fork));
		pthread_mutex_unlock(ptr->next_fork);
		ft_printf("is sleeping", ptr);
		ft_usleep(ptr->info.time_sleep);
		ft_printf("is thinking", ptr);
	}
	return (0);
}

int	ft_check_arg(int ac, char **av, t_shared_info *info)
{
	// int	i;
	// int	j;

	if(ft_check_int(av) == 1)
		return 1;
	// i = 1;
	// while (av[i])
	// {
	// 	j = 0;
	// 	while (av[i][j])
	// 	{
	// 		if (av[i][j] >= '0' && av[i][j] <= '9')
	// 			j++;
	// 		else
	// 			return (1);
	// 	}
	// 	i++;
	// }
	info->start_time = get_time();
	info->nbr_philo = ft_atoi(av[1]);
	if (info->nbr_philo == 1)
		return (0);
	info->time_die = ft_atoi(av[2]);
	info->time_eat = ft_atoi(av[3]);
	info->time_sleep = ft_atoi(av[4]);
	info->nbr_philo_must_eat = -1;
	if (ac == 6)
		info->nbr_philo_must_eat = ft_atoi(av[5]);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_shared_info	info;
	int				i;
	int				j;

	j = 0;
	if (ac == 5 || ac == 6)
	{
		if (ft_check_arg(ac, av, &info) == 1)
			return (0);
		philo = malloc(sizeof(t_philo) * info.nbr_philo);
		if (!philo)
			return (0);
		if (ft_mutex(philo, info) == 0)
			return (0);
		ft_get_next_fork(philo, info);
		i = -1;
		while (++i < info.nbr_philo)
			pthread_create(&philo[i].threads_id, NULL, ft_routine, &philo[i]);
		philo[i].flag = 0;
		if (ft_check(info, philo) == 0)
			return (0);
		int i = -1;
		while(++i < info.nbr_philo)
			pthread_mutex_destroy(&philo[i]);
	}
	else
		return (0);
}
