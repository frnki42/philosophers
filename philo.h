/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@frnki.dev>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 04:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/05/21 16:42:20 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H
// std header
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
// custom header
// macros
// typedef & structs

typedef struct s_philo t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	alive_lock;
	pthread_mutex_t	msg_lock;
	pthread_mutex_t	start_lock;
	t_philo			*philos;
	long			must_eat;
	unsigned int	ready_count;
	int				start;
	unsigned int	all_alive;
	unsigned int	num_of_phil;
	long	    	t_die;
	long	    	t_eat;
	long	    	t_sleep;
	long	    	t_start;
}	t_table;

typedef struct s_philo
{
	unsigned int	num;
	pthread_t		thread;
	unsigned int	ate;
	long			t_last;
	t_table			*table;
	pthread_mutex_t	meal_lock; 
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}	t_philo;

// prototypes
int		all_philos_ate(t_table *table, t_philo *philos);
int		check_args(int argc, char **argv);
long	check_time(void);
int		create_threads(t_table *table);
void	destroy_table(t_table *table);
long	ft_atolong(char *str);
int		init_table(int argc, char **argv, t_table *table);
int		init_mutexes(t_table *table);
void	join_threads(t_table *table);
void	*monitor(void *arg);
int		pick_up_forks(t_philo *philo);
void	precision_timer(long duration);
void	print_status(t_philo *philo, char *msg);
void	put_down_forks(t_philo *philo);
int		set_t_start(t_table *table);
int		set_table(int argc, char **argv, t_table *table);
void	solo_adventure(t_philo *philo);
void	*start_routine(void *arg);
int		set_philos(t_table *table);

#endif