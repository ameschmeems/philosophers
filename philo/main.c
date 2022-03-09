/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:04:37 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/09 20:06:03 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc < 5 || argc > 6)
		return (throw_error("Wrong number of arguments"));
	if (init(&state, argv, argc))
		return (throw_error("Init failed"));
	return (0);
}
