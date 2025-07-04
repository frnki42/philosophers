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
	table->philos = NULL;
	table->must_eat = -1;
	table->all_alive = 1;
	table->num_of_phil = 0;
	table->ready_count = 0;
	table->start = 0;
	table->t_die = 0;
	table->t_eat = 0;
	table->t_sleep = 0;
	table->t_start = 0;
}

// creates mutexes .. yep!
int	init_mutexes(t_table *table)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	while (++i < table->num_of_phil)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&table->forks[j++]);
			return (1);
		}
	}
	if (pthread_mutex_init(&table->msg_lock, NULL)
		|| pthread_mutex_init(&table->alive_lock, NULL)
		|| pthread_mutex_init(&table->start_lock, NULL))
	{
			j = 0;
			while (j < i)
				pthread_mutex_destroy(&table->forks[j++]);
			return (1);			
	}
	return (0);
}

// parses arguments and prepares table
int	init_table(int argc, char **argv, t_table *table)
{
	init_table_zero(table);
	if (set_table(argc, argv, table))
		return (1);
	return (0);
}