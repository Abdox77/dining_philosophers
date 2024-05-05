/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:08:11 by amohdi            #+#    #+#             */
/*   Updated: 2024/05/05 10:14:52 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_philo_full(t_philo *philo)
{
	t_bool	res;

	res = FALSE;
	pthread_mutex_lock(&(philo->data->full_philos_mutex));
	if (philo->number_of_meals == philo->data->num_of_times_to_eat)
		res = TRUE;
	pthread_mutex_unlock(&(philo->data->full_philos_mutex));
	return (res);
}

static void	safe_update_time(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->time_mutex));
	philo->last_time_eaten = get_time() - philo->data->start_of_program;
	pthread_mutex_unlock(&(philo->data->time_mutex));
}

static void	safe_increment(t_philo *philo)
{
	philo->number_of_meals++;
	pthread_mutex_lock(&(philo->data->full_philos_mutex));
	if (philo->number_of_meals == philo->data->num_of_times_to_eat)
		philo->data->num_of_full_philos++;
	pthread_mutex_unlock(&(philo->data->full_philos_mutex));
}

t_bool	eat(t_philo *philo)
{
	if (is_philo_full(philo) || check_if_simulation_ended(philo->data))
		return (TRUE);
	if (pickup_forks(philo) == TRUE)
		return (TRUE);
	safe_update_time(philo);
	safe_write(philo->data, philo->last_time_eaten, philo->id + 1, "is eating");
	safe_increment(philo);
	ft_usleep(philo->data->time_to_eat);
	putdown_forks(philo);
	return (FALSE);
}

void	ft_sleep(t_philo *philo)
{
	long	curr_time;

	if (is_philo_full(philo) || check_if_simulation_ended(philo->data))
		return ;
	curr_time = get_time() - philo->data->start_of_program;
	safe_write(philo->data, curr_time, philo->id + 1, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}
