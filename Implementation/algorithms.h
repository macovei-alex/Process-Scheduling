#pragma once

#include "utility.h"

// Macrocomanda ce descrie parametrii formali primiti de catre toti algoritmii
#define arguments std::deque<process> queue, std::vector<cpu_burst>& execution, double& total_wait_time, int& process_count

// Interfata clasei de algoritmi implementate in "Implementation/algorithms.cpp"
class algorithms
{
private:
	static int calculate_quantum(std::deque<process>& queue);
public:
	static const int nr_of_levels = 4;
	static void(*(functions[]))(arguments, int bonus_process_count);
	static void FCFS(arguments, int bonus_process_count = 0);
	static void SJF(arguments, int bonus_process_count = 0);
	static void RR(arguments, int bonus_process_count = 0);
	static void Priority_Scheduling(arguments, int bonus_process_count = 0);
	static void RR_Priority_Scheduling(arguments, int bonus_process_count = 0);
	static void Multi_level_Queue_Scheduling(arguments, void(*functions[])(arguments, int bonus_process_count));
};