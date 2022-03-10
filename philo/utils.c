/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:52:03 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/10 01:58:14 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	print_message(t_state *state, int id, int action)
{
	long long	ts;

	pthread_mutex_lock(&(state->write));
	ts = timestamp() - state->start;
	if (!(state->dead))
	{
		if (action == FORK)
			printf("%lli Philosopher %i has taken a fork.\n", ts, id + 1);
		else if (action == EAT)
			printf("%lli Philosopher %i is eating.\n", ts, id + 1);
		else if (action == SLEEP)
			printf("%lli Philosopher %i is sleeping.\n", ts, id + 1);
		else if (action == THINK)
			printf("%lli Philosopher %i is thinking.\n", ts, id + 1);
		else if (action == DEAD)
			printf("%lli Philosopher %i died.\n", ts, id + 1);
		pthread_mutex_unlock(&(state->write));
	}
	return ;
}

void	schleep(long long time, t_state *state)
{
	long long	i;

	i = timestamp();
	while (!(state->dead))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}
