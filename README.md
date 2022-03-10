# philosophers
An implementation of Dijkstra's famous dining philosophers problem, using threads in C.

## Details
This project was made for unix systems, using pthreads and mutexes. Compile with make, and run with "./philo *number of philosophers* *time_to_die*
*time_to_eat* *time_to_sleep* [*number_of_times_each_philosopher_must_eat*]".
* number_of_philosophers - the number of philosophers sitting at the table.
* time_to_die (in milliseconds) - the amount of time after which a philosopher dies of starvation.
* time_to_eat (in milliseconds) - the amount of time it takes a philosopher to eat.
* time_to_sleep (in milliseconds) - the amount of time a philosopher sleeps.
* number_of_times_each_philosopher_must_eat (optional) - the program ends after every philosopher ate at least this many times.

## Main concepts learned:
* Threads
* Mutexes
* Data races, and how to avoid them
