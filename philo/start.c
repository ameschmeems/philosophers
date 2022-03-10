/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:46:40 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/10 02:00:12 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eats(t_philo *philo)
{
	t_state *state;

	state = philo->state;
	pthread_mutex_lock(&(state->forks[philo->l_fork]));
	print_message(state, philo->id, FORK);
	pthread_mutex_lock(&(state->forks[philo->r_fork]));
	print_message(state, philo->id, FORK);
	pthread_mutex_lock(&(state->meal_check));
	print_message(state, philo->id, EAT);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&(state->meal_check));
	schleep(state->time_to_eat, state);
	(philo->ate)++;
	pthread_mutex_unlock(&(state->forks[philo->l_fork]));
	pthread_mutex_unlock(&(state->forks[philo->r_fork]));
}

void	*routine(void *philosopher)
{
	int		i;
	t_philo	*philo;
	t_state	*state;

	i = 0;
	philo = (t_philo *)philosopher;
	state = philo->state;
	if (philo->id % 2)
		usleep(15000);
	while (!(state->dead))
	{
		philo_eats(philo);
		if (state->all_ate)
			break ;
		print_message(state, philo->id, SLEEP);
		schleep(state->time_to_sleep, state);
		print_message(state, philo->id, THINK);
		i++;
	}
	return (NULL);
}

void	finish(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philo_amount)
	{
		pthread_join(state->philos[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < state->philo_amount)
	{
		pthread_mutex_destroy(&(state->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(state->write));
	pthread_mutex_destroy(&(state->meal_check));
}

void	check_death(t_state *state, t_philo *p)
{
	int	i;

	while (!(state->all_ate))
	{
		i = 0;
		while (i < state->philo_amount && !(state->dead))
		{
			pthread_mutex_lock(&(state->meal_check));
			if (time_diff(p[i].last_meal, timestamp()) > state->time_to_die)
			{
				print_message(state, i, DEAD);
				state->dead = 1;
			}
			pthread_mutex_unlock(&(state->meal_check));
			usleep(100);
		}
		if (state->dead)
			break ;
		i = 0;
		while (state->num_eat != -1 && i < state->philo_amount && \
			p[i].ate >= state->num_eat)
			i++;
		if (i == state->philo_amount)
			state->all_ate = 1;
	}
}

int	start(t_state *state)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = state->philos;
	state->start = timestamp();
	while (i < state->philo_amount)
	{
		if (pthread_create(&(philos[i].thread_id), NULL, routine, &(philos[i])))
			return (1);
		philos[i].last_meal = timestamp();
		i++;
	}
	check_death(state, state->philos);
	finish(state);
	return (0);
}
