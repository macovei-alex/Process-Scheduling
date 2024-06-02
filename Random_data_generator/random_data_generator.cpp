#include "random_data_generator.h"

#include <iomanip>
#include <iostream>

random_data_generator::random_data_generator(int uniform_min, int uniform_max, int normal_mean, int normal_deviation)
	: generator(time(0)), uniform_distribution(uniform_min, uniform_max), normal_distribution(normal_mean, normal_deviation)
{}

int random_data_generator::generate_uniform()
{
	return uniform_distribution(generator);
}

int random_data_generator::generate_normal()
{
	return abs(int(normal_distribution(generator))); 
}

/*
Genereaza un set de date aleatoare in fisierul "Data/random_data.txt".
Poate fi parametrizat cu: 
	- numarul de procese create, minimul distributiei
	- minimul si maximul distributiei uniforme pentru prioritati
	- mijlocul si deviatia distributiei normale pentru timpii de executie
*/
void random_data_generator::data_set_generator(int process_count, int uniform_min, int uniform_max, int normal_mean, int normal_deviation)
{
	if (process_count <= 0 || uniform_max < uniform_min)
		throw("Invalid inputs to generate random data from\n");
	random_data_generator RNG(uniform_min, uniform_max, normal_mean, normal_deviation);
	int aux, digit_count;
	for (aux = process_count, digit_count = 0; aux > 0; aux /= 10, digit_count++);

	std::ofstream fout("./Data/random_data.txt");
	srand(time(0));
	fout << process_count << '\n';
	for (int i = 0; i < process_count; i++)
	{
		fout << std::setw(digit_count) << i << "  ";
		fout << rand() % 4 << "  "; // clasa de prioritate
		fout << std::setw(2) << RNG.generate_uniform() << "  "; // prioritatea
		fout << std::setw(2) << RNG.generate_normal() + 1; // timpul de executie; se adauga 1 pentru a nu avea procese cu timpul de executie 0
		fout << std::endl;
	}
}