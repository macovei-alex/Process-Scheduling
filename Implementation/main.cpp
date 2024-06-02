#include "../Unit_test/Tests/tests.h"
#include "../Random_data_generator/random_data_generator.h"

#include <iostream>

// Functie care apeleaza toti algoritmii pe un set de date citite din fisierul dat ca parametru. "arguments" este o macrocomanda, se afla definita in "Implementation/algorithms.h" si este folosita pentru estetica. Algoritmii sunt metode cu tipul returnat void pentru care ultimii 3 parametri sunt trimisi prin referinta si reprezinta datele de iesire. In metoda de afisare a datelor se afla si metoda de resetare a variabilelor si structurilor date ca parametru, pentru ca acestea sa poata fi folosite in continuare pentru urmatorul algoritm
void run(const char *file, arguments)
{
	utility::read_process_queue(queue, file);

	algorithms::FCFS(queue, execution, total_wait_time, process_count);
	utility::print_tuple_list(execution, name_FCFS, total_wait_time, process_count);

	algorithms::SJF(queue, execution, total_wait_time, process_count);
	utility::print_tuple_list(execution, name_SJF, total_wait_time, process_count);

	algorithms::RR(queue, execution, total_wait_time, process_count);
	utility::print_tuple_list(execution, name_RR, total_wait_time, process_count);

	algorithms::Priority_Scheduling(queue, execution, total_wait_time, process_count);
	utility::print_tuple_list(execution, name_PS, total_wait_time, process_count);

	algorithms::RR_Priority_Scheduling(queue, execution, total_wait_time, process_count);
	utility::print_tuple_list(execution, name_RRPS, total_wait_time, process_count);

	algorithms::Multi_level_Queue_Scheduling(queue, execution, total_wait_time, process_count, algorithms::functions);
	utility::print_tuple_list(execution, name_MLQS, total_wait_time, process_count);
}

// Apelarea tuturor functiilor pe setul de date aflat in fisierul "Data/manual_data.txt"
void run_manual_data()
{
	std::deque<process> queue;
	std::vector<cpu_burst> execution;
	int process_count = 0;
	double total_wait_time = 0;
	run("./Data/manual_data.txt", queue, execution, total_wait_time, process_count);
}

// Apelarea tuturor algoritmilor pe setul de date aleatoare ce se genereaza automat in fisierul "Data/random_data.txt"
void run_random_data(int n = 10, int uniform_min = 1, int uniform_max = 9, int normal_mean = 0, int normal_deviation = 7)
{
	std::deque<process> queue;
	std::vector<cpu_burst> execution;
	int process_count = 0;
	double total_wait_time = 0;
	random_data_generator::data_set_generator(n, uniform_min, uniform_max, normal_mean, normal_deviation);
	run("./Data/random_data.txt", queue, execution, total_wait_time, process_count);
}

// Constante declarate pentru o mai usoara intelegere, implementare si modificare a codului
enum MENU_CONSTANS
{
	RUN_MANUAL = 1,
	RUN_RANDOM = 2,
	RUN_TESTS = 3,
	EXIT = 4,

	DEFAULT_PARAMETERS = 1,
	CUSTOM_PARAMETERS = 2,
	RETURN = 3,
};

// Functie care asteapta un int de la tastatura si trateaza erorile care pot aparea la utilizarea sa intr-un mod inadecvat. Functia poate primi un mesaj pe care sa-l repete de fiecare data cand intrarea nu este valida, pentru a arata utilizatorului ce trebuie introdus
int input_int(const char *bonus_message = nullptr)
{
	int val;
	while (!(std::cin >> val)) // verificare ca intrarea sa fie valida
	{
		std::cin.clear();			  // resetarea starii lui std::cin
		std::cin.ignore(10000, '\n'); // ignorarea a 10000 de caractere din stream, considerand ca acestea au fost introduse eronat
		std::cout << "\nInvalid input\n\n";
		if (bonus_message != nullptr)
			std::cout << bonus_message;
	}
	std::cout << "\n";
	return val;
}

// Citirea parametrilor de randomizare a datelor de intrare
void input_custom_parameters(int &process_count, int &uniform_min, int &uniform_max, int &normal_mean, int &normal_deviation)
{
	std::cout << "Input the number of processes to generate:\n";
	process_count = input_int("Input the number of processes to generate:\n");

	std::cout << "Input the minimum priority:\n";
	uniform_min = input_int("Input the minimum priority:\n");

	std::cout << "Input the maximum priority:\n";
	uniform_max = input_int("Input the maximum priority:\n");

	std::cout << "Input the mean of the normal distribution for the burst times:\n";
	normal_mean = input_int("Input the mean of the normal distribution for the burst times:\n");

	std::cout << "Input the deviation of the normal distribution for the burst times:\n";
	normal_deviation = input_int("Input the deviation of the normal distribution for the burst times:\n");
}

// Afisarea optiunilor din meniul principal
void menu_1_print()
{
	std::cout << "Select an option:\n";
	std::cout << "   " << RUN_MANUAL << ". Run keyboard input data (from Data/manual_data.txt)\n";
	std::cout << "   " << RUN_RANDOM << ". Run randomly generated data (generated to Data/random_data.txt)\n";
	std::cout << "   " << RUN_TESTS << ". Run tests (from Unit test/Inputs/test1.txt and Unit test/Inputs/test2.txt)\n";
	std::cout << "   " << EXIT << ". Exit\n";
	std::cout << "\n";
}

// Afisarea optiunilor din meniul secundar. Apare in cazul in care se alege optiunea "Run randomly generated data (generated to Data/random_data.txt)"
void menu_2_print()
{
	std::cout << "Select an option:\n";
	std::cout << "   " << DEFAULT_PARAMETERS << ". Run with default parameters (10, 1, 9, 0, 7)\n";
	std::cout << "   " << CUSTOM_PARAMETERS << ". Run with custom parameters\n";
	std::cout << "   " << RETURN << ". Return to the previous menu\n";
	std::cout << "\n\n";
}

// Implementarea meniurilor cu ajutorul a 2 instructiuni "switch" aflate intr-o bucla infinita. Iesirea din program se face cu prima optiune a meniului principal
int main()
{
	int option1, option2;
	int process_count, uniform_min, uniform_max, normal_mean, normal_deviation;
	while (true)
	{
		menu_1_print();
		option1 = input_int();
		switch (option1)
		{
		case RUN_MANUAL:
			run_manual_data();
			break;
		case RUN_TESTS:
			run_tests(); // metoda este implementata in fisierul "Unit_test/Tests/tests.cpp"
			std::cout << '\n';
			break;
		case EXIT:
			return 0;
		default:
			std::cout << "Invalid input\n\n";
			break;
		case RUN_RANDOM:
			menu_2_print();
			option2 = input_int();
			switch (option2)
			{
			case DEFAULT_PARAMETERS:
				run_random_data();
				break;
			case CUSTOM_PARAMETERS:
				input_custom_parameters(process_count, uniform_min, uniform_max, normal_mean, normal_deviation);
				try
				{
					run_random_data(process_count, uniform_min, uniform_max, normal_mean, normal_deviation);
				}
				catch (const char *error_message)
				{
					std::cout << error_message << '\n';
				}
				break;
			case RETURN:
			default:
				break;
			}
		}
	}
}