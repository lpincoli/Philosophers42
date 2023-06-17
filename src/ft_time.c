/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:46:29 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:46:29 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	ft_get_time_now(void)
{
	struct timeval	tp;
	long long		ms;

	gettimeofday(&tp, NULL);
	ms = (tp.tv_sec * 1000) + (tp.tv_usec * 0.001);
	return (ms);
}

long long	delta_time(long long time)
{
	if (time > 0)
		return (ft_get_time_now() - time);
	return (0);
}

int	ft_ca(t_philo *philo, long long dt, long long tn)
{
	int			i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		if (tn - philo[i].last_meal > dt)
		{
			pthread_mutex_lock(&philo->data->stampa);
			pthread_mutex_lock(&philo->data->dad);
			printf("%llu Philo %d e' morto! ☠️\n",
				delta_time(philo->data->time_start), philo[i].id);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->dad);
			pthread_mutex_unlock(&philo->data->stampa);
			pthread_mutex_unlock(&philo->data->lastmeal);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_dead(t_philo *philo)
{
	long long	dead_time;
	long long	time_now;
	int			ret;

	dead_time = (long long)philo->data->time_muori;
	pthread_mutex_lock(&philo->data->timewarp);
	time_now = ft_get_time_now();
	pthread_mutex_unlock(&philo->data->timewarp);
	pthread_mutex_lock(&philo->data->lastmeal);
	ret = ft_ca(philo, dead_time, time_now);
	if (ret == 0)
		pthread_mutex_unlock(&philo->data->lastmeal);
	return (ret);
}

int	ft_print_error(void)
{
	printf("Invalid parameters!\n");
	return (0);
}
