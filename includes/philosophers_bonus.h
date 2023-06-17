/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:47:21 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:47:21 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

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
# include <sys/wait.h>

# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5
# define DONE 6

typedef struct s_data
{
	sem_t			*time;
	sem_t			*sazio;
	sem_t			*kmangia;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*stop;
	sem_t			*last_meal;
	sem_t			*c_death;
	int				n_philo;
	int				time_dormi;
	int				time_mangia;
	int				time_muori;
	int				gburpo;
	int				max_eat;
	int				npasti;
	long long		time_start;
}	t_data;

typedef struct s_philo
{
	pthread_t		death;
	t_data			*data;
	pid_t			pid;
	long long		last_meal;
	int				id;
	int				dead;
	int				npasti;
	int				burpo;
}	t_philo;

int			ft_check_morte(t_philo *philo);
void		*ft_check_death(void *ph);
void		*ft_osserva(void *ph);
int			ft_is_dead(t_philo *philo);
long long	delta_time(long long time);
long long	ft_get_time_now(void);
int			ft_simposio(t_philo *philo);
int			ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
void		ft_stampa_pd(int id, t_philo *philo);
int			ft_atoi(char *num);
int			ft_isdigit(char *str);
int			ft_check_args(int ac, char **av);
void		ft_gburpoplus(t_philo *philo);
void		ft_mutexalo(t_data *data);
void		ft_lonely_boy(t_philo *philo, t_data *data);
void		ft_data_init(int ac, char **av, t_data *data);
void		ft_wait(t_philo *philo);
void		ft_destroyall(t_philo *philo, t_data *data);
void		ft_sem_create(t_data *data);
void		ft_spam_sem_wait(t_data *data);

#endif
