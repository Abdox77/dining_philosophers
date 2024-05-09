/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:10:53 by amohdi            #+#    #+#             */
/*   Updated: 2024/05/09 12:06:51 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_start_simulation(t_data *data)
{
	pthread_mutex_lock(&(data->start_mutex));
	data->start_simulation = TRUE;
	pthread_mutex_unlock(&(data->start_mutex));
}

void	ft_error(char *s)
{
	printf(RED "ERROR : " RESET "%s\n", s);
}

long	ft_atol(char *s)
{
	long long	result;

	result = 0;
	if (!s || !*s)
		return (ft_error("Invalid argument"), -1);
	while (*s && *s == ' ')
		s++;
	while (*s && *s >= '0' && *s <= '9' && result <= __LONG_MAX__)
	{
		result = result * 10 + *s - '0';
		s++;
	}
	if (*s)
		return (-1);
	return (result);
}
