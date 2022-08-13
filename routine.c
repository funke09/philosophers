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

// void     *death_checker(void *arg)
// {
//     t_thread *thread = (t_thread *)arg;

//     while (1)
// 	{
//         // if (currenttime() <= thread->time_limit)
//         //     printf(" currtime >>>>%ld time limits>>>%ld\n",currenttime(), thread->time_limit);
// 		if (currenttime() > thread->time_limit)
// 		{
// 			pthread_mutex_lock(&thread->var->print_lock);
// 			printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%llu philosopher %d died \n",
// 				currenttime() - thread->start, thread->index);
// 			pthread_mutex_unlock(&thread->var->general_lock);
//             // exit(0);
// 			return(NULL);
// 		}
// 		if (thread->var->num_times_toeat != -1
// 			&& thread->eaten >= thread->var->num_times_toeat
// 			* thread->var->num_of_philos)
// 		{
// 			pthread_mutex_lock(&thread->var->print_lock);
// 			printf("End\n");
// 			pthread_mutex_unlock(&thread->var->general_lock);
// 		}
// 		usleep(500);
// 	}
// 	return(NULL);
// }
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
            printf("philo num %d takes fork left\n", philo->philos_num);
            philo->fork_right->is_closed = 1;
            printf("philo num %d takes fork right\n" ,philo->philos_num);
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
    printf("philo %d is eating\n", philo->philos_num);
    usleep(philo->vars.time_to_eat * 1000);
}
void    go_to_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork_left->lock_fork);
    pthread_mutex_lock(&philo->fork_right->lock_fork);
    philo->fork_left->is_closed = 0;
    philo->fork_right->is_closed = 0;
    philo->fork_left->last_user = philo->philos_num;
    philo->fork_right->last_user = philo->philos_num;
    pthread_mutex_unlock(&philo->fork_left->lock_fork);
    pthread_mutex_unlock(&philo->fork_right->lock_fork);
    printf("philo %d is sleeping\n", philo->philos_num);
    usleep(philo->vars.time_to_sleep * 1000);
}

void    droping_forks_and_thinking(t_philo *philo)
{  
    printf("philo %d is thinking\n", philo->philos_num);
}

void    *routine(void *arg)
{
    t_philo *philos_info = (t_philo*) arg;
    int i = 0;
    while(1)
    {
        take_forks(philos_info);
        eat(philos_info);
        go_to_sleep(philos_info);
        droping_forks_and_thinking(philos_info);  
    }
    // t_thread *thread = (t_thread *)arg;
    // pthread_t t;
    // int i = 0;
    
    // pthread_create(&t, NULL, &death_checker, thread);
	// pthread_detach(t);
    // thread->time_limit = currenttime() + thread->var->time_to_die;
    // // printf(" currtime >>>>%ld time limits>>>%ld\n",currenttime(), thread->time_limit);
    // thread->eaten = 0;
    // // printf("teeeeeeeessssst :%d\n" , thread->index);
    // while(1)
    // {
    //     pthread_mutex_lock(&thread->var->fork[thread->left]);

    //     pthread_mutex_lock(&thread->var->print_lock);
    //     printf("%llu %d has taken a fork\n", currenttime() - thread->start ,thread->index);
    //     pthread_mutex_unlock(&thread->var->print_lock);
    
    //     pthread_mutex_lock(&thread->var->fork[thread->right]);
    
    //     pthread_mutex_lock(&thread->var->print_lock);
    //     printf("%llu %d has taken a fork\n", currenttime() - thread->start ,thread->index);
    //     pthread_mutex_unlock(&thread->var->print_lock);
    
    //     pthread_mutex_lock(&thread->var->print_lock);
    //     printf("%llu %d is eating\n", currenttime() - thread->start ,thread->index);
    //     pthread_mutex_unlock(&thread->var->print_lock);

    //     thread->time_limit = currenttime() + thread->var->time_to_die;
    //     // printf("i == %d\n", i++);  
    //     usleep(thread->var->time_to_eat * 1000);
    //     thread->eaten++;
    //     pthread_mutex_unlock(&thread->var->fork[thread->left]);
    //     pthread_mutex_unlock(&thread->var->fork[thread->right]);
    
    //     pthread_mutex_lock(&thread->var->print_lock);
    //     printf("%llu %d is sleeping\n", currenttime() - thread->start ,thread->index);
    //     pthread_mutex_unlock(&thread->var->print_lock);
    //     usleep(thread->var->time_to_sleep * 1000);
    
    //     pthread_mutex_lock(&thread->var->print_lock);
    //     printf("%llu %d is thinking\n", currenttime() - thread->start ,thread->index);
    //     pthread_mutex_unlock(&thread->var->print_lock);
    // }
    
    return(NULL);
}