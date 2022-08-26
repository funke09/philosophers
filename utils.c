/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:31:54 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/26 20:58:38 by zcherrad         ###   ########.fr       */
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
