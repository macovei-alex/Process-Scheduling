// Fisierele "Implementation/utility.h" si "Implementation/utility.cpp" contin metode de citire a unei cozi de procese dintr-un fisier, afisarea profilului de executie al procesorului pentru un algoritm anume si resetarea datelor din profilul de executie

#pragma once

#include "structs.h"

#include <vector>
#include <deque>

constexpr const char* name_FCFS = "FCFS";
constexpr const char* name_SJF = "SJF";
constexpr const char* name_RR = "Round-robin";
constexpr const char* name_PS = "Priority Scheduling";
constexpr const char* name_RRPS = "Round-robin Priority Scheduling";
constexpr const char* name_MLQS = "Multi-level Queue Scheduling";

class utility
{
public:
	static void reset_execution_data(std::vector<cpu_burst>& execution, double& total_wait_time, int& process_count);
	static void print_tuple_list(std::vector<cpu_burst>& execution, const char* alg_name, double& total_wait_time, int& process_count);
	static void read_process_queue(std::deque<process>& queue, const char* file);
};