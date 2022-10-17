/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:24:33 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/20 16:11:41 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

time_t	ft_get_time(void)
{
	struct timeval	start_time;

	if (gettimeofday(&start_time, NULL))
		return (0);
	return ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
}

time_t	ft_diff_time(time_t time_org)
{
	return (ft_get_time() - time_org);
}

void	ft_msg(char *str, int philo_idx, t_philo *philo, int key)
{
	pthread_mutex_lock(&philo->monitor->big_bang_mutex_sub);
	if (philo->monitor->die == 0)
	{
		printf("%06ld %d %s\n", \
			ft_diff_time(philo->monitor->big_bang), philo_idx, str);
		if (key)
			philo->monitor->die = 1;
	}
	pthread_mutex_unlock(&philo->monitor->big_bang_mutex_sub);
}

int	philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->big_bang_mutex);
	if (philo->monitor->die == 0)
	{
		ft_msg("\033[0;31mdied\033[0m", philo->philo_idx, philo, 1);
	}
	pthread_mutex_unlock(&philo->monitor->big_bang_mutex);
	return (1);
}

int	ft_think(t_philo *philo, time_t begin, time_t gap)
{
	int		check;

	check = 0;
	while (ft_diff_time(begin) <= (gap))
	{
		if (ft_diff_time(philo->last_eat) >= philo->die_ms)
		{
			return (philo_die(philo));
		}
		pthread_mutex_lock(&philo->monitor->big_bang_mutex);
		check = philo->monitor->die;
		pthread_mutex_unlock(&philo->monitor->big_bang_mutex);
		if (check)
			return (1);
		usleep(EPSILON / 2);
	}
	return (0);
}
