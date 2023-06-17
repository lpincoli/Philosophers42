/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:46:35 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/17 10:59:07 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*ft_simposio(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->last_meal == 0)
		philo->last_meal = ft_get_time_now();
	while (!check_morte(philo->data) || !philo->data->sazi)
	{
		ft_eat(philo);
		if (philo->data->sazi || check_morte(philo->data))
			break ;
		ft_sleep(philo);
		if (philo->data->sazi || check_morte(philo->data))
			break ;
		ft_think(philo);
	}
	return (NULL);
}

void	ft_even_odd(t_philo *philo)
{
	int	j;

	j = 0;
	if (philo->data->n_philo % 2 == 0)
		j = 0;
	else
		j = 1;
	if (philo->id % 2 == 0 && j == 0)
		usleep(100);
	if (philo->id % 2 == 1 && j == 1)
		usleep(100);
	return ;
}

void	*ft_start_thread(t_philo *philo)
{
	int	i;

	i = 0;
	philo->data->time_start = ft_get_time_now();
	while (i < philo->data->n_philo)
	{
		ft_even_odd(&philo[i]);
		pthread_create(&philo[i].thread, NULL, ft_simposio, (void *)&philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&philo->data->big_bro, NULL, ft_osserva, (void *)philo);
	while (i < philo->data->n_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(philo->data->big_bro, NULL);
	return (NULL);
}

void	ft_init_philo(t_philo *philo, t_data *dt)
{
	t_data	*data;
	int		i;

	data = (t_data *)dt;
	i = 0;
	ft_mutexalo(dt);
	data->fks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * (data->n_philo + 1));
	while (i < data->n_philo)
	{
		philo[i].data = &data[0];
		philo[i].fk1 = i;
		if (i == data->n_philo - 1)
			philo[i].fk2 = 0;
		else
			philo[i].fk2 = i + 1;
		pthread_mutex_init(&data->fks[i], NULL);
		philo[i].id = i + 1;
		philo[i].burpo = 0;
		philo[i].last_meal = 0;
		i++;
	}
	i = 0;
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
	ft_init_philo(philo, data);
	if (data->n_philo > 1)
	{
		ft_start_thread(philo);
		usleep(10000);
		ft_destroyall(philo);
	}
	else
		ft_lonely_boy(philo);
	return (0);
}
