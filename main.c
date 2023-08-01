#include "philosopher.h"

int checkoverflow(unsigned long long out, int sign)
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

int ft_atoi(const char *str)
{
    unsigned long long out;
    int i;
    int sign;

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

void *ft_routine(void *arg)
{
}


void ft_threads(t_info *philo)
{
    int i = 0;
    
}

int main(int ac, char **av)
{
    t_info philo;
    pthread_t *threads;
    pthread_mutex_t *forks;
    int resofcreat;
    int i = 0;

    if (ac == 5 || ac == 6)
    {
        philo.nbr_philo = ft_atoi(av[1]);
        philo.time_die = ft_atoi(av[2]);
        philo.time_eat = ft_atoi(av[3]);
        philo.time_sleep = ft_atoi(av[4]);
        if (ac == 6)
            philo.nbr_philo_must_eat = ft_atoi(av[5]);
        forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo.nbr_philo_must_eat);
        if (!forks)
            return NULL;

        while (i < philo.nbr_philo)
        {
            if (pthread_mutex_init(&(forks[i]), NULL) != 0)
                return NULL;
            i++;
        }
        
        philo.philosopher = malloc(sizeof(t_info) * philo.nbr_philo);
        if(!philo.philosopher)
            return NULL;
        philo.philosopher[0].id_philo = 1;
        philo.philosopher[0].lfork = &(forks[philo.nbr_philo - 1]);
        philo.philosopher[0].rfork = &(forks[philo.nbr_philo + 1]);

        i = 2;
        while (i < philo.nbr_philo)
        {
            philo.philosopher[i].id_philo = i;
            philo.philosopher[i].lfork = &(forks[i - 1]);
            philo.philosopher[i].rfork = &(forks[i + 1]);
            i++;
        }
            //begin threading
        ft_threads(&philo);
        while (i < philo.nbr_philo)
        {
            resofcreat = pthread_create(&threads, NULL, ft_routine, &);
            i++;
        }

        printf("time to sleep = %d\n", philo.time_sleep);
    }
    else
        exit(0);
}