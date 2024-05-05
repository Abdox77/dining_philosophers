/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:08:21 by amohdi            #+#    #+#             */
/*   Updated: 2024/05/05 10:11:31 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	check_start_simulation(t_data *data)
{
	t_bool	status;

	pthread_mutex_lock(&(data->start_mutex));
	status = data->start_simulation;
	pthread_mutex_unlock(&(data->start_mutex));
	return (status);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (check_start_simulation(philo->data) == FALSE)
		;
	if (philo->id % 2)
		ft_usleep(philo->data->time_to_eat / 2);
	while (check_if_simulation_ended(philo->data) == FALSE)
	{
		if (eat(philo) == TRUE)
			return (NULL);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	think(t_philo *philo)
{
	long	curr_time;

	if (is_philo_full(philo) || check_if_simulation_ended(philo->data))
		return ;
	curr_time = get_time() - philo->data->start_of_program;
	safe_write(philo->data, curr_time, philo->id + 1, "is sleeping");
}
