/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:14 by amohdi            #+#    #+#             */
/*   Updated: 2024/04/18 18:46:56 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (printf(RED "Error " RESET ": Invalid number of arguments\n"),
			EXIT_FAILURE);
	get_args(ac, av, &data);
	init_data(&data);
	cleanup(&data);
	return (0);
}
