/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:25:38 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/10 02:14:08 by kpucylo          ###   ########.fr       */
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
	if (start(&state))
		return (throw_error("Failed to create threads"));
	return (0);
}
