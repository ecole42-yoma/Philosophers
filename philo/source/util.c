/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmkim <codeyoma@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:15:21 by yongmkim          #+#    #+#             */
/*   Updated: 2022/05/14 02:53:02 by yongmkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	is_space(char c)
{
	char	*space;

	space = "\t\n\v\f\r ";
	while (*space)
	{
		if (*space == c)
			return (1);
		space++;
	}
	return (0);
}

static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_strlen(char *str)
{
	int	cnt;

	if (str == NULL || *str == '\0')
		return (0);
	cnt = 0;
	while (*str)
	{
		++cnt;
		str++;
	}
	return (cnt);
}

void	ft_print_fd(char *str, int fd)
{
	if (str == NULL || *str == '\0')
		return ;
	write(fd, str, ft_strlen(str));
}

int	ft_atoi(char *str)
{
	long long	sum;

	if (str == NULL || *str == '\0')
		return (-1);
	while (is_space(*str))
		str++;
	if (*str == '-')
		return (-1);
	sum = 0;
	while (is_digit(*str))
	{
		sum = (sum * 10) + (*str - '0');
		str++;
	}
	if (*str != '\0' && !(is_digit(*str)))
		return (-1);
	if (sum > 2147483647)
		return (-1);
	return (sum);
}
