/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:45:05 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/14 20:22:14 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

void	ft_mutex_free(t_fork **fork, int idx)
{
	int	cnt;

	cnt = 0;
	while (cnt < idx)
	{
		pthread_mutex_destroy(&(*fork)[cnt].fork);
		++cnt;
	}
}

void	ft_mutex_fork_link(t_info *info, t_fork **fork)
{
	int	cnt;

	cnt = 0;
	while (cnt < info->philo_num)
	{
		if (cnt & 1)
		{
			info->philo[cnt].l_fork = &(*fork)[(cnt + 1) % info->philo_num];
			info->philo[cnt].r_fork = &(*fork)[cnt];
		}
		else
		{
			info->philo[cnt].l_fork = &(*fork)[cnt];
			info->philo[cnt].r_fork = &(*fork)[(cnt + 1) % info->philo_num];
		}
		++cnt;
	}
}

int	check_full(t_philo *philo)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&philo->monitor->big_bang_mutex);
	if ((philo->eat_flag) && (philo->monitor->eat_flag == philo->eat_cnt))
	{
		ft_msg("is full", philo->philo_idx, philo, 0);
		check = 1;
	}
	pthread_mutex_unlock(&philo->monitor->big_bang_mutex);
	return (check);
}

void	ft_usleep(time_t gap)
{
	time_t	dst;
	time_t	now;

	dst = ft_get_time() + gap;
	now = ft_get_time();
	while (now < dst)
	{
		usleep(250);
		now = ft_get_time();
	}
}

void	handle_exit(void)
{
	system("leaks philo");
}
