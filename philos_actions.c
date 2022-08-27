/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:53:41 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/27 16:38:29 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	while (!*(philo->terminate))
	{
		pthread_mutex_lock(&philo->fork_left->lock_fork);
		pthread_mutex_lock(&philo->fork_right->lock_fork);
		if (philo->fork_left->is_closed == 0 && \
			philo->fork_right->is_closed == 0 \
			&& (philo->philos_num != philo->fork_left->last_user \
				&& philo->philos_num != philo->fork_right->last_user))
		{
			philo->fork_left->is_closed = 1;
			print_mutex("take left fork", currenttime() - \
			philo->start, philo, 0);
			philo->fork_right->is_closed = 1;
			print_mutex("take right fork", currenttime() - \
			philo->start, philo, 0);
			pthread_mutex_unlock(&philo->fork_left->lock_fork);
			pthread_mutex_unlock(&philo->fork_right->lock_fork);
			return ;
		}
		pthread_mutex_unlock(&philo->fork_left->lock_fork);
		pthread_mutex_unlock(&philo->fork_right->lock_fork);
		usleep(100);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_eat);
	philo->last_time = currenttime();
	pthread_mutex_unlock(&philo->last_eat);
	print_mutex("is eating", currenttime() - philo->start, philo, 0);
	ft_usleep(philo->vars.time_to_eat);
	philo->meals_eaten += 1;
	if (philo->vars.num_times_toeat != -1)
	{
		if (philo->meals_eaten == philo->vars.num_times_toeat)
			*(philo->are_full) += 1;
		if (*(philo->are_full) == philo->vars.num_of_philos)
			*(philo->terminate) = 1;
	}
}

void	droping_forks_and_go_to_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_left->lock_fork);
	pthread_mutex_lock(&philo->fork_right->lock_fork);
	philo->fork_left->is_closed = 0;
	philo->fork_right->is_closed = 0;
	philo->fork_left->last_user = philo->philos_num;
	philo->fork_right->last_user = philo->philos_num;
	pthread_mutex_unlock(&philo->fork_left->lock_fork);
	pthread_mutex_unlock(&philo->fork_right->lock_fork);
	print_mutex("is sleeping", currenttime() - philo->start, philo, 0);
	ft_usleep(philo->vars.time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_mutex("is thinking", currenttime() - philo->start, philo, 0);
}

void	give_forks(t_philo *philo, t_fork *forks)
{
	if ((philo->philos_num - 1) == 0)
	{
		philo->fork_right = &forks[philo->philos_num - 1];
		philo->fork_left = &forks[((philo->philos_num - 1) + 1) % \
			philo->vars.num_of_philos];
	}
	else
	{
		philo->fork_left = &forks[philo->philos_num - 1];
		philo->fork_right = &forks[((philo->philos_num - 1) + 1) % \
			philo->vars.num_of_philos];
	}
}
