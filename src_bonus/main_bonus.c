/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:47:05 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:47:06 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	ft_pick_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	ft_stampa_pd(FORK, philo);
	sem_wait(philo->data->forks);
	ft_stampa_pd(FORK, philo);
}

int	ft_simposio(t_philo *philo)
{
	pthread_t	death;

	if (philo->last_meal == 0)
		philo->last_meal = ft_get_time_now();
	pthread_create(&death, NULL, ft_check_death, philo);
	pthread_detach(death);
	while (1)
	{
		ft_pick_forks(philo);
		if (!ft_eat(philo))
			return (1);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (0);
}

void	ft_start_process(t_philo *philo)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	philo->data->time_start = ft_get_time_now();
	while (i < philo->data->n_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			j += ft_simposio(&philo[i]);
			if (j >= 1)
			{
				exit(0);
			}
		}
		i++;
		usleep(150);
	}
}

void	ft_init_philo(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	ft_sem_create(data);
	while (i < data->n_philo)
	{
		philo[i].npasti = data->npasti;
		philo[i].data = data;
		philo[i].pid = -1;
		philo[i].burpo = 0;
		philo[i].id = i + 1;
		philo[i].dead = 0;
		philo[i].last_meal = 0;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	if (ft_check_args(ac, av))
		data = malloc(sizeof(t_data));
	else
		return (0);
	philo = malloc(sizeof(t_philo) * (ft_atoi(av[1]) + 1));
	ft_data_init(ac, av, data);
	if (data->n_philo > 1)
	{
		ft_init_philo(philo, data);
		sem_wait(data->stop);
		ft_start_process(philo);
		ft_spam_sem_wait(data);
		sem_wait(data->stop);
		ft_destroyall(philo, data);
	}
	else
		ft_lonely_boy(philo, data);
	return (0);
}
