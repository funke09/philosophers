/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:45:45 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/27 16:43:22 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_vars
{
	uint64_t	time_to_eat;
	uint64_t	time_to_die;
	uint64_t	time_to_sleep;
	int			num_of_philos;
	int			num_times_toeat;
}	t_vars;

typedef struct s_fork
{
	int				is_closed;
	pthread_mutex_t	lock_fork;
	int				last_user;
}	t_fork;

typedef struct s_philo
{
	int				philos_num;
	t_fork			*fork_left;
	t_fork			*fork_right;
	uint64_t		last_time;
	uint64_t		start;
	t_vars			vars;
	int				*terminate;
	int				meals_eaten;
	int				*are_full;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	last_eat;
}	t_philo;

//******* parssing *******//
int		ft_atoi(const char *str);
int		check_char(char *str);
int		parss_args(char **av, t_vars *vars);

//***** display ******//
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	droping_forks_and_go_to_sleep(t_philo *philo);
void	thinking(t_philo *philo);
void	*routine(void *arg);

//***** utils ******//
int		currenttime(void);
void	ft_error(char *str);
void	give_forks(t_philo *philo, t_fork *forks);
void	print_mutex(char *str, uint64_t time, t_philo *philo, int status);
void	fill_philos(t_philo **philo, pthread_mutex_t *mutex, t_vars var, int i);
void	ft_usleep(int n);
int		*intallocate(void);
void	free_resources(t_philo *philo, t_fork *forks);
#endif
