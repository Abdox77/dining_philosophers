/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:08:21 by amohdi            #+#    #+#             */
/*   Updated: 2024/04/18 18:52:42 by amohdi           ###   ########.fr       */
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
	while (check_start_simulation(philo->data) == false)
		;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (check_if_simulation_ended(philo->data) == false)
	{
		eat(philo);
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
	pthread_mutex_lock(&(philo->data->print_mutex));
	printf("%ld %d is thinking\n", curr_time, philo->id + 1);
	pthread_mutex_unlock(&(philo->data->print_mutex));
}
