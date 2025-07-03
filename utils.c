/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@frnki.dev>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 04:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/05/21 16:20:42 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// prints time + message and handles msg_lock
void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->msg_lock);
	if (philo->table->all_alive)
	{
		timestamp = check_time() - philo->table->t_start;
		printf("%li %i %s\n", timestamp, philo->num, msg);
	}
	pthread_mutex_unlock(&philo->table->msg_lock);
}

// converts string to long
long	ft_atolong(char *str)
{
	int		i;
	int		sign;
	long	tmp;

	i = 0;
	sign = 1;
	tmp = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		tmp = tmp * 10 + (str[i++] - '0');
	return (tmp * sign);
}

// destroys everything on the table, then the table itself
void	destroy_table(t_table *table)
{
	unsigned int	i;

	i = -1;
	while (++i < table->num_of_phil)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->state_locks[i]);
	}
	if (table->forks)
		free(table->forks);
	if (table->state_locks)
		free(table->state_locks);
	pthread_mutex_destroy(&table->msg_lock);
	pthread_mutex_destroy(&table->alive_lock);
}

// frees and destroys all state_lock
void	destroy_philos(t_philo *philo, unsigned int num_of_phil)
{
	unsigned int	i;

	i = -1;
	while (++i < num_of_phil)
	{
		if (philo[i].state_lock)
		{
			pthread_mutex_destroy(philo[i].state_lock);
			free(philo[i].state_lock);
			philo[i].state_lock = NULL;
		}
	}
}

// starts a funny starving adventure
void	solo_adventure(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(&philo->table->msg_lock);
	timestamp = check_time() - philo->table->t_start;
	printf("%li %i has taken a fork (left)\n", timestamp, philo->num);
	pthread_mutex_unlock(&philo->table->msg_lock);
	usleep(philo->table->t_die * 1000);
	pthread_mutex_lock(&philo->table->msg_lock);
	timestamp = check_time() - philo->table->t_start;
	printf("%li %i died\n", timestamp, philo->num);
	pthread_mutex_unlock(&philo->table->msg_lock);
}
