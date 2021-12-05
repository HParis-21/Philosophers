/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 21:58:51 by hparis            #+#    #+#             */
/*   Updated: 2021/08/20 21:59:30 by hparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_phil(t_phil *philo)
{
	philo->f_die = 1;
	philo->sist->fls_die = 1;
	printf("%ld ms: %d died\n", philo->sist->time_die + 1, 1);
}

void	*life(t_phil *philo)
{
	while (!philo->f_die && \
	(philo->sist->nbr_eat == -1 || philo->num_lun < philo->sist->nbr_eat))
	{
		pthread_mutex_lock(philo->left_fork);
		print_mess(philo->name_ph, "has taken a first fork \n", philo->sist);
		if (philo->sist->num_phi == 1)
			one_phil(philo);
		pthread_mutex_lock(philo->right_fork);
		print_mess(philo->name_ph, "has taken a second fork\n", philo->sist);
		if (philo->f_die)
			break ;
		print_mess(philo->name_ph, "is eating\n", philo->sist);
		philo->las_eat = get_time() + philo->sist->time_eat * 1000;
		my_sleep(philo->sist->time_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_mess(philo->name_ph, "is sleeping\n", philo->sist);
		my_sleep(philo->sist->time_slee);
		print_mess(philo->name_ph, "is thinking\n", philo->sist);
		philo->num_lun++;
	}
	if (philo->sist->nbr_eat > 0 && philo->num_lun == philo->sist->nbr_eat)
		philo->f_eat = 1;
	return (NULL);
}

void	*monitor(t_data *sist)
{
	int		i;
	int		doned;

	while (1)
	{
		doned = 1;
		i = -1;
		while (++i < sist->num_phi)
		{
			doned = doned && sist->phi[i].f_eat;
			if (!sist->phi[i].f_eat && \
				(get_time() - sist->phi[i].las_eat > sist->time_die))
			{
				sist->phi[i].f_die = 1;
				sist->fls_die = 1;
				pthread_mutex_lock(sist->mess);
				printf("%ld ms: %d died\n", get_time(), i + 1);
				return (NULL);
			}
		}
		if (doned)
			break ;
	}
	return (NULL);
}

int	osnova(t_data *sist, pthread_t *pthre, t_phil *philo)
{
	int	i;

	i = -1;
	while (++i < sist->num_phi)
	{
		if (pthread_create(&pthre[i], NULL, \
			(void *(*)(void *)) life, &philo[i]) != 0)
			print_return("Thread creation error/n", 1);
		usleep (100);
	}
	if (pthread_create(&pthre[sist->num_phi], NULL, \
		(void *(*)(void *)) monitor, sist) != 0)
		print_return("Thread creation error/n", 1);
	pthread_join(pthre[sist->num_phi], NULL);
	i = 0;
	while (i < sist->num_phi)
		pthread_detach(pthre[i++]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		sist;
	t_phil		*philo;
	pthread_t	*pthre;

	if (check_arg(argc, argv, &sist))
		print_return("Wrong arguments\n", 1);
	if (mall_phi(&sist, &philo, &pthre))
		return (1);
	if (init_phill(&sist, philo) && (pthread_mutex_init(sist.mess, NULL) != 0))
		print_return("Mutex initialization error/n", 1);
	osnova(&sist, pthre, philo);
	return (0);
}
