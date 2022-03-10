/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:31:36 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/10 12:02:06 by kpucylo          ###   ########.fr       */
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
	if (pthread_mutex_init(&(state->death), NULL))
		return (1);
	if (pthread_mutex_init(&(state->ate), NULL))
		return (1);
	if (pthread_mutex_init(&(state->all_ate_m), NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_state *state)
{
	int	i;

	i = 0;
	state->philos = malloc(sizeof(t_philo) * state->philo_amount);
	if (!(state->philos))
		return (1);
	while (i < state->philo_amount)
	{
		state->philos[i].id = i;
		state->philos[i].ate = 0;
		state->philos[i].l_fork = i;
		state->philos[i].r_fork = (i + 1) % state->philo_amount;
		state->philos[i].last_meal = 0;
		state->philos[i].state = state;
		i++;
	}
	return (0);
}

void	*one_philosopher_routine(void *state_void)
{
	t_state	*state;

	state = (t_state *)state_void;
	printf("%d Philosopher 1 died.\n", state->time_to_die);
	return (NULL);
}

int	one_philosopher(t_state *state)
{
	state->philos = malloc(sizeof(t_philo) * state->philo_amount);
	if (!(state->philos))
		return (3);
	state->forks = malloc(sizeof(t_philo) * state->philo_amount);
	state->philos[0].state = state;
	if (!(state->forks))
		return (3);
	pthread_create(&(state->philos[0].thread_id), NULL, \
		one_philosopher_routine, state);
	return (4);
}

int	init_all(t_state *state, char **argv, int argc)
{
	if (check_arguments(argc, argv))
		return (1);
	state->philo_amount = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	state->dead = 0;
	state->all_ate = 0;
	state->num_eat = -1;
	if (state->philo_amount == 1)
		return (one_philosopher(state));
	if (argc == 6)
		state->num_eat = ft_atoi(argv[5]);
	if (state->time_to_die < 0 || state->time_to_eat < 0 || \
		state->time_to_sleep < 0 || (state->num_eat <= 0 && argc == 6))
		return (1);
	if (init_mutex(state))
		return (2);
	if (init_philosophers(state))
		return (3);
	return (0);
}
