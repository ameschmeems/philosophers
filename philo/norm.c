/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:17:59 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/10 12:27:34 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	subroutine(t_philo *philo, t_state *state)
{
	while (1)
	{
		philo_eats(philo);
		pthread_mutex_lock(&(state->all_ate_m));
		if (state->all_ate)
		{
			pthread_mutex_unlock(&(state->all_ate_m));
			break ;
		}
		pthread_mutex_unlock(&(state->all_ate_m));
		print_message(state, philo->id, SLEEP);
		schleep(state->time_to_sleep, state);
		print_message(state, philo->id, THINK);
		pthread_mutex_lock(&(state->death));
		if (state->dead)
		{
			pthread_mutex_unlock(&(state->death));
			break ;
		}
		pthread_mutex_unlock(&(state->death));
	}
}

void	check_death_loop(t_state *state, t_philo *p, int *i)
{
	pthread_mutex_lock(&(state->meal_check));
	if (time_diff(p[(*i)].last_meal, timestamp()) > state->time_to_die)
	{
		print_message(state, (*i), DEAD);
		pthread_mutex_lock(&(state->death));
		state->dead = 1;
		pthread_mutex_unlock(&(state->death));
	}
	pthread_mutex_unlock(&(state->meal_check));
	usleep(100);
}
