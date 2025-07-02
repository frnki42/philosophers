/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@frnki.dev>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 04:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/04/24 16:42:20 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	philo_has_died(t_philo *philo)
{
	long	time_now;
	long	time_last_meal;

	time_now = check_time();
	time_last_meal = time_now - philo->t_last;
	if (time_last_meal > philo->table->t_die)
		return (1);
	return (0);
}

static void	report_death(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->msg_lock);
	if (table->all_alive)
	{
		table->all_alive = 0;
		printf("%ld %d died\n", check_time() - table->t_start, philo->num);
	}
	pthread_mutex_unlock(&table->msg_lock);
}

static int	check_each_philo(t_philo *philos)
{
	unsigned int	i;
	t_table		*table;

	table = philos[0].table;
	i = 0;
	while (i < table->num_of_phil)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philo_has_died(&philos[i]))
		{
			pthread_mutex_unlock(philos[i].meal_lock);
			report_death(&philos[i]);
			return (1);
		}
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo *philos;
	t_table	*table;

	philos = (t_philo *)arg;
	table = philos[0].table;
	while (table->all_alive)
	{
		if (check_each_philo(philos))
			break ;
		if (table->must_eat > 0 && all_philos_ate(table, philos))
			break ;
		usleep(1000);
	}
	return (NULL);
}
