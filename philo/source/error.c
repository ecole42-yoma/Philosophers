/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:15:53 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/14 14:18:44 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	ft_free_all(t_info *info, int cnt, int key, char *msg)
{
	pthread_mutex_destroy(&info->philo[0].monitor->big_bang_mutex);
	pthread_mutex_destroy(&info->philo[0].monitor->big_bang_mutex_sub);
	if (key & 2)
	{
		ft_mutex_free(&info->fork, cnt);
		free(info->fork);
	}
	return (ft_free(info, 0, key, msg));
}

int	ft_free(t_info *info, int target, int key, char *msg)
{
	int	cnt;

	if (info == NULL)
		return (1);
	cnt = 0;
	while (cnt < info->philo_num)
	{
		if (key & 1 && cnt < target)
			free(info->philo[cnt].philo);
		else if (key & 2)
			free(info->philo[cnt].philo);
		++cnt;
	}
	free(info->philo);
	ft_print_fd(msg, 2);
	return (1);
}

static int	ft_error_case(int key)
{
	if (key == 0)
		ft_print_fd("./philo philo_num die_ms eat_ms sleep_ms [must_eat]\n", 2);
	else if (key == 1)
		ft_print_fd("invalid philo_num\n", 2);
	else if (key == 2)
		ft_print_fd("philo_num <= 500\n", 2);
	else if (key == 3)
		ft_print_fd("invalid die_ms\n", 2);
	else if (key == 4)
		ft_print_fd("invalid eat_ms\n", 2);
	else if (key == 5)
		ft_print_fd("invalid sleep_ms\n", 2);
	else if (key == 6)
		ft_print_fd("invalid must_eat\n", 2);
	return (1);
}

int	ft_argv_check(int argc, char **argv, t_info *info)
{
	info->philo_num = ft_atoi(argv[1]);
	if (info->philo_num <= 0)
		return (ft_error_case(1));
	if (info->philo_num > 500)
		return (ft_error_case(2));
	info->die_ms = ft_atoi(argv[2]);
	if (info->die_ms < 0)
		return (ft_error_case(3));
	info->eat_ms = ft_atoi(argv[3]);
	if (info->eat_ms < 0)
		return (ft_error_case(4));
	info->sleep_ms = ft_atoi(argv[4]);
	if (info->sleep_ms < 0)
		return (ft_error_case(5));
	info->eat_flag = 0;
	if (argc == 6)
	{
		info->eat_flag = 1;
		info->eat_cnt = ft_atoi(argv[5]);
		if (info->eat_cnt <= 0)
			return (ft_error_case(6));
	}
	return (0);
}

int	ft_argc_check(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_error_case(0);
		return (1);
	}
	return (0);
}
