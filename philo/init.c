/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:04:24 by amohdi            #+#    #+#             */
/*   Updated: 2024/04/20 12:57:09 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_args(int ac, char **av, t_data *data)
{
	data->num_of_philo = ft_atoi(av[1]);
	if (data->num_of_philo < 1 || data->num_of_philo > PHILO_MAX)
		return (ft_error("Invalid number of philosophers"), EXIT_FAILURE);
	data->num_of_times_to_eat = -1;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->num_of_times_to_eat = ft_atoi(av[5]);
		if (data->num_of_times_to_eat < 0)
			ft_error("error ");
	}
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		return (ft_error("Time stamps should be greater than 60 ms\n"),
			EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	init_data(t_data *data)
{
	data->start_of_program = get_time();
	data->start_simulation = false;
	data->end_simulation = false;
	data->num_of_full_philos = 0;
	init_mutexes(data);
	init_forks(data);
	init_philos(data);
	join_philos(data);
}

void	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&(data->time_mutex), NULL))
		ft_error("Mutex init failed");
	if (pthread_mutex_init(&(data->stop_mutex), NULL))
		ft_error("Mutex init failed");
	if (pthread_mutex_init(&(data->start_mutex), NULL))
		ft_error("Mutex init failed");
	if (pthread_mutex_init(&(data->print_mutex), NULL))
		ft_error("Mutex init failed");
	if (pthread_mutex_init(&(data->full_philos_mutex), NULL))
		ft_error("Mutex init failed");
}

void	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			ft_error("Mutex init failed");
	}
	i = -1;
	while (++i < data->num_of_philo)
	{
		data->philos[i].right_fork = &(data->forks[i]);
		if (data->num_of_philo != 1)
			data->philos[i].left_fork = &(data->forks[(i + 1) % data->num_of_philo]);
	}
	// 	data->philos[0].left_fork = &(data->forks[data->num_of_philo - 1]);
	// else
	if (data->num_of_philo == 1)
		data->philos[0].left_fork = &(data->forks[0]);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		data->philos[i].id = i;
		data->philos[i].data = data;
		data->philos[i].philo_is_full = false;
		data->philos[i].number_of_meals = 0;
		data->philos[i].last_time_eaten = get_time() - data->start_of_program;
		pthread_create(&(data->philos[i].philo), NULL, routine,
			&(data->philos[i]));
		i++;
	}
	set_start_simulation(data);
	pthread_create(&(data->monitor), NULL, monitoring, data->philos);
}
