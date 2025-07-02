/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/05/21 16:42:42 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// set current time to t_last and increment ate + usleep(t_eat)
static void	eat_spaghetti(t_philo *philo)
{
	long	i;
	long	timestamp;

	philo->t_last = check_time();
	philo->ate++;
	if (philo->table->all_alive)
	{
		pthread_mutex_lock(&philo->table->msg_lock);
		timestamp = check_time() - philo->table->t_start;
		printf("%li %i is eating\n", timestamp, philo->num);
		pthread_mutex_unlock(&philo->table->msg_lock);
		i = 0;
		while (philo->table->all_alive && i++ < 100)
			usleep(philo->table->t_eat * 10);
	}
}

// usleep(t_sleep)
static void	take_a_nap(t_philo *philo)
{
	unsigned int	i;
	long			timestamp;

	pthread_mutex_lock(&philo->table->msg_lock);
	timestamp = check_time() - philo->table->t_start;
	if (philo->table->all_alive)
		printf("%li %i is sleeping\n", timestamp, philo->num);
	pthread_mutex_unlock(&philo->table->msg_lock);
	i = 0;
	while (philo->table->all_alive && i++ < 100)
		usleep(philo->table->t_sleep * 10);
}

// face the harsh reality of life
static void	reality_check(t_philo *philo)
{
	long	timestamp;

	if ((check_time() - philo->t_last) >= philo->table->t_die)
	{
		pthread_mutex_lock(&philo->table->alive_lock);
		philo->table->all_alive = 0;
		pthread_mutex_unlock(&philo->table->alive_lock);
		pthread_mutex_lock(&philo->table->msg_lock);
		timestamp = check_time() - philo->table->t_start;
		printf("%li %i died\n", timestamp, philo->num);
		pthread_mutex_unlock(&philo->table->msg_lock);
	}
}

// find your inner zen
static void	think_about_life(t_philo *philo)
{
	long	timestamp;

	if (philo->table->all_alive)
	{
		pthread_mutex_lock(&philo->table->msg_lock);
		timestamp = check_time() - philo->table->t_start;
		printf("%li %i is thinking\n", timestamp, philo->num);
		pthread_mutex_unlock(&philo->table->msg_lock);
		reality_check(philo);
	}
}

// make the thread do some work
void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->t_last = check_time();
	if (philo->table->num_of_phil == 1)
		return (solo_adventure(philo), arg);
	while (philo->ate < philo->table->must_eat && philo->table->all_alive)
	{
		if (philo->table->all_alive)
			pick_up_forks(philo);
		else
			break ;
		if (philo->table->all_alive)
			eat_spaghetti(philo);
		put_down_forks(philo);
		if (philo->table->all_alive)
			take_a_nap(philo);
		else
			break ;
		if (philo->table->all_alive)
			think_about_life(philo);
	}
	return (arg);
}
