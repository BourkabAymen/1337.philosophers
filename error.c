/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourkab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:38:19 by abourkab          #+#    #+#             */
/*   Updated: 2023/02/20 20:38:24 by abourkab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * @brief free and display the error represented by a macro.
 * 1 : If the second argument is NULL 
 * this function displays the error message
 * 2 : If the second argument is not NULL
 * this function frees the table structer
 * this function displays the error message
 * @param table
 */
void	*error_msg_null(char *str, t_table *table)
{
	if (table)
		free_table(table);
	printf("%s", str);
	return (NULL);
}
