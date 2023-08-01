#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>


typedef struct s_philo
{
    int id_philo;
    int rfork;
    int lfork;
    t_info *action;
    struct s_info *info;
} t_philo;

typedef struct s_info
{
    t_philo *philosopher;
    int nbr_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int nbr_philo_must_eat;
    int start;
} t_info;

#endif