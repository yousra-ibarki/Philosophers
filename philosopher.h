/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoibarki <yoibarki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:10:19 by yoibarki          #+#    #+#             */
/*   Updated: 2023/08/17 12:10:24 by yoibarki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_shared_info
{
	pthread_mutex_t	lock_print;
	int				nbr_philo;
	int				flag;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	unsigned long	start_time;
	int				nbr_philo_must_eat;
}					t_shared_info;

typedef struct s_philo
{
	int				id_philo;
	pthread_t		threads_id;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	int				nbr_of_meals;
	unsigned long	end_eating;
	t_shared_info	info;

}					t_philo;

int					ft_atoi(const char *str);
unsigned long		get_time(void);
void				ft_usleep(int nbr);
void				ft_printf(const char *str, t_philo *ptr);
int					ft_check(t_shared_info info, t_philo *philo);
int					ft_mutex(t_philo *philo, t_shared_info info);
void				ft_get_next_fork(t_philo *philo, t_shared_info info);

#endif
