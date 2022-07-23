/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:45:45 by zcherrad          #+#    #+#             */
/*   Updated: 2022/07/23 23:00:42 by zcherrad         ###   ########.fr       */
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
    int time_to_eat;
    int time_to_die;
    int num_of_philos;
    int time_to_sleep;
    int num_times_toeat;
    pthread_mutex_t *fork;
    pthread_mutex_t	print_lock;
    pthread_mutex_t	general_lock;
    
}   t_vars;

typedef struct s_thread
{
    t_vars  *var;
    int			index;
	long		time_limit;
	int			nmeal;
	int			left;
	int			right;
	long int	start;
	long int	end;
    int         eaten;
}   t_thread;



//******* parssing *******//

int	ft_atoi(const char *str);
int check_char(char *str);
int parss_args(char **av, t_vars *vars);

//***** display ******//

long	currenttime(void);
void    routine(void *arg);


#endif