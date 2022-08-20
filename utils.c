/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherrad <zcherrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:31:54 by zcherrad          #+#    #+#             */
/*   Updated: 2022/08/06 23:20:18 by zcherrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isspace(int x)
{
	if (x == '\t' || x == '\n' || x == '\v')
		return (1);
	if (x == '\f' || x == '\r' || x == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	z;

	i = 0;
	s = 1;
	z = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		z = (z * 10) + (str[i] - '0');
		i++;
	}
	return (z * s);
}


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int check_char(char *str)
{
    int i = 0;

    while(str[i])
    {
        if(!ft_isdigit(str[i]))
            return(0);
        i++;
    }
    return(1);
}

int	currenttime(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}
