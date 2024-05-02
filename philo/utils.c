/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:10:53 by amohdi            #+#    #+#             */
/*   Updated: 2024/04/18 18:49:05 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_start_simulation(t_data *data)
{
	pthread_mutex_lock(&(data->start_mutex));
	data->start_simulation = true;
	pthread_mutex_unlock(&(data->start_mutex));
}

void	ft_error(char *s)
{
	printf(RED "Error " RESET ": %s\n", s);
}

int	ft_atoi(char *s)
{
	int	result;

	result = 0;
	if (!s || !*s)
		ft_error("Invalid argument");
	while (*s && *s == ' ')
		s++;
	while (*s && *s >= '0' && *s <= '9')
	{
		result = result * 10 + *s - '0';
		s++;
	}
	if (*s)
		ft_error("Invalid argument");
	return (result);
}
