# Philosophers
### <i>I never thought philosophy would be so deadly </i>

* Eat, Sleep, Spaghetti, repeat.
* This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.
* In this project, you will learn the basics of threading a process.
* You will see how to create threads and you will discover mutexes.

<br>

# Examples

## Compile

`make`

## Execute

`./philo philo_num die_ms eat_ms sleep_ms [must_eat]`
- `philo_num` 
  - The number of philosophers and also the number of forks.
- `die_ms`
  - time of life
  - If a philosopher didn’t start eating die_ms milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- `eat_ms`
  - time to eat 
  - The time it takes for a philosopher to eat. During that time, they will need to hold two forks of left and right.
- `sleep_ms`
  - time to sleep
  - The time a philosopher will spend sleeping.
- `must_eat`
  - optional parameter
  - If all philosophers have eaten at least `must_eat` times, the simulation stops.
  - If not specified, the simulation stops when a philosopher dies. 
