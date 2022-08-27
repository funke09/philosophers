/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macos <macos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:31:54 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/27 12:29:08 by macos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	currenttime(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	exit(1);
}

void	print_lock(char *str, uint64_t time, t_philo *philo)
{
	pthread_mutex_lock(philo->print_lock);
	printf("[%8lldms][%8d]\t\t[%8s]\n", time, philo->philos_num, str);
	if (*(philo->terminate) != 1)
		pthread_mutex_unlock(philo->print_lock);
}

void	ft_usleep(int n)
{
	int	time;

	time = currenttime();
	while (n + time > currenttime())
		usleep(10);
}

void	fill_philos(t_philo **philo, pthread_mutex_t *mutex, t_vars var, int i)
{
	t_philo *philos;

	if (!philo || !*philo)
		return ;
	philos = *philo;
	philos[i].philos_num = i + 1;
	philos[i].vars = var;
	philos[i].print_lock = mutex;
	philos[i].terminate = philos[0].terminate;
	philos[i].start = philos[0].start;
	philos[i].are_full = philos[0].are_full;
	philos[i].meals_eaten = 0;
}
