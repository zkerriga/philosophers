cmake_minimum_required(VERSION 3.17)
project(philosophers C)
set(CMAKE_C_STANDARD 11)

include_directories(lib philo_three/includes)
#include_directories(lib philo_two/includes)
#include_directories(lib philo_one/includes)

FILE(GLOB LIB lib/*.c)

set(PHILO_ONE
        philo_one/main.c
        philo_one/classes/table/table_constructors.c
        philo_one/classes/table/table_start_simulation.c

        philo_one/classes/philosopher/philosopher_constructors.c
        philo_one/classes/philosopher/philosopher_actions.c
        philo_one/classes/philosopher/philosopher_lifetime.c
        philo_one/classes/philosopher/philosopher_say.c
        )

set(PHILO_TWO
        philo_two/main.c
        philo_two/classes/table/table_constructors.c
        philo_two/classes/table/table_start_simulation.c

        philo_two/classes/philosopher/philosopher_constructors.c
        philo_two/classes/philosopher/philosopher_actions.c
        philo_two/classes/philosopher/philosopher_lifetime.c
        philo_two/classes/philosopher/philosopher_say.c
        )

set(PHILO_THREE
        philo_three/main.c
        philo_three/classes/table/table_constructors.c
        philo_three/classes/table/table_start_simulation.c

        philo_three/classes/philosopher/philosopher_constructors.c
        philo_three/classes/philosopher/philosopher_actions.c
        philo_three/classes/philosopher/philosopher_lifetime.c
        philo_three/classes/philosopher/philosopher_say.c
        )

add_executable(philosophers
        ${LIB}
        ${PHILO_THREE}
        )
