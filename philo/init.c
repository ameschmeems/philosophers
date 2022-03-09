/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:33:59 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/09 20:47:57 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutexes(t_state *state)
{
	int	i;

	pthread_mutex_init(&state->write, NULL);
	state->forks = malloc(sizeof(pthread_mutex_t) * \
		state->number_of_philosophers);
	if (!state->forks)
		return (1);
	i = 0;
	while (i < state->number_of_philosophers)
	{
		pthread_mutex_init(&state->forks[i], NULL);
		i++;
	}
	return (0);
}

void	init_philos(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		state->philos[i].is_eating = 0;
		state->philos[i].position = i;
		state->philos[i].l_fork = i;
		state->philos[i].r_fork = (i + 1) % state->number_of_philosophers;
		state->philos[i].state = state;
		i++;
	}
}

int	init(t_state *state, char **argv, int argc)
{
	state->number_of_philosophers = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		state->number_of_times = ft_atoi(argv[5]);
	else
		state->number_of_times = 0;
	if (state->number_of_philosophers < 2)
		return (1);
	state->philos = malloc(sizeof(t_philo) * state->number_of_philosophers);
	if (!state->philos)
		return (1);
	init_philos(state);
}
