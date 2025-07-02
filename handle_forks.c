/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/02/25 16:42:42 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// lock fork_left before locking fork_right
void	pick_left_first(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(&philo->table->msg_lock);
	timestamp = check_time() - philo->table->t_start;
	if (philo->table->all_alive)
		printf("%li %i has taken a fork (left)\n", timestamp, philo->num);
	pthread_mutex_unlock(&philo->table->msg_lock);
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(&philo->table->msg_lock);
	timestamp = check_time() - philo->table->t_start;
	if (philo->table->all_alive)
		printf("%li %i has taken a fork (right)\n", timestamp, philo->num);
	pthread_mutex_unlock(&philo->table->msg_lock);
}

// lock fork_right before locking fork_left
void	pick_right_first(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(philo->fork_right);
	if (philo->table->all_alive)
	{
		pthread_mutex_lock(&philo->table->msg_lock);
		timestamp = check_time() - philo->table->t_start;
		printf("%li %i has taken a fork (right)\n", timestamp, philo->num);
		pthread_mutex_unlock(&philo->table->msg_lock);
	}
	else
		return ;
	pthread_mutex_lock(philo->fork_left);
	if (philo->table->all_alive)
	{
		pthread_mutex_lock(&philo->table->msg_lock);
		timestamp = check_time() - philo->table->t_start;
		printf("%li %i has taken a fork (left)\n", timestamp, philo->num);
	}
	pthread_mutex_unlock(&philo->table->msg_lock);
}

// lock and unlock mutexes for fork_left, fork_right
void	pick_up_forks(t_philo *philo)
{
	if (philo->num % 2)
		pick_left_first(philo);
	else
		pick_right_first(philo);
}

// put forks down
void	put_down_forks(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_lock(&philo->table->msg_lock);
	timestamp = check_time() - philo->table->t_start;
	if (philo->table->all_alive)
		printf("%li %i put a fork down (left)\n", timestamp, philo->num);
	pthread_mutex_unlock(&philo->table->msg_lock);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_lock(&philo->table->msg_lock);
	timestamp = check_time() - philo->table->t_start;
	if (philo->table->all_alive)
		printf("%li %i put a fork down (right)\n", timestamp, philo->num);
	pthread_mutex_unlock(&philo->table->msg_lock);
}
