/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:00:10 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/09 20:42:50 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

enum	e_state
{
	EAT,
	SLEEP,
	FORK,
	THINK,
	DEAD
};

struct	s_state;

typedef struct s_philo
{
	int				is_eating;
	int				position;
	int				l_fork;
	int				r_fork;
	int				eat_count;
	uint64_t		limit;
	uint64_t		last_eat;
	struct s_state	*state;
}	t_philo;

typedef struct s_state
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times;
	uint64_t		start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}	t_state;

//init
int			init(t_state *state, char **argv, int argc);

//messages
void		display_message(int state, t_philo *philo);

//utils
int			ft_atoi(const char *nptr);
uint64_t	get_time(void);

//errors
int			throw_error(char *str);

#endif