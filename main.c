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
            return(-1);
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
    if(!forks)
        ft_error("Error : allocation failed\n");
    while (i < num_of_philos)
    {
        forks[i].is_closed = 0;
        forks[i].last_user = 0;
        if (pthread_mutex_init(&forks[i].lock_fork, NULL) < 0)
        {
            free(forks);
            // pthread_attr_destroy()
            // destroys, free
            ft_error("Error : filed to init mutex");
            return NULL;
        }  
        i++;  
    }
    return(forks);
}

t_philo *initialize_philos(t_vars var, t_fork *forks)
{
    t_philo *philos = malloc(sizeof(t_philo) * var.num_of_philos);
    int i = 0;
    pthread_mutex_t *print_mutex = malloc(sizeof(pthread_mutex_t));

    if(!philos || !print_mutex)
        ft_error("Error : allocation failed\n");
    int *terminate =  malloc(sizeof(int));
    if(!terminate)
        return(NULL);
    *terminate = 0;
    if(pthread_mutex_init(print_mutex, NULL) < 0)
        ft_error("Error : failed to init mutex\n");
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
    
    if(!philo_threads)
        ft_error("Error : allocstion faild\n");
    while (i < var.num_of_philos)
    {
        if(pthread_create(&philo_threads[i], NULL, &routine, (void*)&philos[i]) < 0)
            ft_error("Error : failed to create thread\n");
        if(pthread_detach(philo_threads[i]) < 0)
            ft_error("Error : failed to detach thread\n");
        i++;
    }
    if(pthread_join(philo_threads[0], NULL) < 0)
        ft_error("Error : failed to join thread\n");
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
        if(parss_args(av, &vars) < 0)
            ft_error("Error : !bad parameters\n");
        init_forks = initialize_forks(vars.num_of_philos);
        init_philosophers = initialize_philos(vars, init_forks);
        if(!init_forks || !init_philosophers)
            ft_error("Philosopher intialization failed.\n");
        ft_thread(init_philosophers, vars);
    }
    else
        ft_error("no nums of args\n");
    printf("we out\n");
    return (0);
}