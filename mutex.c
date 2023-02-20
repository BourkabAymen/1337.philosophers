/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourkab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:39:45 by abourkab          #+#    #+#             */
/*   Updated: 2023/02/20 20:39:51 by abourkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * @brief 
 * 1 This function initialize the last_meal variable for each philosopher
 * which is start_dining in code
 * 2 This function set a value to the last_meal variable for each philosopher
 * after eating
 */
void	set_last_meal_value(t_philo *philo, time_t value)
{
	pthread_mutex_lock(&philo->general_meal_lock);
	philo->last_meal = value;
	pthread_mutex_unlock(&philo->general_meal_lock);
}

/**
 * @brief 
 * This function sets False or true to the dinner_end variable
 */
void	set_dinner_end_value(t_table *table, bool value)
{
	pthread_mutex_lock(&table->dinner_end_lock);
	table->dinner_end = value;
	pthread_mutex_unlock(&table->dinner_end_lock);
}

/**
 * @brief This function increments the number of meals 
 * when each philosopher has finished its meal
 */
void	increment_number_of_eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->general_meal_lock);
	philo->nbr_meals_done++;
	pthread_mutex_unlock(&philo->general_meal_lock);
}

/**
 * @brief This function if dinner_end is True which means that one of 
 * the philosophers is died
 */
bool	has_dinner_finish(t_table *table)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&table->dinner_end_lock);
	if (table->dinner_end == true)
		result = true;
	pthread_mutex_unlock(&table->dinner_end_lock);
	return (result);
}
