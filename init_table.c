/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/05/21 16:42:20 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// inits table struct
void	init_table_zero(t_table *table)
{
	table->forks = NULL;
	table->state_locks = NULL;
	table->must_eat = -1;
	table->all_alive = 1;
	table->num_of_phil = 0;
	table->t_die = 0;
	table->t_eat = 0;
	table->t_sleep = 0;
	table->t_start = 0;
}

// creates mutexes .. yep!
int	init_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->num_of_phil)
	{
		if (pthread_mutex_init(&table->forks[i++], NULL))
		{
			printf("# pthread_mutex_init failed!\n");
			destroy_table(table);
			return (1);
		}
		if (pthread_mutex_init(&table->state_locks[i], NULL))
		{
			printf("# pthread_mutex_init failed!\n");
			destroy_table(table);
			return (1);
		}
	}
	if (pthread_mutex_init(&table->msg_lock, NULL) ||
		pthread_mutex_init(&table->alive_lock, NULL))
	{
		printf("# pthread_mutex_init failed!\n");
		destroy_table(table);
		return (1);
	}
	return (0);
}

// allocates forks and calls create_mutexes() to .. well, you already know
int	init_forks_and_state_locks(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_phil);
	table->state_locks = malloc(sizeof(pthread_mutex_t) * table->num_of_phil);
	if (!table->forks || !table->state_locks)
	{
		printf("# malloc failed!\n");
		free(table->forks);
		free(table->state_locks);
		return (1);
	}
	if (init_mutexes(table))
		return (1);
	return (0);
}


// parses arguments and prepares table
int	init_table(int argc, char **argv, t_table *table)
{
	init_table_zero(table);
	set_table(argc, argv, table);
	if (init_forks_and_state_locks(table))
		return (1);
	return (0);
}
