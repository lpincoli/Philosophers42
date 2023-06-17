/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_orfane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:46:22 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/17 10:59:19 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_mutexalo(t_data *data)
{
	pthread_mutex_init(&data->timewarp, NULL);
	pthread_mutex_init(&data->kmangia, NULL);
	pthread_mutex_init(&data->stampa, NULL);
	pthread_mutex_init(&data->dad, NULL);
	pthread_mutex_init(&data->lastmeal, NULL);
	pthread_mutex_lock(&data->dad);
	data->dead = 0 ;
	pthread_mutex_unlock(&data->dad);
}

void	ft_lonely_boy(t_philo *philo)
{
	printf("0 Philo 1 sta pensando! 🤔 Ha fame!\n");
	printf("0 Ma ho solo una forchetta!! Maledizione!\n");
	printf("0 Mea culpa! Mi pento di tutto!\n");
	printf("%d Philo 1 e' morto! ☠️\n", philo->data->time_muori);
	ft_destroyall(philo);
}

void	ft_data_init(int ac, char **av, t_data *data)
{
	data->n_philo = ft_atoi(av[1]);
	data->time_muori = ft_atoi(av[2]);
	data->time_mangia = ft_atoi(av[3]);
	data->time_dormi = ft_atoi(av[4]);
	if (ac == 6)
		data->npasti = ft_atoi(av[5]);
	else
		data->npasti = 0;
	data->gburp = 1;
	data->sazi = 0;
	return ;
}
