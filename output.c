/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourkab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:39:58 by abourkab          #+#    #+#             */
/*   Updated: 2023/02/20 20:40:02 by abourkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*parse_status(t_state status);
static char	*parse_format_pretty(t_state status);

/**
 * @brief This function display the messages that appear in the screen
 */
void	log_status(t_philo *philo, t_state status)
{
	if (has_dinner_finish(philo->table) == true)
		return ;
	pthread_mutex_lock(&philo->table->log_lock);
	printf("%i %ld %s\n", get_time_ms(philo->table->start_dining),
		philo->id + 1, parse_status(status));
	pthread_mutex_unlock(&philo->table->log_lock);
}

/**
 * @brief Translate the state from enum, to this description
 * @param status
 * @return char*
 */
static char	*parse_status(t_state status)
{
	if (status == S_EATING)
		return ("is eating");
	else if (status == S_LEFT_FORK || status == S_RIGHT_FORK)
		return ("has taken a fork");
	else if (status == S_SLEEPING)
		return ("is sleeping");
	else if (status == S_THINKING)
		return ("is thinking");
	else if (status == S_DEAD)
		return ("died");
	else
		return ("");
}
