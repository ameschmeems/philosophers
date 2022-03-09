/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:31:36 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/09 23:25:47 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_state *state)
{
	int	i;

	i = 0;
	state->forks = malloc(sizeof(pthread_mutex_t) * state->philo_amount);
	if (!state->forks)
		return (1);
	while (i < state->philo_amount)
	{
		if (pthread_mutex_init(&(state->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(state->write), NULL))
		return (1);
	if (pthread_mutex_init(&(state->meal_check), NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_state *state)
{
	int	i;

	i = 0;
	state->philos = malloc(sizeof(t_philo) * state->philo_amount);
	if (!state->philos)
		return (1);
	while (i < state->philo_amount)
	{
		state->philos[i].id = i;
		state->philos[i].ate = 0;
		state->philos[i].l_fork = i;
		state->philos[i].r_fork = (i + 1) % state->philo_amount;
		state->philos[i].last_meal = 0;
		state->philos[i].state = state;
	}
	return (0);
}

int	init_all(t_state *state, char **argv, int argc)
{
	if (check_arguments(argc, argv))
		return (1);
	state->philo_amount = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	state->num_eat = -1;
	if (argc == 6)
		state->num_eat = ft_atoi(argv[5]);
	state->dead = 0;
	state->all_ate = 0;
	if (state->philo_amount < 2 || state->time_to_die < 0 \
		|| state->time_to_eat < 0 || state->time_to_sleep < 0 || \
		state->num_eat <= 0)
		return (1);
	if (init_mutex(state))
		return (2);
	if (init_philosophers(state))
		return (3);
	return (0);
}
