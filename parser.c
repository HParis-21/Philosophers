/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 22:05:20 by hparis            #+#    #+#             */
/*   Updated: 2021/08/20 22:05:23 by hparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mess(int name, char *str, t_data *sist)
{
	if (sist->fls_die == 1)
		return ;
	pthread_mutex_lock(sist->mess);
	printf("%ld ms: %d %s", get_time(), name, str);
	pthread_mutex_unlock(sist->mess);
}

int	check_arg(int argc, char **argv, t_data *sist)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (1);
	while (argv[++i])
	{
		if (!ft_isdigit_str(argv[i]))
			print_return("Wrong arguments\n", 1);
	}
	sist->num_phi = ft_atoi(argv[1]);
	sist->time_die = ft_atoi(argv[2]);
	sist->time_eat = ft_atoi(argv[3]);
	sist->time_slee = ft_atoi(argv[4]);
	if (argc == 6)
		sist->nbr_eat = ft_atoi(argv[5]);
	else
		sist->nbr_eat = -1;
	if (sist->time_die <= 0 || sist->time_slee <= 0 \
		|| sist->time_eat <= 0 || sist->num_phi <= 0)
		print_return("Wrong arguments\n", 1);
	return (0);
}

int	mall_phi(t_data *sist, t_phil **philo, pthread_t **pthre)
{
	(*philo) = malloc(sist->num_phi * sizeof(t_phil));
	if (!(*philo))
		print_return("Malloc error\n", 1);
	sist->phi = (*philo);
	(*pthre) = malloc((sist->num_phi + 1) * sizeof(pthread_t));
	if (!(*pthre))
		print_return("Malloc error\n", 1);
	sist->forks = malloc(sist->num_phi * sizeof(pthread_mutex_t));
	if (!(sist->forks))
		print_return("Malloc error\n", 1);
	sist->mess = malloc(sizeof (pthread_mutex_t));
	if (!sist->mess)
		print_return("Malloc error\n", 1);
	return (0);
}

void	set_fo(t_phil *philo, int low, int hight)
{
	philo->left_fork = &philo->sist->forks[low];
	philo->right_fork = &philo->sist->forks[hight];
}

int	init_phill(t_data *sist, t_phil *philo)
{
	int	i;

	i = 0;
	while (i < sist->num_phi)
	{
		philo[i].name_ph = i + 1;
		philo[i].sist = sist;
		philo[i].las_eat = 0;
		philo[i].f_die = 0;
		philo[i].num_lun = 0;
		if (pthread_mutex_init(&sist->forks[i], NULL))
			return (1);
		if (i > 0 && i % 2 == 0 && sist->num_phi > 2)
			set_fo(&philo[i], i - 1, i);
		else if (i > 0 && sist->num_phi > 2)
			set_fo(&philo[i], i, i - 1);
		else if (i > 0 && sist->num_phi == 2)
			set_fo(&philo[i], i - 1, i);
		i++;
	}
	philo[0].left_fork = &sist->forks[0];
	philo[0].right_fork = &sist->forks[sist->num_phi - 1];
	return (0);
}
