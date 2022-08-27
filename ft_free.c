/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:39:54 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/27 16:41:35 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philo(t_philo *philos)
{
	free(philos->terminate);
	free(philos->are_full);
	if (pthread_mutex_destroy(philos->print_lock))
		ft_error("Error : mutex_destroy failed\n");
	free(philos->print_lock);
	free(philos);
}

void	free_forks(t_fork *forks, int num_ofphilo)
{
	while (--num_ofphilo >= 0)
	{
		if (pthread_mutex_destroy(&forks[num_ofphilo].lock_fork))
			ft_error("Error : failed to destroy_mutex !\n");
	}
}

void	free_resources(t_philo *philo, t_fork *forks)
{
	free_philo(philo);
	(void)forks;
	free_forks(forks, philo->vars.num_of_philos);
}
