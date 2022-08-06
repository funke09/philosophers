/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:39:30 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/06 23:30:16 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void     *death_checker(void *arg)
{
    t_thread *thread = (t_thread *)arg;

    while (1)
	{
        // if (currenttime() <= thread->time_limit)
        //     printf(" currtime >>>>%ld time limits>>>%ld\n",currenttime(), thread->time_limit);
		if (currenttime() >= thread->time_limit)
		{
			pthread_mutex_lock(&thread->var->print_lock);
			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%llu philosopher %d died \n",
				currenttime() - thread->start, thread->index);
			pthread_mutex_unlock(&thread->var->general_lock);
            break;
            // exit(0);
			// return(NULL);
		}
		// if (thread->var->num_times_toeat != -1
		// 	&& thread->eaten >= thread->var->num_times_toeat
		// 	* thread->var->num_of_philos)
		// {
		// 	pthread_mutex_lock(&thread->var->print_lock);
		// 	printf("End\n");
		// 	pthread_mutex_unlock(&thread->var->general_lock);
		// }
		usleep(500);
	}
	return(NULL);
}

void    *routine(void *arg)
{
    t_thread *thread = (t_thread *)arg;
    pthread_t t;
    int i = 0;
    
    pthread_create(&t, NULL, &death_checker, &thread);
	pthread_detach(t);
    thread->time_limit = currenttime() + thread->var->time_to_die;
    // printf(" currtime >>>>%ld time limits>>>%ld\n",currenttime(), thread->time_limit);
    thread->eaten = 0;
    // printf("teeeeeeeessssst :%d\n" , thread->index);
    while(1)
    {
        // if (/* condition */)
        // {
        //     /* code */
        // }
        // printf("%llu time to die\n", thread->var->time_to_die);
        pthread_mutex_lock(&thread->var->fork[thread->left]);

        pthread_mutex_lock(&thread->var->print_lock);
        printf("%llu %d has taken a fork\n", currenttime() - thread->start ,thread->index);
        pthread_mutex_unlock(&thread->var->print_lock);
    
        pthread_mutex_lock(&thread->var->fork[thread->right]);
    
        pthread_mutex_lock(&thread->var->print_lock);
        printf("%llu %d has taken a fork\n", currenttime() - thread->start ,thread->index);
        pthread_mutex_unlock(&thread->var->print_lock);
    
        pthread_mutex_lock(&thread->var->print_lock);
        printf("%llu %d is eating\n", currenttime() - thread->start ,thread->index);
        pthread_mutex_unlock(&thread->var->print_lock);

        thread->time_limit = currenttime() + thread->var->time_to_die;
        // printf("i == %d\n", i++);  
        usleep(thread->var->time_to_eat * 1000);
        thread->eaten++;
        pthread_mutex_unlock(&thread->var->fork[thread->left]);
        pthread_mutex_unlock(&thread->var->fork[thread->right]);
    
        pthread_mutex_lock(&thread->var->print_lock);
        printf("%llu %d is sleeping\n", currenttime() - thread->start ,thread->index);
        pthread_mutex_unlock(&thread->var->print_lock);
        usleep(thread->var->time_to_sleep * 1000);
    
        pthread_mutex_lock(&thread->var->print_lock);
        printf("%llu %d is thinking\n", currenttime() - thread->start ,thread->index);
        pthread_mutex_unlock(&thread->var->print_lock);
    }
    
    return(NULL);
}