/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 02:32:39 by amohdi            #+#    #+#             */
/*   Updated: 2024/04/20 13:05:24 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_philos(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_of_philo == 1)
	{
		pthread_join(data->monitor, NULL);
		return ;
	}
	while (i < data->num_of_philo)
	{
		pthread_join(data->philos[i].philo, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}

void	cleanup(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->start_mutex));
	pthread_mutex_destroy(&(data->stop_mutex));
	pthread_mutex_destroy(&(data->print_mutex));
	pthread_mutex_destroy(&(data->time_mutex));
}
