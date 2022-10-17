/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:49:50 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/20 16:49:51 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

# define NULLL (void *)0
# define EPSILON 1000

/*
typedef enum e_bool
{
	false	= 0,
	true
}			t_bool;
*/

typedef struct s_monitor
{
	pthread_mutex_t	big_bang_mutex;
	pthread_mutex_t	big_bang_mutex_sub;
	time_t			big_bang;
	int				eat_flag;
	int				die;
	int				philo_num;
}					t_monitor;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_check;
}					t_fork;

typedef struct s_philo
{
	pthread_t		*philo;
	t_fork			*l_fork;
	t_fork			*r_fork;
	int				philo_idx;
	time_t			last_eat;
	int				eat_flag;
	int				eat_cnt;
	t_monitor		*monitor;
	time_t			die_ms;
	time_t			eat_ms;
	time_t			sleep_ms;
}					t_philo;

typedef struct s_info
{
	int				philo_num;
	time_t			die_ms;
	time_t			eat_ms;
	time_t			sleep_ms;
	int				eat_flag;
	int				eat_cnt;
	t_philo			*philo;
	t_fork			*fork;
}					t_info;

/* main_function
**-----------------------------------------------------------------------------
*/
void		*philo_init(void *argv);
int			philo_die(t_philo *philo);
int			ft_think(t_philo *philo, time_t begin, time_t gap);
int			check_full(t_philo *philo);

/* mutex_function
**-----------------------------------------------------------------------------
*/
void		ft_mutex_fork_link(t_info *info, t_fork **fork);
void		ft_mutex_free(t_fork **fork, int idx);

/* error_function
**-----------------------------------------------------------------------------
*/
int			ft_free_all(t_info *info, int cnt, int key, char *msg);
int			ft_free(t_info *info, int target, int key, char *msg);
int			ft_argv_check(int argc, char **argv, t_info *info);
int			ft_argc_check(int argc);
void		ft_sleep_check(t_info *info);
void		handle_exit(void);

/* util_function
**-----------------------------------------------------------------------------
*/
void		ft_msg(char *str, int x, t_philo *philo, int key);
time_t		ft_get_time(void);
time_t		ft_diff_time(time_t time_org);
void		ft_usleep(time_t gap);
int			ft_atoi(char *str);
void		ft_print_fd(char *str, int fd);

#endif
