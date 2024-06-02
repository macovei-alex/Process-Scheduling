#include "algorithms.h"

#include <algorithm>

// Un vector de pointeri catre functii primit de algoritmul "algorithms::Multi_level_Queue_Scheduling" care stabileste ce algoritmi vor fi utilizati pentru coada de pe fiecare nivel
void (*(algorithms::functions[algorithms::nr_of_levels]))(arguments, int bonus_process_count) = {&algorithms::FCFS, &algorithms::SJF, &algorithms::RR, &algorithms::RR};

/*
Calculare cuantei pentru algoritmii round-robin.
Se sorteaza un vector cu timpii de executie ai proceselor din coada, dupa care se alege valoarea de pe pozitia "nr_procese / 10" pentru a garanta ca valoarea cuantei alese este mai mare doar decat maxim 10% din timpii de executie ai proceselor
*/
int algorithms::calculate_quantum(std::deque<process> &queue)
{
	if (queue.size() == 0)
		return 0;
	std::vector<int> burst_times;
	for (auto &proc : queue)
		burst_times.push_back(proc.time);
	std::sort(burst_times.begin(), burst_times.end());
	return burst_times[burst_times.size() / 10];
}

// Variabila "bonus_process_count" furnizeaza numarul de procese aflate in cozile de executie ale nivelelor de mai jos in cazul in care a fost apelat "algorithms::Multi_level_Queue_Scheduling". Implicit aceasta are valoarea 0
void algorithms::FCFS(arguments, int bonus_process_count)
{
	int current_time = 0;

	/*
	Pentru toti algoritmii in afara de "algorithms::Multi_level_Queue_Scheduling", aceasta bucata de cod ajuta la reutilizarea functiei in "algorithms::Multi_level_Queue_Scheduling" si calcularea corecta a timpului mediu 	de asteptare.
	Explicatie: deoarece prin parametrul "deque<process>" fiecare dintre cei 5 algoritmi pe 1 singur nivel primeste doar coada de procese pentru nivelul pe care a fost chemata functia, timpul de asteptare al proceselor de pe celelalte nivele tot trebuie sa creasca.
	Explicatia este valabila pentru fiecare dintre cei 5 algoritmi pe 1 singur nivel
	*/
	if (!execution.empty())
		current_time = execution[execution.size() - 1].stop_time;
	process_count += queue.size();

	// Pentru fiecare proces din coada
	while (!queue.empty())
	{
		// Se actualizeaza profilul de executie al procesorului si variabilele de timp folosite
		execution.push_back({current_time, current_time + queue.front().time, queue.front().time, queue.front().pid});
		current_time += queue.front().time;
		total_wait_time += queue.front().time * (queue.size() - 1 + bonus_process_count);

		// Scoaterea procesului executat din coada
		queue.pop_front();
	}
}

// Executie similara cu "algorithms::FCFS", diferenta fiind in sortarea initiala a cozii de procese crescator dupa timpul de executie cu o functie lambda
void algorithms::SJF(arguments, int bonus_process_count)
{
	std::sort(queue.begin(), queue.end(),
			  [](process a, process b)
			  {
				  return a.time < b.time;
			  });
	int current_time = 0;
	if (!execution.empty())
		current_time = execution[execution.size() - 1].stop_time;
	process_count += queue.size();
	while (!queue.empty())
	{
		execution.push_back({current_time, current_time + queue.front().time, queue.front().time, queue.front().pid});
		current_time += queue.front().time;
		total_wait_time += queue.front().time * (queue.size() - 1 + bonus_process_count);
		queue.pop_front();
	}
}

