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
		usleep(100);
}

// philos 9-5
void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->table->alive_lock);
		if (!philo->table->all_alive)
		{
			pthread_mutex_unlock(&philo->table->alive_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->alive_lock);
		philo->t_last = check_time();
		pick_up_forks(philo);
		print_status(philo, "is eating");
		philo->t_last = check_time();
		precision_timer(philo->t_eat);
		philo->ate++;
		put_down_forks(philo);
		print_status(philo, "is sleeping");
		precision_timer(philo->t_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
