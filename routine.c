/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:39:30 by zcherrad          #+#    #+#             */
/*   Updated: 2022/07/29 09:39:36 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void     *death_checker(void *arg)
{
    t_thread *thread = (t_thread *)arg;

    while (1)
	{
		if (currenttime() > thread->time_limit)
		{
			pthread_mutex_lock(&thread->var->print_lock);
			printf("%ld philosopher %d died \n",
				currenttime() - thread->start, thread->index);
			pthread_mutex_unlock(&thread->var->general_lock);
			return(NULL);
		}
		if (thread->var->num_times_toeat != -1
			&& thread->eaten >= thread->var->num_times_toeat
			* thread->var->num_of_philos)
		{
			pthread_mutex_lock(&thread->var->print_lock);
			printf("End\n");
			pthread_mutex_unlock(&thread->var->general_lock);
		}
		usleep(500);
	}
	return(NULL);
}

void    routine(void *arg)
{
    t_thread *thread = (t_thread *)arg;
    pthread_t t;
    
    pthread_create(&t, NULL, &death_checker, (void *)thread);
	pthread_detach(t);
    thread->time_limit = currenttime() + thread->var->time_to_die;
    thread->eaten = 0;
    while(1)
    {
        pthread_mutex_lock(&thread->var->fork[thread->left]);

        pthread_mutex_lock(&thread->var->print_lock);
        printf("%ld %d has taken a fork\n", currenttime() - thread->start ,thread->index);
        pthread_mutex_unlock(&thread->var->print_lock);
    
        pthread_mutex_lock(&thread->var->fork[thread->right]);
    
        pthread_mutex_lock(&thread->var->print_lock);
        printf("%ld %d has taken a fork\n", currenttime() - thread->start ,thread->index);
        pthread_mutex_unlock(&thread->var->print_lock);
    
        pthread_mutex_lock(&thread->var->print_lock);
        printf("%ld %d is eating\n", currenttime() - thread->start ,thread->index);
        pthread_mutex_unlock(&thread->var->print_lock);

        thread->time_limit = currenttime() + thread->var->time_to_die;
        
        usleep(thread->var->time_to_eat * 1000);
        thread->eaten++;
        pthread_mutex_unlock(&thread->var->fork[thread->left]);
        pthread_mutex_unlock(&thread->var->fork[thread->right]);
    
        pthread_mutex_lock(&thread->var->print_lock);
        printf("%ld %d is sleeping\n", currenttime() - thread->start ,thread->index);
        pthread_mutex_unlock(&thread->var->print_lock);
        usleep(thread->var->time_to_sleep * 1000);
    
        pthread_mutex_lock(&thread->var->print_lock);
        printf("%ld %d is thinking\n", currenttime() - thread->start ,thread->index);
        pthread_mutex_unlock(&thread->var->print_lock);
    }
    
}