/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoibarki <yoibarki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 12:10:19 by yoibarki          #+#    #+#             */
/*   Updated: 2023/08/28 20:18:23 by yoibarki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_shared_info
{
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_flag;
	pthread_mutex_t	protect_nbr_meals;
	pthread_mutex_t	protect_end_eating;
	unsigned long	start_time;
	int				nbr_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_philo_must_eat;
}					t_shared_info;

typedef struct s_philo
{
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	t_shared_info	*info;
	unsigned long	end_eating;
	pthread_t		threads_id;
	int				id_philo;
	int				flag;
	int				nbr_of_meals;

}					t_philo;

unsigned long		get_time(void);
int					ft_atoi(const char *str);
int					ft_check_meal(t_shared_info *info, t_philo *philo);
int					ft_mutex(t_philo *philo, t_shared_info *info);
int					ft_check_int(char **av);
void				ft_usleep(int nbr);
void				ft_printf(char *str, t_philo *ptr);
void				ft_get_next_fork(t_philo *philo, t_shared_info *info);
int					ft_destroy_mutex(t_philo *philo, t_shared_info *info);

#endif
