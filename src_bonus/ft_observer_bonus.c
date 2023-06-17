/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_observer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:46:53 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:46:54 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	ft_spam_sem(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		sem_post(philo->data->stop);
		i++;
	}
}

void	ft_spam_sem_wait(t_data *data)
{
	int		i;

	i = 0;
	if (data->npasti != -1)
	{
		while (i < data->n_philo - 1)
		{
			sem_wait(data->stop);
			i++;
		}
	}
}

void	*ft_check_death(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (1)
	{
		sem_wait(philo->data->last_meal);
		if (ft_get_time_now() - philo->last_meal > philo->data->time_muori)
		{
			sem_post(philo->data->last_meal);
			ft_stampa_pd(DIED, philo);
			ft_spam_sem(philo);
			break ;
		}
		sem_post(philo->data->last_meal);
		sem_wait(philo->data->kmangia);
		if ((philo->data->npasti != -1)
			&& (philo->burpo == philo->data->npasti))
		{
			sem_post(philo->data->kmangia);
			break ;
		}
		sem_post(philo->data->kmangia);
	}
	return (NULL);
}
