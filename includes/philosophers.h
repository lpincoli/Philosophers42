/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:47:25 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/17 10:58:56 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	pthread_t		big_bro;
	pthread_mutex_t	timewarp;
	pthread_mutex_t	kmangia;
	pthread_mutex_t	stampa;
	pthread_mutex_t	lastmeal;
	pthread_mutex_t	dad;
	pthread_mutex_t	*fks;
	int				gburp;
	int				n_philo;
	int				npasti;
	int				time_dormi;
	int				time_mangia;
	int				time_muori;
	int				n_end;
	int				dead;
	int				sazi;
	long long		time_start;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				fk1;
	int				fk2;
	t_data			*data;
	long long		last_meal;
	int				id;
	int				burpo;
}	t_philo;

int			fk_lock_2(int dx, int sx);
int			fk_lock_1(int sx, int dx);
int			check_morte(t_data *data);
void		*ft_osserva(void *ph);
int			ft_is_dead(t_philo *philo);
long long	delta_time(long long time);
long long	ft_get_time_now(void);
void		*ft_simposio(void *ph);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
void		ft_stampa_pd(t_philo *philo, char *str);
void		ft_destroyall(t_philo *philo);
int			ft_atoi(char *num);
int			ft_isdigit(char *str);
int			ft_check_args(int ac, char **av);
void		ft_gburpoplus(t_philo *philo);
void		ft_mutexalo(t_data *data);
int			ft_print_error(void);
void		ft_lonely_boy(t_philo *philo);
void		ft_data_init(int ac, char **av, t_data *data);

#endif
