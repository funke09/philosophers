/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:39:30 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/13 19:05:02 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_time(t_philo *philo)
{
    if(currenttime() - philo->last_time > philo->vars.time_to_eat 
    || currenttime() - philo->last_time > philo->vars.time_to_sleep 
    || currenttime() - philo->last_time > philo->vars.time_to_die )
    // ||philo->vars.num_times_toeat < 1)
        return 1;
    return 0;
}

void     *death_watcher(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
	{
		if (check_time(philo) == 1)
		{
			pthread_mutex_lock(&philo->print_lock);
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%d philosopher %d died \n",
				currenttime() - philo->start, philo->philos_num);
			pthread_mutex_unlock(&philo->print_lock);
			return(NULL);
		}
	}
	return(NULL);
}

void take_forks(t_philo *philo)
{
    while(1)
    {   
        pthread_mutex_lock(&philo->fork_left->lock_fork);
        pthread_mutex_lock(&philo->fork_right->lock_fork);
        if (philo->fork_left->is_closed == 0 && philo->fork_right->is_closed == 0 
        && (philo->philos_num != philo->fork_right->last_user 
        && philo->philos_num != philo->fork_right->last_user))
        {
            philo->fork_left->is_closed = 1;
            printf("%d philo num %d takes fork left\n", currenttime() - philo->start, philo->philos_num);
            philo->fork_right->is_closed = 1;
            printf("%d philo num %d takes fork right\n", currenttime() - philo->start, philo->philos_num);
            pthread_mutex_unlock(&philo->fork_left->lock_fork);
            pthread_mutex_unlock(&philo->fork_right->lock_fork);
            return ;
        }
        pthread_mutex_unlock(&philo->fork_left->lock_fork);
        pthread_mutex_unlock(&philo->fork_right->lock_fork);
    }
}

void    eat(t_philo *philo)
{
    printf("%d philo %d is eating\n", currenttime() - philo->start, philo->philos_num);
    usleep(philo->vars.time_to_eat * 1000);
}
void    droping_forks_and_go_to_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork_left->lock_fork);
    pthread_mutex_lock(&philo->fork_right->lock_fork);
    philo->fork_left->is_closed = 0;
    philo->fork_right->is_closed = 0;
    philo->fork_left->last_user = philo->philos_num;
    philo->fork_right->last_user = philo->philos_num;
    pthread_mutex_unlock(&philo->fork_left->lock_fork);
    pthread_mutex_unlock(&philo->fork_right->lock_fork);
    printf("%d philo %d is sleeping\n", currenttime() - philo->start, philo->philos_num);
    usleep(philo->vars.time_to_sleep * 1000);
}

void    thinking(t_philo *philo)
{  
    printf("philo %d is thinking\n", philo->philos_num);
}

void    *routine(void *arg)
{
    t_philo *philos_info = (t_philo*) arg;
    int i = 0;
    pthread_t watcher;

    pthread_create(&watcher, NULL, &death_watcher, (void*)&philos_info);
    pthread_detach(watcher);
    philos_info->last_time = currenttime() + philos_info->vars.time_to_die;
    while(1)
    {
        take_forks(philos_info);
        eat(philos_info);
        droping_forks_and_go_to_sleep(philos_info);
        thinking(philos_info);  
    }
    return(NULL);
}