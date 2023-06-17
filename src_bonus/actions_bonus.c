/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:46:49 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:46:50 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	ft_stampa_pd(int id, t_philo *philo)
{
	long long	time;

	time = delta_time(philo->data->time_start);
	sem_wait(philo->data->print);
	if (id == FORK)
		printf("%llu Philo %d ha preso una forchetta 🍴\n", time, philo->id);
	else if (id == EATING)
		printf("%llu Philo %d sta mangiando!🍝\n", time, philo->id);
	else if (id == SLEEPING)
		printf("%llu Philo %d sta dormendo! 💤\n", time, philo->id);
	else if (id == THINKING)
		printf("%llu Philo %d sta pensando! 🤔\n", time, philo->id);
	else if (id == DIED)
		printf("%llu Philo %d e' morto ☠️\n", time, philo->id);
	else if (id == DONE)
		printf("Simulazione finita! Tutti sazi\n");
	if (id != DIED)
		sem_post(philo->data->print);
}

int	ft_eat(t_philo *philo)
{
	ft_stampa_pd(EATING, philo);
	usleep((*philo).data->time_mangia * 1000);
	if (philo->data->npasti != -1)
	{
		sem_wait(philo->data->kmangia);
		philo->burpo += 1;
		sem_post(philo->data->kmangia);
	}
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	if (philo->data->npasti == philo->burpo)
	{
		sem_post(philo->data->stop);
		ft_wait(philo);
		return (0);
	}
	sem_wait(philo->data->last_meal);
	philo->last_meal = ft_get_time_now();
	sem_post(philo->data->last_meal);
	return (1);
}

void	ft_sleep(t_philo *philo)
{
	ft_stampa_pd(SLEEPING, philo);
	usleep((*philo).data->time_dormi * 1000);
}

void	ft_think(t_philo *philo)
{
	ft_stampa_pd(THINKING, philo);
}
