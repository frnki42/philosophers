/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@frnki.dev>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/05/21 04:16:20 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// joins threads
void	join_threads(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->num_of_phil)
		pthread_join(table->philos[i++].thread, NULL);
}

// creates one thread, destroys and frees stuff on failure
int	create_thread(t_table *table, unsigned int i)
{
	unsigned int	j;

	if (pthread_create(&table->philos[i].thread, NULL, start_routine, &table->philos[i]))
	{
		pthread_mutex_lock(&table->alive_lock);
		table->all_alive = 0;
		pthread_mutex_unlock(&table->alive_lock);
		j = 0;
		while (j < i)
			pthread_join(table->philos[j++].thread, NULL);
		return (1);
	}
	return (0);
}

// calls create_thread num_of_phil amount of time
int	create_threads(t_table *table)
{
	unsigned int	i;
	pthread_t		monitor_thread;

	i = -1;
	while (++i < table->num_of_phil)
	{
		if (i % 2 == 0)
			usleep(1000);
		if (create_thread(table, i))
			return (1);
	}
	while (1)
	{
		pthread_mutex_lock(&table->start_lock);
		if (table->ready_count == table->num_of_phil)
		{
			pthread_mutex_unlock(&table->start_lock);
			set_t_start(table);
			pthread_mutex_lock(&table->start_lock);
			table->start = 1;
			pthread_mutex_unlock(&table->start_lock);
			break ;
		}
		pthread_mutex_unlock(&table->start_lock);
		usleep(100);
	}
	if (pthread_create(&monitor_thread, NULL, monitor, table->philos))
	{
		pthread_mutex_lock(&table->alive_lock);
		table->all_alive = 0;
		pthread_mutex_unlock(&table->alive_lock);
		join_threads(table);
		return (1);
	}
	join_threads(table);
	pthread_detach(monitor_thread);
	return (0);
}