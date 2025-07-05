/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@frnki.dev>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/02/25 16:42:42 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// lock fork_left before locking fork_right
int	pick_left_first(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->alive_lock);
	if (!philo->table->all_alive)
	{
		pthread_mutex_unlock(&philo->table->alive_lock);
		pthread_mutex_unlock(philo->fork_left);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->alive_lock);
	pthread_mutex_lock(philo->fork_right);
	print_status(philo, "has taken a fork");
	return (0);
}

// lock fork_right before locking fork_left
int	pick_right_first(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->alive_lock);
	if (!philo->table->all_alive)
	{
		pthread_mutex_unlock(&philo->table->alive_lock);
		pthread_mutex_unlock(philo->fork_right);
		return (1); ;
	}
	pthread_mutex_unlock(&philo->table->alive_lock);
	pthread_mutex_lock(philo->fork_left);
	print_status(philo, "has taken a fork");
	return (0);
}

// lock and unlock mutexes for fork_left, fork_right
int	pick_up_forks(t_philo *philo)
{
	if (philo->num % 2)
		return (pick_left_first(philo));
	else
		return (pick_right_first(philo));
}

// put forks down
void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}
