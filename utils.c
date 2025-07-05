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

// pew pew pew
void	precision_timer(long duration)
{
	long	time;

	time = check_time();
	while ((check_time() - time) < duration)
		usleep(100);
}

// prints time + message and handles msg_lock
void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->msg_lock);
	pthread_mutex_lock(&philo->table->alive_lock);
	if (philo->table->all_alive)
	{
		timestamp = check_time() - philo->table->t_start;
		printf("%li %i %s\n", timestamp, philo->num, msg);
	}
	pthread_mutex_unlock(&philo->table->alive_lock);
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
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->msg_lock);
	pthread_mutex_destroy(&table->alive_lock);
	if (table->philos)
	{
		i = -1;
		while (++i < table->num_of_phil)
			pthread_mutex_destroy(&table->philos[i].meal_lock);
	}
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	if (table)
		free(table);
}

// starts a funny starving adventure
void	solo_adventure(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->fork_left);
	time = check_time() - philo->table->t_start;
	printf("%li %i has taken a fork\n", time, philo->num);
	usleep(philo->table->t_die * 1000);
	time = check_time() - philo->table->t_start;
	printf("%li %i died\n", time, philo->num);
	pthread_mutex_unlock(philo->fork_left);
}
