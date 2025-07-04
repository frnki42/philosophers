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

// checks if someone was hungry for too long
static int	philo_has_died(t_philo *philo)
{
	long	time_now;
	long	time_last_meal;

	time_now = check_time();
	pthread_mutex_lock(&philo->meal_lock);
	time_last_meal = time_now - philo->t_last;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_last_meal > philo->table->t_die)
		return (1);
	return (0);
}

// calls 911 reaaally quick, trust me.
static void	report_death(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->msg_lock);
	pthread_mutex_lock(&table->alive_lock);
	if (table->all_alive)
	{
		table->all_alive = 0;
		printf("%ld %d died\n", check_time() - table->t_start, philo->num);
	}
	pthread_mutex_unlock(&table->alive_lock);
	pthread_mutex_unlock(&table->msg_lock);
}

// weird looking dude, looking at everyone from far
void	*monitor(void *arg)
{
	unsigned int	i;
	t_table		*table;
	t_philo		*philo;

	philo = (t_philo *)arg;
	table = philo[0].table;
	while (1)
	{
		i = -1;
		while (++i < table->num_of_phil)
		{
			if (philo_has_died(&philo[i]))
				return (report_death(&philo[i]), NULL);
		}
		if (table->must_eat > 0 && all_philos_ate(table, philo))
		{
			pthread_mutex_lock(&table->alive_lock);
			table->all_alive = 0;
			pthread_mutex_unlock(&table->alive_lock);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
