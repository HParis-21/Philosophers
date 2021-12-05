/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 22:07:42 by hparis            #+#    #+#             */
/*   Updated: 2021/08/20 22:07:45 by hparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_phil	t_phil;

typedef struct s_data {
	int				num_phi;
	long			time_die;
	long			time_eat;
	long			time_slee;
	int				nbr_eat;
	int				fls_die;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mess;
	t_phil			*phi;
}					t_data;

typedef struct s_phil {
	int				name_ph;
	long			las_eat;
	int				f_die;
	int				f_eat;
	int				num_lun;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*sist;
}						t_phil;

long	get_time(void);
void	my_sleep(int waiting);
int		ft_atoi(const char *s);
int		ft_isdigit_str(const char *str);
int		print_return(char *str, int i);

void	print_mess(int name, char *str, t_data *sist);
int		check_arg(int argc, char **argv, t_data *sist);
int		mall_phi(t_data *sist, t_phil **philo, pthread_t **pthre);
void	set_fo(t_phil *philo, int low, int hight);
int		init_phill(t_data *sist, t_phil *philo);

void	one_phil(t_phil *philo);
void	*life(t_phil *philo);
void	*monitor(t_data *sist);
int		osnova(t_data *sist, pthread_t *pthre, t_phil *philo);
#endif
