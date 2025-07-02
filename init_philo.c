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

void	init_philo_zero(t_philo *philo, unsigned int index)
{
	philo[index].fork_left = NULL;
	philo[index].fork_right = NULL;
	philo[index].table = NULL;
	philo[index].ate = 0;
	philo[index].num = 0;
	philo[index].thread = 0;
	philo[index].t_last = 0;
}

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

void	create_philo(t_philo *philo, t_table *table, unsigned int index)
{
	init_philo_zero(philo, index);
	set_philo(philo, table, index);
}

void	init_philo(t_table *table, t_philo *philo)
{
	unsigned int	index;

	index = 0;
	while (index < table->num_of_phil && table->all_alive)
		create_philo(philo, table, index++);
}
