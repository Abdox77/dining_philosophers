/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:14 by amohdi            #+#    #+#             */
/*   Updated: 2024/05/09 11:55:37 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (ft_error("Invalid number of arguments\n"),
			EXIT_FAILURE);
	if (get_args(ac, av, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_data(&data);
	cleanup(&data);
	return (0);
}
