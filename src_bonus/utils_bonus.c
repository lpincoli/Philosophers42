/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:47:09 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:47:10 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

int	ft_atoi(char *num)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((num[i] >= 9 && num[i] <= 13) || num[i] == 32)
		i++;
	if (num[i] == '-')
		return (-1);
	if (num[i] == '+')
		i++;
	while (num[i] >= '0' && num[i] <= '9')
	{
		res = res * 10 + (num[i] - 48);
		i++;
	}
	return (res);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_print_error(void)
{
	printf("Invalid parameters!\n");
	return (0);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (ft_print_error());
	while (i < ac)
	{
		if (ft_atoi(av[i]) >= 0 && ft_isdigit(av[i]))
			i++;
		else
			return (ft_print_error());
		if (ft_atoi(av[1]) == 0)
			return (ft_print_error());
		if (av[5])
		{
			if (ft_atoi(av[5]) == 0)
				return (ft_print_error());
		}
	}
	return (1);
}