void algorithms::RR(arguments, int bonus_process_count)
{
	int current_time = 0;
	if (!execution.empty())
		current_time = execution[execution.size() - 1].stop_time;
	int quantum = calculate_quantum(queue); // calcularea unei cuante benefice dupa formula prezentata anterior
	process_count += queue.size();

	// Cat timp exista procese care nu s-au terminat in coada
	while (!queue.empty())
		// Pentru fiecare proces din coada
		for (unsigned i = 0; i < queue.size(); i++)
		{
			// Se executa un "burst_time" din proces, aflat ca minimul dintre timpul total de executie ramas al procesului si valoarea cuantei alese
			int burst_time = std::min(quantum, queue[i].time);
			// Actualizarea profilului de executie si a variabilelor de timp conform "burst_time" calculat anterior
			execution.push_back({current_time, current_time + burst_time, burst_time, queue[i].pid});
			queue[i].time -= burst_time;
			current_time += burst_time;
			total_wait_time += burst_time * (queue.size() - 1 + bonus_process_count);

			// Daca prin executarea acestei bucati din proces procesul s-a terminat, atunci se scoate din coada
			if (queue[i].time == 0)
			{
				queue.erase(queue.begin() + i);
				i--;
			}
		}
}

// Executie similara cu "algorithms::FCFS", dar procesele sunt mai intai sortate descrescator dupa prioritatea de executie
void algorithms::Priority_Scheduling(arguments, int bonus_process_count)
{
	std::sort(queue.begin(), queue.end(),
			  [](process a, process b)
			  {
				  return a.priority > b.priority;
			  });
	int current_time = 0;
	if (!execution.empty())
		current_time = execution[execution.size() - 1].stop_time;
	process_count += queue.size();
	while (!queue.empty())
	{
		execution.push_back({current_time, current_time + queue.front().time, queue.front().time, queue.front().pid});
		current_time += queue.front().time;
		total_wait_time += queue.front().time * (queue.size() - 1 + bonus_process_count);
		queue.pop_front();
	}
}

// Algoritmul face sortarea proceselor descrescator dupa prioritate si executa "algorithms::RR" pe coada de procese
void algorithms::RR_Priority_Scheduling(arguments, int bonus_process_count)
{
	std::sort(queue.begin(), queue.end(),
			  [](process a, process b)
			  {
				  return a.priority_class > b.priority_class;
			  });
	int current_time = 0;
	if (!execution.empty())
		current_time = execution[execution.size() - 1].stop_time;
	int quantum = calculate_quantum(queue);
	process_count += queue.size();
	while (!queue.empty())
	{
		int current_priority_class = queue.front().priority_class;
		for (unsigned i = 0; i < queue.size() && queue.front().priority_class == current_priority_class; i++)
		{
			int burst_time = std::min(quantum, queue[i].time);
			execution.push_back({current_time, current_time + burst_time, burst_time, queue[i].pid});
			queue[i].time -= burst_time;
			current_time += burst_time;
			total_wait_time += burst_time * (queue.size() - 1 + bonus_process_count);

			if (queue[i].time == 0)
			{
				queue.erase(queue.begin() + i);
				i--;
			}
		}
	}
}

// Procesele sunt primite tot printr-o coada si sunt impartite in interiorul functiei in "algorithms::nr_of_levels" cozi. Pentru fiecare coada se apeleaza algoritmul indicat de vectorul de pointeri catre unele dintre functiile de mai sus
void algorithms::Multi_level_Queue_Scheduling(arguments, void (*functions[])(arguments, int bonus_process_count))
{
	// Impartirea in mai multe cozi
	std::deque<process> queues[algorithms::nr_of_levels];
	for (unsigned i = 0; i < queue.size(); i++)
		queues[queue[i].priority_class].push_back(queue[i]);

	for (int i = 0; i < algorithms::nr_of_levels; i++)
	{
		// Calcularea numarului de procese ramase in cozile de pe nivelele inferioare
		int bonus_process_count = 0;
		for (int j = i + 1; j < algorithms::nr_of_levels; j++)
			bonus_process_count += queues[j].size();

		// Apelarea functiei prestabilite pentru coada de pe nivelul respectiv
		(*functions[i])(queues[i], execution, total_wait_time, process_count, bonus_process_count);
	}
}