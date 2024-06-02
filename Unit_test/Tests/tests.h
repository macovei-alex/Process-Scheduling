#pragma once

#include "../../Implementation/algorithms.h"
#include <iomanip>

// Macrocomanda implementata dupa exemplul din fisierul cu cerinta temei
#define TEST(file, i, algorithm, expected) \
{ \
	utility::read_process_queue(queue, file); \
	algorithm(queue, execution, total_wait_time, process_count); \
	if (execution == expected) \
		std::cout << "Test case " << std::setw(2) << i << " passed!" << std::endl; \
	else \
		std::cout << "Test case " << std::setw(2) << i << " failed!" << std::endl; \
	utility::reset_execution_data(execution, total_wait_time, process_count); \
}

// Aceasta macrocomanda este necesara deoarece algoritmul algorithms::Multi_level_Queue_Scheduling primeste un parametru in plus fata de ceilalti algoritmi. Algoritmii se afla implementati in fisierul "Implementation/algorithms.cpp"
#define TEST_MULTI_LEVEL(file, i, algorithm, expected) \
{ \
	utility::read_process_queue(queue, file); \
	algorithm(queue, execution, total_wait_time, process_count, algorithms::functions); \
	if (execution == expected) \
		std::cout << "Test case " << std::setw(2) << i << " passed!" << std::endl; \
	else \
		std::cout << "Test case " << std::setw(2) << i << " failed!" << std::endl; \
	utility::reset_execution_data(execution, total_wait_time, process_count); \
}

void run_tests();