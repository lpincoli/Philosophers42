/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_observer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:46:17 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/17 10:59:12 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_morte(t_data *data)
{
	pthread_mutex_lock(&data->dad);
	if (data->dead == 1)
	{
		pthread_mutex_unlock(&data->dad);
		return (1);
	}
	pthread_mutex_unlock(&data->dad);
	return (0);
}

int	ft_sazio(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < philo->data->n_philo && !check_morte(philo->data))
	{
		if (philo[i].burpo == philo->data->npasti)
			j += 1;
		i++;
	}
	if (j == philo->data->n_philo)
	{
		pthread_mutex_lock(&philo->data->stampa);
		printf("%llu Siamo tutti sazi 🤮\n", delta_time(philo->data->time_start));
		philo->data->sazi = 1;
		pthread_mutex_unlock(&philo->data->stampa);
		return (1);
	}
	return (0);
}

void	*ft_osserva(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	usleep(5000);
	if (philo->data->npasti > 0)
	{
		while (!philo->data->sazi && !check_morte(philo->data))
		{
			if (ft_is_dead(philo) || philo->data->sazi)
				break ;
			if (ft_sazio(philo))
				break ;
		}
	}
	else
	{
		while (check_morte(philo->data) == 0)
		{
			if (ft_is_dead(philo))
				break ;
		}
	}
	return (NULL);
}
