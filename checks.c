/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/04/20 16:20:42 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// checks if int is in ascii range for digits
static int	check_char(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

// check if string is valid (digit with only one sign if any)
static int	check_str(char *str)
{
	if (!*str)
		return (printf("# empty argument\n"), 1);
	if (*str == '+' || *str == '-' || check_char(*str))
		str++;
	while (*str)
	{
		if (!check_char(*str++))
			return (printf("# invalid argument\n"), 1);
	}
	return (0);
}

//checks the amount of arguments and each argument
int	check_args(int argc, char **argv)
{
	int	errors;

	if (argc < 5 || argc > 6)
	{
		printf("# wrong amount of arguments\n");
		return (1);
	}
	errors = 0;
	while (--argc)
		errors += check_str(argv[argc]);
	if (errors)
		return (1);
	return (0);
}

// where is my car dude?
long	check_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (printf("# gettimeofday() failed.\n"), -1);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}
