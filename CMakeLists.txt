cmake_minimum_required(VERSION 3.17)
project(philosophers C)
set(CMAKE_C_STANDARD 11)

include_directories(lib philo_one/includes)

FILE(GLOB LIB lib/*.c)

set(PHILO_ONE
        philo_one/main.c
        philo_one/classes/table/table_constructors.c
        philo_one/classes/philosopher/philosopher_constructors.c
        )

add_executable(philosophers
        ${LIB}
        ${PHILO_ONE}
        )
