/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:09:12 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/14 20:08:06 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	put_down_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	if (fork->fork_check == 0)
		fork->fork_check = 1;
	pthread_mutex_unlock(&fork->fork);
}

static int	take_fork(t_philo *philo, t_fork *fork, time_t last_eat)
{
	int		is_taken;

	is_taken = 0;
	while ((ft_diff_time(last_eat) <= philo->die_ms))
	{
		pthread_mutex_lock(&fork->fork);
		if (fork->fork_check)
		{
			fork->fork_check = 0;
			is_taken = 1;
		}
		pthread_mutex_unlock(&fork->fork);
		if (is_taken)
			return (0);
		usleep(EPSILON / 5);
	}
	return (1);
}

static int	ft_delay(t_philo *philo, time_t gap, time_t begin)
{
	int		check;

	check = 0;
	while (ft_diff_time(begin) <= ((gap)))
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

static int	philo_eat(t_philo *philo, time_t eat_ms)
{
	if (take_fork(philo, philo->l_fork, philo->last_eat) == 0)
	{
		ft_msg("\033[0;36mhas taken a fork\033[0m", philo->philo_idx, philo, 0);
		if (take_fork(philo, philo->r_fork, philo->last_eat) == 0)
		{
			ft_msg("\033[0;32mis eating\033[0m", philo->philo_idx, philo, 0);
			philo->last_eat = ft_get_time();
			philo->eat_cnt += 1;
			if (ft_delay(philo, eat_ms, philo->last_eat))
				return (1);
		}
		else
			return (philo_die(philo));
		put_down_fork(philo->r_fork);
		put_down_fork(philo->l_fork);
		usleep(EPSILON / 2);
		if (check_full(philo))
			return (1);
		return (0);
	}
	else
		return (philo_die(philo));
}

void	*philo_init(void *argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	pthread_mutex_lock(&philo->monitor->big_bang_mutex);
	philo->last_eat = philo->monitor->big_bang;
	pthread_mutex_unlock(&philo->monitor->big_bang_mutex);
	if (philo->philo_idx & 1)
		usleep(EPSILON * 4);
	while (1)
	{		
		if (philo_eat(philo, philo->eat_ms))
			break ;
		if (philo->sleep_ms)
		{
			ft_msg("\033[0;33mis sleeping\033[0m", philo->philo_idx, philo, 0);
			if (ft_delay(philo, philo->sleep_ms, \
						philo->last_eat + philo->eat_ms))
				break ;
		}
		ft_msg("\033[0;34mis thinking\033[0m", philo->philo_idx, philo, 0);
		if (ft_think(philo, philo->last_eat, philo->die_ms * .8))
			break ;
	}
	return (NULL);
}
