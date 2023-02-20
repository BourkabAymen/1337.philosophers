/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourkab <abourkab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:40:47 by abourkab          #+#    #+#             */
/*   Updated: 2023/02/20 21:06:42 by abourkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * @brief datetime_now 
 * This function returns the time of the day by using a defined function 
 * called gettimeofday with a time origin January 1, 1970
 * The returned value will be stored in start_dining that will be considered
 * as our time origin in the rest of the project and that represents the 
 * start of the dinning
 * @return int
 */
int	datetime_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @brief get_time_ms 
 * This function returns the actual time by using start_dining as an origin of 
 * time 
 * @return int
 */
int	get_time_ms(int start_dining)
{
	return (datetime_now() - start_dining);
}

/**
 * @brief thread_sleep 
 * This function let the thread wait for a certain duration
 * This duration may be time_to_eat or time_to_sleep
 * but at first we have to check if one of the philosophers is dead
 * by calling this has_dinner_finish
 * @return int
 */
void	thread_sleep(t_table *table, time_t duration)
{
	time_t	time_wake_up;

	time_wake_up = datetime_now() + duration;
	while (datetime_now() < time_wake_up)
	{
		if (has_dinner_finish(table))
			break ;
		usleep(100);
	}
}

/**
 * @brief thread_sleep 
 * This function gives an approximate value to the thinking for each philosopher
 * @return int
 */
long	handle_thinking_time(t_philo *philo)
{
	long	time_to_think;

	pthread_mutex_lock(&philo->general_meal_lock);
	time_to_think = (philo->table->time_to_die - (datetime_now()
				- philo->last_meal) - philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->general_meal_lock);
	if (time_to_think > 500)
		return (200);
	else
		return (1);
}
