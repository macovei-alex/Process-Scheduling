#include "utility.h"

#include <iostream>
#include <iomanip>
#include <fstream>

void utility::reset_execution_data(std::vector<cpu_burst>& execution, double& total_wait_time, int& process_count)
{
	execution.clear();
	total_wait_time = 0;
	process_count = 0;
}

// Afisarea profilului de executie sub forma de lista de tuple
void utility::print_tuple_list(std::vector<cpu_burst>& execution, const char* alg_name, double& total_wait_time, int& process_count)
{
	if (process_count == 0)
		return;
	std::cout << alg_name << " algorithm\n";
	std::cout << "average wait time: " << total_wait_time / process_count << '\n';
	for (unsigned i = 0; i < execution.size(); i++)
	{
		std::cout << "<start: " << std::setw(3) << execution[i].start_time << "ms, ";
		std::cout << "stop: " << std::setw(3) << execution[i].stop_time << "ms, ";
		std::cout << "duration: " << std::setw(3) << execution[i].duration;
		std::cout << "ms, pid: " << std::setw(2) << execution[i].pid << ">\n";
	}
	std::cout << '\n';
	reset_execution_data(execution, total_wait_time, process_count);
}

void utility::read_process_queue(std::deque<process>& queue, const char* file)
{
	std::ifstream fin(file);
	if (!fin.good())
	{
		std::cout << "File " << file << " could not be open\n";
		return;
	}
	int n;
	fin >> n;
	queue.resize(n);
	for (int i = 0; i < n; i++)
		fin >> queue[i].pid >> queue[i].priority_class >> queue[i].priority >> queue[i].time;
}