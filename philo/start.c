/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:46:40 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/10 12:28:09 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eats(t_philo *philo)
{
	t_state	*state;

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
	pthread_mutex_lock(&(state->ate));
	(philo->ate)++;
	pthread_mutex_unlock(&(state->ate));
	pthread_mutex_unlock(&(state->forks[philo->l_fork]));
	pthread_mutex_unlock(&(state->forks[philo->r_fork]));
}

void	*routine(void *philosopher)
{
	t_philo	*philo;
	t_state	*state;

	philo = (t_philo *)philosopher;
	state = philo->state;
	if (philo->id % 2)
		usleep(15000);
	subroutine(philo, state);
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
	pthread_mutex_destroy(&(state->death));
}

void	check_death(t_state *state, t_philo *p)
{
	int	i;

	while (!(state->all_ate))
	{
		i = -1;
		while (++i < state->philo_amount && !(state->dead))
		{
			check_death_loop(state, p, &i);
		}
		if (state->dead)
			break ;
		i = 0;
		pthread_mutex_lock(&(state->ate));
		while (state->num_eat != -1 && i < state->philo_amount && \
			p[i].ate >= state->num_eat)
			i++;
		pthread_mutex_lock(&(state->all_ate_m));
		if (i == state->philo_amount)
			state->all_ate = 1;
		pthread_mutex_unlock(&(state->all_ate_m));
		pthread_mutex_unlock(&(state->ate));
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
		philos[i].last_meal = timestamp();
		if (pthread_create(&(philos[i].thread_id), NULL, routine, &(philos[i])))
			return (1);
		i++;
	}
	check_death(state, state->philos);
	finish(state);
	return (0);
}
