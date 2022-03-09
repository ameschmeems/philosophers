/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:11:17 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/09 20:39:58 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_message(int state, t_philo *philo)
{
	uint64_t	ts;
	static int	done = 0;

	if (!done)
	{
		pthread_mutex_lock(&philo->state->write);
		ts = get_time() - philo->state->start;
		if (state == EAT)
			printf("%llu Philosopher %d is eating.\n", ts, philo->position);
		else if (state == SLEEP)
			printf("%llu Philosopher %d is sleeping.\n", ts, philo->position);
		else if (state == FORK)
			printf("%llu Philosopher %d has taken a fork.\n", ts, \
				philo->position);
		else if (state == THINK)
			printf("%llu Philosopher %d is thinking.\n", ts, philo->position);
		else if (state == DEAD)
		{
			printf("%llu Philosopher %d died.\n", ts, philo->position);
			done = 1;
		}
		pthread_mutex_unlock(&philo->state->write);
	}
}
