/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:42:48 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/27 17:43:39 by zcherrad         ###   ########.fr       */
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
		if (num < 0 || !check_char(av[i]))
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
	pthread_mutex_t	*print_lock;
	int				i;

	i = -1;
	philos = malloc(sizeof(t_philo) * var.num_of_philos);
	print_lock = malloc(sizeof(pthread_mutex_t));
	philos->terminate = intallocate();
	philos->are_full = intallocate();
	philos->start = currenttime();
	if (pthread_mutex_init(print_lock, NULL) != 0 || !philos
		|| !print_lock
		|| !philos->terminate || !philos->are_full)
		ft_error("Error : failed to init philosophers\n");
	while (++i < var.num_of_philos)
	{	
		if (pthread_mutex_init(&philos[i].last_eat, NULL) != 0)
			ft_error("Error : failed to init mutex");
		fill_philos(&philos, print_lock, var, i);
		give_forks(&philos[i], forks);
	}
	return (philos);
}

void	ft_thread(t_philo *philos, t_vars var)
{
	int			i;
	pthread_t	*philo_threads;

	i = 0;
	philo_threads = malloc(sizeof(pthread_t) * var.num_of_philos);
	if (!philo_threads)
		ft_error("Error : allocation faild\n");
	while (i < var.num_of_philos)
	{
		if (pthread_create(&philo_threads[i], \
			NULL, &routine, (void *) &philos[i]) != 0)
			ft_error("Error : failed to create thread\n");
		i++;
	}
	i = 0;
	while (i < var.num_of_philos)
	{
		if (pthread_join(philo_threads[i], NULL))
			ft_error("Error : failed to join thread\n");
		i++;
	}
	free(philo_threads);
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
		free_resources(init_philosophers, init_forks);
	}
	else
		ft_error("Error : Usage = [philosophers] [time_TD] \
		[time_TE] [time_TS]\n");
	return (0);
}
