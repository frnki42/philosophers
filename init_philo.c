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
void	init_philo_zero(t_philo *philo, unsigned int index)
{
	philo[index].fork_left = NULL;
	philo[index].fork_right = NULL;
	philo[index].state_lock = NULL;
	philo[index].table = NULL;
	philo[index].ate = 0;
	philo[index].num = 0;
	philo[index].thread = 0;
	philo[index].t_last = 0;
}

// sets forks, table and num for philo
void	set_philo(t_philo *philo, t_table *table, unsigned int index)
{
	philo[index].fork_left = &table->forks[index];
	if ((index + 1) < table->num_of_phil)
		philo[index].fork_right = &table->forks[index + 1];
	else if ((index + 1) == table->num_of_phil)
		philo[index].fork_right = &table->forks[0];
	philo[index].table = table;
	philo[index].num = index + 1;
}

// inits and sets philo (+mutex)
int	create_philo(t_philo *philo, t_table *table, unsigned int index)
{
	init_philo_zero(philo, index);
	set_philo(philo, table, index);
	philo[index].state_lock = &table->state_locks[index];
	return (0);
}

// sets up all philos
int	init_philo(t_table *table, t_philo *philo)
{
	unsigned int	index;

	index = 0;
	while (index < table->num_of_phil && table->all_alive)
	{
		if (create_philo(philo, table, index++))
		{
			destroy_philos(philo, index);
			return (1);
		}
	}
	if (!table->all_alive)
	{
		destroy_philos(philo, index);
		return (1);
	}
	return (0);
}
