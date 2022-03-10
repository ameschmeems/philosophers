/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:25:38 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/10 11:51:10 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_state	state;
	int		error_check;

	if (argc < 5 || argc > 6)
		return (throw_error("Wrong number of arguments"));
	error_check = init_all(&state, argv, argc);
	if (error_check == 1)
		return (throw_error("Invalid arguments"));
	else if (error_check == 2)
		return (throw_error("Failed to initialize mutexes"));
	else if (error_check == 3)
		return (throw_error("Failed to allocate memory"));
	if (error_check == 4)
		pthread_join(state.philos[0].thread_id, NULL);
	else if (start(&state))
		return (throw_error("Failed to create threads"));
	free(state.forks);
	free(state.philos);
	return (0);
}
