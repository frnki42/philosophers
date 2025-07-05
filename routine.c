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

// pew pew pew
void	precision_timer(long duration)
{
	long	time;

	time = check_time();
	while ((check_time() - time) < duration)
		usleep(100);
}

// philos 9-5
void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->start_lock);
	philo->table->ready_count++;
	pthread_mutex_unlock(&philo->table->start_lock);
	while (1)
	{
		pthread_mutex_lock(&philo->table->start_lock);
		if (philo->table->start)
		{
			pthread_mutex_unlock(&philo->table->start_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->start_lock);
		usleep(100);
	}
	pthread_mutex_lock(&philo->meal_lock);
	philo->t_last = check_time();
	pthread_mutex_unlock(&philo->meal_lock);
	while (1)
	{
		if (philo->num % 2)
			usleep(100);
		pthread_mutex_lock(&philo->table->alive_lock);
		if (!philo->table->all_alive)
		{
			pthread_mutex_unlock(&philo->table->alive_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->alive_lock);
		if (pick_up_forks(philo))
			break ;
		pthread_mutex_lock(&philo->meal_lock);
		philo->t_last = check_time();
		print_status(philo, "is eating");
		pthread_mutex_unlock(&philo->meal_lock);
		precision_timer(philo->table->t_eat);
		pthread_mutex_lock(&philo->meal_lock);
		philo->ate++;
		pthread_mutex_unlock(&philo->meal_lock);
		put_down_forks(philo);
		print_status(philo, "is sleeping");
		precision_timer(philo->table->t_sleep);
		print_status(philo, "is thinking");
		usleep(1000);
	}
	return (NULL);
}
