/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:39:30 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/27 17:43:55 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat);
	if (currenttime() - philo->last_time > philo->vars.time_to_die)
	{
		pthread_mutex_unlock(&philo->last_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_eat);
	return (0);
}

void	*death_watcher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*(philo->terminate) == 0)
	{
		if (check_time(philo) == 1)
		{
			*(philo->terminate) = 1;
			print_mutex("is dead", currenttime() - philo->start, philo, 1);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo		*philos_info;
	pthread_t	watcher;

	philos_info = (t_philo *) arg;
	philos_info->last_time = currenttime();
	if (pthread_create(&watcher, NULL, &death_watcher, (void *) philos_info))
		ft_error("Error : death_watcher failed\n");
	if (pthread_detach(watcher))
		ft_error("Error : failed to detach death_watcher\n");
	while (!*(philos_info->terminate))
	{
		take_forks(philos_info);
		eat(philos_info);
		droping_forks_and_go_to_sleep(philos_info);
		thinking(philos_info);
	}
	return (NULL);
}
