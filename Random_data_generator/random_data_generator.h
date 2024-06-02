#pragma once

#include <random>
#include <fstream>

class random_data_generator
{
private:
	std::mt19937 generator; // generator de numere aleatoare
	std::uniform_int_distribution<int> uniform_distribution; // simuleaza o distribuire uniforma a unui numar
	std::normal_distribution<double> normal_distribution; // simuleaza o distributire normala a unui numar

	int generate_uniform();
	int generate_normal();
	random_data_generator(int uniform_min, int uniform_max, int normal_mean, int normal_deviation);

public:
	static void data_set_generator(int process_count, int uniform_min = 1, int unifor_max = 9, int normal_mean = 0, int normal_deviation = 7);
};