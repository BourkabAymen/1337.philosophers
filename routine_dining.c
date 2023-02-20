/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_dining.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourkab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:40:22 by abourkab          #+#    #+#             */
/*   Updated: 2023/02/20 20:40:26 by abourkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*lonely_philo(t_philo *philo);
static void	keep_thinking(t_philo *philo, bool log);
static void	keep_eating(t_philo *philo);
static void	keep_sleeping(t_philo *philo);

/**
 * @brief The typecasting is mandatory because pthread_create should have as one
 * of there arguments a function that its argument is pointing to void
 * 1 set the start_dining value to the last_meal variable as the first value
 * by calling set_last_meal_value
 * 2 we call lonely_philo if nbr_philo == 1
 * 3 to avoid the datarace we have used this if condition philo->id % 2 != 0 
 * by calling keep_thinking
 * @param philo
 */
void	*dining_routines(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->time_must_eat == 0)
		return (NULL);
	set_last_meal_value(philo, philo->table->start_dining);
	if (philo->table->nbr_philo == 1)
		return (lonely_philo(philo));
	if (philo->id % 2 != 0)
		keep_thinking(philo, false);
	while (has_dinner_finish(philo->table) == false)
	{
		keep_eating(philo);
		keep_sleeping(philo);
		keep_thinking(philo, true);
	}
	return (NULL);
}

/**
 * @brief Responsible to keep the philo sleeping.
 * Log the status and sleep the thread
 * @param philo
 */
static void	keep_sleeping(t_philo *philo)
{
	log_status(philo, S_SLEEPING);
	thread_sleep(philo->table, philo->table->time_to_sleep);
}

/**
 * @brief Responsible to Eating process.
 * This will: 1) Lock forks, 2) Log this action, 3) Log eating routine.
 * 4) Update last meal, 5) Sleep until time to eat, 6)Update the number 
 * of eats for each philo after checking that no philosopher is dead
 */
static void	keep_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_lock[philo->fork[F_LEFT]]);
	log_status(philo, S_LEFT_FORK);
	pthread_mutex_lock(&philo->table->fork_lock[philo->fork[F_RIGHT]]);
	log_status(philo, S_RIGHT_FORK);
	log_status(philo, S_EATING);
	set_last_meal_value(philo, datetime_now());
	thread_sleep(philo->table, philo->table->time_to_eat);
	if (has_dinner_finish(philo->table) == false)
		increment_number_of_eats(philo);
	pthread_mutex_unlock(&philo->table->fork_lock[philo->fork[F_RIGHT]]);
	pthread_mutex_unlock(&philo->table->fork_lock[philo->fork[F_LEFT]]);
}

/**
 * @brief Handle the think function.
 * 1 : The first execution is when log = false
 * which means that the philosopher concerned has not started eating.
 * so in this case we we should not display "is thinking"
 * 2 : Th second execution is when log = true
 * which means that the philosopher concerned has started eating.
 * so in this case we we should display "is thinking"
 * @param philo Philo structure
 */
static void	keep_thinking(t_philo *philo, bool log)
{
	time_t	time_thinking;

	time_thinking = handle_thinking_time(philo);
	if (log == true)
		log_status(philo, S_THINKING);
	thread_sleep(philo->table, time_thinking);
}

/**
 * @brief Handle single Philo. Grab the fork and wait until die.
 * Philos are not allowed to eat with just one fork
 * @param philo
 */
static void	*lonely_philo(t_philo *philo)
{
	log_status(philo, S_LEFT_FORK);
	thread_sleep(philo->table, philo->table->time_to_die);
	log_status(philo, S_DEAD);
	return (NULL);
}
