/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:00:10 by kpucylo           #+#    #+#             */
/*   Updated: 2022/03/10 05:18:55 by kpucylo          ###   ########.fr       */
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

enum
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
};

struct	s_state;

typedef struct s_philo
{
	int				id;
	int				ate;
	int				l_fork;
	int				r_fork;
	long long		last_meal;
	struct s_state	*state;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_state
{
	int				philo_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	int				dead;
	int				all_ate;
	long long		start;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	t_philo			*philos;
}	t_state;

//init
int			init_all(t_state *state, char **argv, int argc);

//errors
int			throw_error(char *str);
int			check_arguments(int argc, char **argv);

//program
int			start(t_state *state);
void		print_message(t_state *state, int id, int action);

//utils
int			ft_atoi(const char *nptr);
int			ft_isdigit(int c);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void		schleep(long long time, t_state *state);

#endif