/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amohdi <amohdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:13:58 by amohdi            #+#    #+#             */
/*   Updated: 2024/05/05 10:15:06 by amohdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define RESET "\033[0m"
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define PHILO_MAX 200

typedef enum s_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t			philo;
	int					id;
	t_bool				philo_is_full;
	long				number_of_meals;
	long				last_time_eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philo;

struct					s_data
{
	t_philo				philos[PHILO_MAX];
	pthread_mutex_t		forks[PHILO_MAX];
	pthread_t			monitor;
	pthread_mutex_t		start_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		time_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		full_philos_mutex;
	t_bool				start_simulation;
	t_bool				end_simulation;
	int					num_of_philo;
	int					num_of_full_philos;
	int					num_of_times_to_eat;
	long				start_of_program;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
};

/*=====================utils=======================*/
long					get_time(void);
void					ft_usleep(long time);
long					ft_atol(char *s);
void					ft_error(char *s);
void					set_start_simulation(t_data *data);

/*=====================init=======================*/
int						get_args(int ac, char **av, t_data *data);
int						init_forks(t_data *data);
int						init_mutexes(t_data *data);
void					init_philos(t_data *data);
int						init_data(t_data *data);

/*=====================routine=======================*/
void					*routine(void *data);
t_bool					eat(t_philo *philo);
void					ft_sleep(t_philo *philo);
void					think(t_philo *philo);
t_bool					pickup_forks(t_philo *philo);
void					putdown_forks(t_philo *philo);
t_bool					is_philo_full(t_philo *philo);

/*=====================monitoring=======================*/
void					*monitoring(void *args);
t_bool					check_if_simulation_ended(t_data *data);
t_bool					safe_write(t_data *data, long time, int id,
							char *message);

/*=====================cleanup=======================*/
void					join_philos(t_data *data);
void					cleanup(t_data *data);

#endif
