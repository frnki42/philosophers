/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/05/21 16:42:20 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// starts the stopwatch
int	set_t_start(t_table *table)
{
	unsigned int	i;

	table->t_start = check_time();
	if (table->t_start == -1)
		return (1);
	i = 0;
	while (i < table->num_of_phil)
		table->philos[i++].t_last = table->t_start;
	return (0);
}

// counts todays contestants
static int	set_num_of_phil(t_table *table, char *arg)
{
	long	tmp;

	tmp = ft_atolong(arg);
	if (tmp < 1 || tmp > 2048)
	{
		printf("# invalid number_of_philosophers!\n");
		printf("# pick a number between 1 and 2048.\n");
		return (1);
	}
	table->num_of_phil = tmp;
	return (0);
}

// that's the bouncer - if you are too young, you will get rejected 
static int	set_long(long *time, char *arg)
{
	*time = ft_atolong(arg);
	if (*time < 1)
	{
		printf("# invalid argument!\n");
		printf("# set a positive value.\n");
		return (1);
	}
	return (0);
}

// allocates forks and calls create_mutexes() to .. well, you already know
int	init_forks(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_phil);
	if (!table->forks)
	{
		printf("# malloc failed!\n");
		free(table->forks);
		return (1);
	}
	return (0);
}

// sets t_die, t_eat, t_sleep and num_of_phil
int	set_table(int argc, char **argv, t_table *table)
{
	if (set_num_of_phil(table, argv[1])
		|| set_long(&table->t_die, argv[2])
		|| set_long(&table->t_eat, argv[3])
		|| set_long(&table->t_sleep, argv[4])
		|| init_forks(table)
		|| init_mutexes(table))
		return (1);
	if (argc == 6)
	{
		if (set_long(&table->must_eat, argv[5]))
			return (1);
	}
	return (0);
}
