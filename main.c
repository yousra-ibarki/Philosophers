#include "philosopher.h"

int	checkoverflow(unsigned long long out, int sign)
{
	if (out > 2146218951891489519)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	unsigned long long	out;
	int					i;
	int					sign;

	out = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		out *= 10;
		out += str[i++] - '0';
		if (checkoverflow(out, sign) == 0)
			return (0);
		else if (checkoverflow(out, sign) == -1)
			return (-1);
	}
	return (out * sign);
}

unsigned long	get_time(void)
{
	struct timeval	begin;

	gettimeofday(&begin, NULL);
	return ((begin.tv_sec * 1000) + (begin.tv_usec / 1000));
}

void	ft_printf(const char *str, t_philo *ptr)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(ptr->info.lock_print));
	printf("%lu %d %s\n", (get_time() - ptr->info.start_time), ptr->id_philo,
			str);
	pthread_mutex_unlock(&(ptr->info.lock_print));
}

void	*ft_routine(void *philo)
{
	t_philo	*ptr;
	int		i;
	int		nbr_eat;

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
		pthread_mutex_unlock(&(ptr->fork));
		pthread_mutex_unlock(ptr->next_fork);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_shared_info	info;
	int				i;

	i = -1;
	if (ac == 5 || ac == 6)
	{
		info.start_time = get_time();
		info.nbr_philo = ft_atoi(av[1]);
		info.time_die = ft_atoi(av[2]);
		info.time_eat = ft_atoi(av[3]);
		info.time_sleep = ft_atoi(av[4]);
		info.nbr_philo_must_eat = -1;
		if (ac == 6)
			info.nbr_philo_must_eat = ft_atoi(av[5]);
		if (pthread_mutex_init(&(info.lock_print), NULL) != 0)
			return (0);
		philo = malloc(sizeof(t_philo) * info.nbr_philo);
		if (!philo)
			return (0);
		//pthread_mutex_init
		while (++i < info.nbr_philo)
		{
			if (pthread_mutex_init(&(philo[i].fork), NULL) != 0)
				return (0);
			philo[i].id_philo = i + 1;
			philo[i].info = info;
		}
		//pthread_create5
		i = -1;
		while (++i < info.nbr_philo)
			philo[i].next_fork = &(philo[i + 1].fork);
		i = -1;
		while (++i < info.nbr_philo)
		{
			//printf("id_philo%d\n", philo[i].id_philo);
			pthread_create(&philo[i].threads_id, NULL, ft_routine, &philo[i]);
		}
		i = -1;
		while (++i < info.nbr_philo)
		{
			pthread_join(philo[i].threads_id, NULL);
		}
		//printf("time to sleep = %d\n", info.time_sleep);
	}
	else
		exit(0);
}
