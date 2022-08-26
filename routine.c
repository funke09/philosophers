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
    if( currenttime() - philo->last_time > philo->vars.time_to_die )
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
			// pthread_mutex_lock(philo->print_lock);

			print_lock("is dead", currenttime() - philo->start, philo->philos_num, philo->print_lock);
            *(philo->terminate) = 1;
			return(NULL);
		}
        usleep(100);
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
        && (philo->philos_num != philo->fork_left->last_user 
        && philo->philos_num != philo->fork_right->last_user))
        {
            philo->fork_left->is_closed = 1;
            print_lock("take left fork", currenttime() - philo->start, philo->philos_num, philo->print_lock);
            philo->fork_right->is_closed = 1;
            print_lock("take right fork", currenttime() - philo->start, philo->philos_num, philo->print_lock);
            pthread_mutex_unlock(&philo->fork_left->lock_fork);
            pthread_mutex_unlock(&philo->fork_right->lock_fork);
            return ;
        }
        pthread_mutex_unlock(&philo->fork_left->lock_fork);
        pthread_mutex_unlock(&philo->fork_right->lock_fork);
        usleep(100);
    }
}

void    eat(t_philo *philo)
{
    philo->last_time = currenttime();
    print_lock("is eating", currenttime() - philo->start, philo->philos_num, philo->print_lock);
    ft_usleep(philo->vars.time_to_eat);
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
    print_lock("is sleeping", currenttime() - philo->start, philo->philos_num, philo->print_lock);
    ft_usleep(philo->vars.time_to_sleep);
}

void    thinking(t_philo *philo)
{  
    print_lock("is thinking", currenttime() - philo->start, philo->philos_num, philo->print_lock);
}

void    *routine(void *arg)
{
    t_philo *philos_info = (t_philo*) arg;
    pthread_t watcher;

    philos_info->last_time = currenttime();
    pthread_create(&watcher, NULL, &death_watcher, (void*)philos_info);
    pthread_detach(watcher);
    while(!*(philos_info->terminate))
    {
        take_forks(philos_info);
        eat(philos_info);
        droping_forks_and_go_to_sleep(philos_info);
        thinking(philos_info);  
    }
    return(NULL);
}