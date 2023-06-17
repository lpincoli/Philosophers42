/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stra_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:46:58 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:46:58 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	ft_destroyall(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		kill(philo[i++].pid, SIGKILL);
	sem_close(philo->data->forks);
	sem_close(philo->data->time);
	sem_close(philo->data->kmangia);
	sem_close(philo->data->print);
	sem_close(philo->data->stop);
	sem_close(philo->data->c_death);
	sem_close(philo->data->last_meal);
	free(data);
	free(philo);
}

void	ft_wait(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->data->last_meal);
		philo->last_meal = ft_get_time_now();
		sem_post(philo->data->last_meal);
	}
}

void	ft_data_init(int ac, char **av, t_data *data)
{
	data->n_philo = ft_atoi(av[1]);
	data->time_muori = ft_atoi(av[2]);
	data->time_mangia = ft_atoi(av[3]);
	data->time_dormi = ft_atoi(av[4]);
	if (ac == 5)
		data->npasti = -1;
	else if (ac == 6)
	{
		data->npasti = ft_atoi(av[5]);
		data->gburpo = 0;
		data->max_eat = data->n_philo * ft_atoi(av[5]);
	}
	return ;
}

void	ft_lonely_boy(t_philo *philo, t_data *data)
{
	printf("0 Philo 1 sta pensando! 🤔 Ha fame!\n");
	printf("0 Ma ho solo una forchetta!! Maledizione!\n");
	printf("0 Mea culpa! Mi pento di tutto!\n");
	printf("%d Philo 1 e' morto! ☠️\n", data->time_muori);
	free(data);
	free(philo);
}

void	ft_sem_create(t_data *data)
{
	sem_unlink("c_death");
	sem_unlink("print");
	sem_unlink("stop");
	sem_unlink("forks");
	sem_unlink("time");
	sem_unlink("last_meal");
	sem_unlink("kmangia");
	data->c_death = sem_open("c_death", O_CREAT, 0644, 1);
	data->print = sem_open("print", O_CREAT, 0644, 1);
	data->stop = sem_open("stop", O_CREAT, 0644, 1);
	data->forks = sem_open("forks", O_CREAT, 0644, data->n_philo);
	data->time = sem_open("time", O_CREAT, 0644, 1);
	data->last_meal = sem_open("last_meal", O_CREAT, 0644, 1);
	data->kmangia = sem_open("kmangia", O_CREAT, 0644, 1);
}
