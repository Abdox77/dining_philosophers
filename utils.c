/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 22:10:53 by amohdi            #+#    #+#             */
/*   Updated: 2024/05/05 10:04:20 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(time * 1e3);
}

void	set_start_simulation(t_data *data)
{
	pthread_mutex_lock(&(data->start_mutex));
	data->start_simulation = TRUE;
	pthread_mutex_unlock(&(data->start_mutex));
}

static int	ft_strlen(char *s)
{
	if (!*s)
		return (0);
	return (ft_strlen(++s) + 1);
}

void	ft_error(char *s)
{
	write(STDERR_FILENO, RED "ERROR : " RESET, ft_strlen("ERROR : "));
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, "\n", 1);
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
