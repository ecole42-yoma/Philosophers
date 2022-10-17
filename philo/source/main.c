/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:50:51 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/20 16:50:07 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

static int	ft_init_thread(t_info *info)
{
	int	cnt;

	cnt = 0;
	pthread_mutex_lock(&info->philo[0].monitor->big_bang_mutex);
	while (cnt < info->philo_num)
	{
		if (pthread_create(info->philo[cnt].philo, NULL, philo_init, \
											&info->philo[cnt]))
			return (ft_free_all(info, info->philo_num, 2, \
									"pthread create error\n"));
		++cnt;
	}
	info->philo[0].monitor->big_bang = ft_get_time();
	if (info->philo[0].monitor->big_bang == 0)
		return (ft_free_all(info, info->philo_num, 2, "get_time error\n"));
	pthread_mutex_unlock(&info->philo[0].monitor->big_bang_mutex);
	cnt = 0;
	while (cnt < info->philo_num)
	{
		pthread_join(*info->philo[cnt].philo, NULL);
		++cnt;
	}
	return (0);
}

static int	ft_init_mutex(t_info *info, t_fork **fork)
{
	int	cnt;

	*fork = (t_fork *)malloc(sizeof(t_fork) * info->philo_num);
	if (*fork == NULL)
		return (ft_free(info, 0, 2, "t_fork malloc error\n"));
	cnt = 0;
	while (cnt < info->philo_num)
	{
		(*fork)[cnt].fork_check = 1;
		if (pthread_mutex_init(&(*fork)[cnt].fork, NULL))
			return (ft_free_all(info, cnt, 2, "fork mutex init error\n"));
		++cnt;
	}
	ft_mutex_fork_link(info, fork);
	return (0);
}

static int	ft_init_monitor(t_monitor *monitor, t_info *info)
{
	monitor->die = 0;
	monitor->philo_num = info->philo_num;
	monitor->eat_flag = 0;
	if (info->eat_flag)
		monitor->eat_flag = info->eat_cnt;
	if (pthread_mutex_init(&(monitor->big_bang_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(monitor->big_bang_mutex_sub), NULL))
		return (1);
	return (0);
}

static int	ft_init_philo(t_info *info, t_monitor *monitor)
{
	int		cnt;

	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->philo_num);
	if (info->philo == NULL)
		return (1);
	if (ft_init_monitor(monitor, info))
		return (ft_free(info, 0, 5, "big_bang mutex init error\n"));
	cnt = 0;
	while (cnt < info->philo_num)
	{
		info->philo[cnt].philo = (pthread_t *)malloc(sizeof(pthread_t));
		if (info->philo[cnt].philo == NULL)
			return (ft_free_all(info, cnt, 1, "pthread_t malloc error\n"));
		info->philo[cnt].philo_idx = cnt + 1;
		info->philo[cnt].last_eat = 0;
		info->philo[cnt].eat_flag = info->eat_flag;
		info->philo[cnt].eat_cnt = 0;
		info->philo[cnt].die_ms = info->die_ms;
		info->philo[cnt].eat_ms = info->eat_ms;
		info->philo[cnt].sleep_ms = info->sleep_ms;
		info->philo[cnt].monitor = monitor;
		++cnt;
	}
	return (0);
}

//atexit(handle_exit);
int	main(int argc, char **argv)
{
	t_info		info;
	t_monitor	monitor;
	t_fork		*fork;

	if (ft_argc_check(argc))
		return (1);
	if (ft_argv_check(argc, argv, &info))
		return (1);
	if (ft_init_philo(&info, &monitor))
		return (1);
	if (ft_init_mutex(&info, &fork))
		return (1);
	info.fork = fork;
	if (ft_init_thread(&info))
		return (1);
	if (info.eat_flag || monitor.die)
		ft_free_all(&info, info.philo_num, 2, NULL);
	return (0);
}
