/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:23:27 by amohdi            #+#    #+#             */
/*   Updated: 2024/04/20 13:01:23 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = (time.tv_sec * 1e3) + (time.tv_usec / 1e3);
	return (result);
}

t_bool	check_if_simulation_ended(t_data *data)
{
	t_bool	state;

	pthread_mutex_lock(&(data->stop_mutex));
	state = data->end_simulation;
	pthread_mutex_unlock(&(data->stop_mutex));
	return (state);
}

t_bool	safe_write(t_data *data, long time, int id, char *message)
{
	pthread_mutex_lock(&data->print_mutex);
	if (time == -1)
		printf("%s\n", message);
	if (check_if_simulation_ended(data) == true)
		return (pthread_mutex_unlock(&data->print_mutex), true);
	printf("%ld %d %s\n", time, id, message);
	pthread_mutex_unlock(&data->print_mutex);
	return (false);
}

void	pickup_forks(t_philo *philo)
{
	long	curr_time;

	pthread_mutex_lock(philo->right_fork);
	curr_time = get_time() - philo->data->start_of_program;
	safe_write(philo->data, curr_time, philo->id + 1, "has taken a fork");
	// pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	curr_time = get_time() - philo->data->start_of_program;
	safe_write(philo->data, curr_time, philo->id + 1, "has taken a fork");
}

void	putdown_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
