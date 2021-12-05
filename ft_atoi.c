/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 22:04:06 by hparis            #+#    #+#             */
/*   Updated: 2021/08/20 22:04:09 by hparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_return(char *str, int i)
{
	printf("%s", str);
	return (i);
}

void	my_sleep(int waiting)
{
	long		now;

	now = get_time();
	while (get_time() < now + waiting)
		usleep(10);
}

long	get_time(void)
{
	static struct timeval	start;
	struct timeval			time;
	long long				ret;

	if (start.tv_sec == 0)
		gettimeofday(&start, NULL);
	gettimeofday(&time, NULL);
	ret = (time.tv_sec - start.tv_sec) * 1000 + \
	(time.tv_usec - start.tv_usec) / 1000;
	return (ret);
}

int	ft_isdigit_str(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || \
			str[i] == '-' || str[i] == '+'))
			return (0);
		if ((str[i] == '-' || str[i] == '+') && str[i + 1] == '\0')
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *s)
{
	int			i;
	int			z;
	int long	res;

	i = 0;
	z = 1;
	res = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
		z = ',' - s[i++];
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i++] - '0');
		if ((res > 2147483647 && z == 1) || (res > 2147483648 && z == -1))
			return (0);
	}
	return ((int)res * z);
}
