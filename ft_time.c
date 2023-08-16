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

void	ft_printf(const char *str, t_philo *ptr)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(ptr->info.lock_print));
	printf("%lu %d %s\n", (get_time() - ptr->info.start_time), ptr->id_philo,
			str);
	if (str[0] != 'd')
		pthread_mutex_unlock(&(ptr->info.lock_print));
} 