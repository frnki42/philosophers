/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@frnki.dev>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 04:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/05/21 16:42:42 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// ngl, this is the coolest part in this project
void	precision_timer(long duration)
{
	long	timestamp;

	timestamp = check_time();
	while ((check_time() - timestamp) < duration)
		usleep(1000);
}

// fork dispenser
static void	eat_spaghetti(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		print_status(philo, "has taken a fork");
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->t_last = check_time();
	philo->ate++;
	pthread_mutex_unlock(philo->meal_lock);
	precision_timer(philo->table->t_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

// philos 9-5
void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 0)
		usleep(1000);
	while (philo->table->all_alive)
	{
		if (philo->table->must_eat > 0
			&& philo->ate >= philo->table->must_eat)
			break;
		eat_spaghetti(philo);
		print_status(philo, "is sleeping");
		precision_timer(philo->table->t_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
