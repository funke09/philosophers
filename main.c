/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:42:48 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/13 18:47:26 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int parss_args(char **av, t_vars *vars)
{
    int i = 1;
    int num  = 0;
    
    while(av[i])
    {
        num = ft_atoi(av[i]);
        if (num == -1 || !check_char(av[i]))
        {
            printf("error\n");
            return -1;
        }
        //printf("%d\n",num);
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
    return(0);
}

t_fork  *initialize_forks(int num_of_philos)
{
    int i = 0;
    t_fork *forks;
    forks = malloc(sizeof(t_fork) * num_of_philos);
    // free fork
    while (i < num_of_philos)
    {
        forks[i].is_closed = 0;
        forks[i].last_user = 0;
        if (pthread_mutex_init(&forks[i].lock_fork, NULL))
        {
            // destroys, free
            return NULL;
        }  
        i++;  
    }
    return(forks);
}

t_philo *initialize_philos(t_vars var, t_fork *forks)
{
    t_philo *philos = malloc(sizeof(t_philo) * var.num_of_philos);
    //protection
    int i = 0;
    pthread_mutex_t *print_mutex = malloc(sizeof(pthread_mutex_t));
    int *terminate =  malloc(sizeof(int));
    *terminate = 0;
    pthread_mutex_init(print_mutex, NULL);
    //protection
    int start = currenttime();
    while(i < var.num_of_philos)
    {
        philos[i].philos_num = i + 1;
        philos[i].vars = var;
        philos[i].print_lock = print_mutex;
        philos[i].terminate = terminate;
        philos[i].start = start;
        if(i == 0) // dead_lock_solved
        {
            philos[i].fork_right = &forks[i];
            philos[i].fork_left = &forks[(i + 1) % var.num_of_philos];
        } 
        else 
        {
            philos[i].fork_left = &forks[i];
            philos[i].fork_right = &forks[(i + 1) % var.num_of_philos];
        }
        
        i++;
    }
    return (philos);
}

void    ft_thread(t_philo *philos, t_vars var)
{
    int i = 0;
    pthread_t *philo_threads;
    philo_threads = malloc(sizeof(pthread_t) * var.num_of_philos);
    int time = currenttime(); 
    
    //protection
    while (i < var.num_of_philos)
    {
        pthread_create(&philo_threads[i], NULL, &routine, (void*)&philos[i]);
        // pthread_detach(philo_threads[i]);
        //protection
        
        i++;
    }
    pthread_join(philo_threads[0], NULL); 
    i = 0;
    while (!*(philos->terminate))
        usleep(100);
    
}

int main(int ac, char **av)
{
    t_vars   vars;
    t_fork  *init_forks;
    t_philo *init_philosophers;
    
    if(ac == 5 || ac == 6)
    {
        parss_args(av, &vars);
     // return error
        // protect parss_args
        init_forks = initialize_forks(vars.num_of_philos);
        init_philosophers = initialize_philos(vars, init_forks);
        // protection 
        printf("was here\n");
        ft_thread(init_philosophers, vars);
    }
    else
     //ft_error();
         printf("no nums of args\n");
    printf("we out\n");
    return (0);
}