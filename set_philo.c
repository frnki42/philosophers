/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/05/21 16:20:42 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// inits philo struct
static void	init_philo(t_table *table, unsigned int i)
{
	table->philos[i].ate = 0;
	table->philos[i].thread = 0;
	table->philos[i].num = i + 1;
	table->philos[i].table = table;
	table->philos[i].fork_left = &table->forks[i];
	if ((i + 1) < table->num_of_phil)
		table->philos[i].fork_right = &table->forks[i + 1];
	else 
		table->philos[i].fork_right = &table->forks[0];
	pthread_mutex_init(&table->philos[i].meal_lock, NULL);
}

// inits and sets philo (+mutex)
int	set_philos(t_table *table)
{
	unsigned int	i;

	table->philos = malloc(sizeof(t_philo) * table->num_of_phil);
	if (!table->philos)
		return (1);
	i = -1;
	while (++i < table->num_of_phil)
		init_philo(table, i);
	return (0);
}
