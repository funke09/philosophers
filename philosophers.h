/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:45:45 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/13 18:52:43 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_vars
{
    uint64_t time_to_eat; // int 
    uint64_t time_to_die;
    uint64_t time_to_sleep;
    int num_of_philos;
    int num_times_toeat;
    
}   t_vars;


typedef struct s_fork
{
    int is_closed;
    pthread_mutex_t lock_fork;
    int last_user;
    
}   t_fork;

typedef struct s_philo
{
    int philos_num;
    t_fork *fork_left;
    t_fork *fork_right;
    int last_time;
    int start;
    t_vars vars;
    pthread_mutex_t print_lock;
}   t_philo;


//******* parssing *******//

int	ft_atoi(const char *str);
int check_char(char *str);
int parss_args(char **av, t_vars *vars);

//***** display ******//

int	currenttime(void);
void    *routine(void *arg);


#endif