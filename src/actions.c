/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:46:10 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/17 10:59:23 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_destroyall(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		pthread_mutex_destroy(&philo->data->fks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data->timewarp);
	pthread_mutex_destroy(&philo->data->kmangia);
	pthread_mutex_destroy(&philo->data->stampa);
	pthread_mutex_destroy(&philo->data->dad);
	pthread_mutex_destroy(&philo->data->lastmeal);
	free(philo->data->fks);
	free(philo->data);
	free(philo);
}

void	ft_stampa_pd(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->stampa);
	if (check_morte(philo->data) == 1 || philo->data->sazi == 1)
	{
		pthread_mutex_unlock(&philo->data->stampa);
		return ;
	}
	printf("%llu %d %s\n",
		delta_time(philo->data->time_start), philo->id, str);
	usleep(5);
	pthread_mutex_unlock(&philo->data->stampa);
}

void	ft_eat(t_philo *philo)
{
	if (check_morte(philo->data) == 1)
		return ;
	pthread_mutex_lock(&philo->data->fks[fk_lock_1(philo->fk1, philo->fk2)]);
	pthread_mutex_lock(&philo->data->fks[fk_lock_2(philo->fk1, philo->fk2)]);
	ft_stampa_pd(philo, "ha preso la sua forchetta 🍴");
	ft_stampa_pd(philo, "ha preso la forchetta di un altro 🍴");
	(*philo).burpo += 1;
	ft_stampa_pd(philo, "sta mangiando!🍝");
	usleep((*philo).data->time_mangia * 1000);
	pthread_mutex_lock(&philo->data->lastmeal);
	philo->last_meal = ft_get_time_now();
	pthread_mutex_unlock(&philo->data->lastmeal);
	pthread_mutex_unlock(&philo->data->fks[fk_lock_1(philo->fk1, philo->fk2)]);
	pthread_mutex_unlock(&philo->data->fks[fk_lock_2(philo->fk1, philo->fk2)]);
}

void	ft_sleep(t_philo *philo)
{
	if (check_morte(philo->data) == 1)
		return ;
	ft_stampa_pd(philo, "sta dormendo! 💤");
	usleep((*philo).data->time_dormi * 1000);
}

void	ft_think(t_philo *philo)
{
	if (check_morte(philo->data) == 1)
		return ;
	ft_stampa_pd(philo, "sta pensando! 🤔 Ha fame!");
}
