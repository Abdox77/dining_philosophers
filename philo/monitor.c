/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 02:11:44 by amohdi            #+#    #+#             */
/*   Updated: 2024/04/18 18:46:56 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	safe_stop_simulation(t_data *data)
{
	pthread_mutex_lock(&(data->stop_mutex));
	data->end_simulation = true;
	pthread_mutex_unlock(&(data->stop_mutex));
}

static int	check_for_death(t_philo philo)
{
	long	curr_time;

	pthread_mutex_lock(&(philo.data->time_mutex));
	curr_time = get_time() - philo.data->start_of_program
		- philo.last_time_eaten;
	pthread_mutex_unlock(&(philo.data->time_mutex));
	if (curr_time >= philo.data->time_to_die)
		return (true);
	return (false);
}

static t_bool	are_philos_full(t_data *data)
{
	t_bool	res;

	res = false;
	pthread_mutex_lock(&(data->full_philos_mutex));
	if (data->num_of_full_philos == data->num_of_philo)
		res = true;
	pthread_mutex_unlock(&(data->full_philos_mutex));
	return (res);
}

void	*monitoring(void *args)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = (t_philo *)args;
	while (42)
	{
		if (++i == philo[0].data->num_of_philo)
			i = 0;
		if (check_for_death(philo[i]))
		{
			safe_write(philo[i].data, get_time()
				- philo[i].data->start_of_program, i + 1, "died");
			return (safe_stop_simulation(philo[i].data), NULL);
		}
		else if (are_philos_full(philo[i].data))
			return (safe_stop_simulation(philo[i].data), NULL);
	}
	return (NULL);
}
