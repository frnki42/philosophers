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

static void	precision_timer(long duration)
{
	long	timestamp;

	timestamp = check_time();
	while ((check_time() - timestamp) < duration)
		usleep(1000);
}

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

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 0)
		usleep(1000);
	while (philo->table->all_alive)
	{
		eat_spaghetti(philo);
		print_status(philo, "is sleeping");
		precision_timer(philo->table->t_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
