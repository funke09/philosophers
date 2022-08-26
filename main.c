/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:42:48 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/26 21:19:31 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parss_args(char **av, t_vars *vars)
{
	int	i;
	int	num;

	i = 1;
	num = 0;
	while (av[i])
	{
		num = ft_atoi(av[i]);
		if (num == -1 || !check_char(av[i]))
			return (-1);
		if (i == 1)
			vars->num_of_philos = num;
		else if (i == 2)
			vars->time_to_die = num;
		else if (i == 3)
			vars->time_to_eat = num;
		else if (i == 4)
			vars->time_to_sleep = num;
		else if (i == 5)
			vars->num_times_toeat = num;
		i++;
	}
	if (i == 5)
		vars->num_times_toeat = -1;
	return (0);
}

t_fork	*initialize_forks(int num_of_philos)
{
	int		i;
	t_fork	*forks;

	i = 0;
	forks = malloc(sizeof(t_fork) * num_of_philos);
	if (!forks)
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
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_philo	*initialize_philos(t_vars var, t_fork *forks)
{
	t_philo			*philos;
	pthread_mutex_t	*print_mutex;
	int				i;

	i = -1;
	philos = malloc(sizeof(t_philo) * var.num_of_philos);
	print_mutex = malloc(sizeof(pthread_mutex_t));
	philos->terminate = intallocate();
	philos->are_full = intallocate();
	philos->start = currenttime();
	if (pthread_mutex_init(print_mutex, NULL) != 0 || !philos \
		|| !print_mutex || \
		!philos->terminate || !philos->are_full)
		ft_error("Error : failed to init philosophers\n");
	while (++i < var.num_of_philos)
	{	
		if (pthread_mutex_init(&philos[i].last_eat, NULL) != 0)
			ft_error("Error : failed to init mutex");
		philos[i].philos_num = i + 1;
		philos[i].vars = var;
		philos[i].print_lock = print_mutex;
		philos[i].terminate = philos[0].terminate;
		philos[i].start = philos[0].start;
		philos[i].are_full = philos[0].are_full;
		philos[i].meals_eaten = 0;
		give_forks(&philos[i], forks);
	}
	return (philos);
}

void	ft_thread(t_philo *philos, t_vars var)
{
	int			i;
	int			time;
	pthread_t	*philo_threads;

	i = 0;
	time = currenttime();
	philo_threads = malloc(sizeof(pthread_t) * var.num_of_philos);
	if (!philo_threads)
		ft_error("Error : allocstion faild\n");
	while (i < var.num_of_philos)
	{
		if (pthread_create(&philo_threads[i], \
			NULL, &routine, (void *) &philos[i]) != 0)
			ft_error("Error : failed to create thread\n");
		if (pthread_detach(philo_threads[i]))
			ft_error("Error : failed to detach thread\n");
		i++;
	}
	if (pthread_join(philo_threads[0], NULL) < 0)
		ft_error("Error : failed to join thread\n");
	i = 0;
	while (!*(philos->terminate))
		usleep(100);
}

int	main(int ac, char **av)
{
	t_vars	vars;
	t_fork	*init_forks;
	t_philo	*init_philosophers;

	if (ac == 5 || ac == 6)
	{
		if (parss_args(av, &vars) < 0)
			ft_error("Error : !bad parameters\n");
		init_forks = initialize_forks(vars.num_of_philos);
		init_philosophers = initialize_philos(vars, init_forks);
		if (!init_forks && !init_philosophers)
			ft_error("Philosopher intialization failed.\n");
		ft_thread(init_philosophers, vars);
	}
	else
		ft_error("no nums of args\n");
	return (0);
}
