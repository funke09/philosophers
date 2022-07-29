/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:42:48 by zcherrad          #+#    #+#             */
/*   Updated: 2022/07/25 22:46:31 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int parss_args(char **av, t_vars *vars)
{
    int i = 1;
    int num  = 0;
    

    // if ((i = atoi(av[1]) == -1))
    // {
    //     printf("error\n");
    //     return -1;
    // }
    // vars.num_of_philos = i;
    while(av[i])
    {
        num = ft_atoi(av[i]);
        if (num == -1 || !check_char(av[i]))
        {
            printf("error\n");
            return -1;
        }
        // printf("%d\n",num);
        if(i == 1)
            vars->num_of_philos = num;
        else if (i == 2)
            vars->time_to_die = num;
        else if (i == 3)
            vars->time_to_eat = num;
        else if(i == 4)
            vars->time_to_sleep = num;
        else if(i == 5)
            vars->num_times_toeat = num;
        i++;
        
    }
    if (i == 5)
        vars->num_times_toeat = -1;
    printf("%d\n%d\n%d\n%d\n%d\n", vars->num_of_philos, vars->time_to_die, vars->time_to_eat, vars->time_to_sleep, vars->num_times_toeat);
    return(0);
}

void initialize_forks(t_vars *vars)
{
    int i = 0;
    vars->fork = malloc(sizeof(pthread_mutex_t) * vars->num_of_philos);

    while (i < vars->num_of_philos)
    {
        if (pthread_mutex_init(&vars->fork[i], NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return;
        }
        i++;
    }
    pthread_mutex_init(&vars->general_lock, NULL);
    pthread_mutex_lock(&vars->general_lock);
}

void    ft_thread(t_vars *vars)
{
    t_thread thread;
    pthread_t tid[vars->num_of_philos];
    int i = 0;
    thread.start = currenttime();
    while(i < vars->num_of_philos)
    {
        //func//
        thread.var = vars;
        thread.index = i + 1;
        thread.right = thread.index;
        thread.left = thread.index + 1;
        if(thread.left > vars->num_of_philos)
            thread.left = 1;
        pthread_create(&tid[i], NULL, &routine, (void *)&thread);
        pthread_join(tid[i], NULL);
        i++;
    }
    i = 0;
	while (i < vars->num_of_philos)
		pthread_mutex_destroy(&vars->fork[i++]);
	pthread_mutex_destroy(&vars->print_lock);
	pthread_mutex_destroy(&vars->general_lock);
}

int main(int ac, char **av)
{
    t_vars   vars;
    
    if(ac == 5 || ac == 6)
    {
        parss_args(av, &vars);
        initialize_forks(&vars);
        ft_thread(&vars);
    }
    else
     //ft_error();
     printf("no nums of args\n");
    return (0);
}