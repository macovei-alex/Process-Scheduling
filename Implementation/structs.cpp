#include "structs.h" 

cpu_burst::cpu_burst() {}

cpu_burst::cpu_burst(int start_time, int stop_time, int duration, int pid)
{
	this->start_time = start_time;
	this->stop_time = stop_time;
	this->duration = duration;
	this->pid = pid;
}

// Comparator de egalitate utilizat pentru efectuarea compararii rezultatului obtinut cu rezultatul asteptat in testele din "Unit_test/Tests/tests.cpp"
bool cpu_burst::operator==(const cpu_burst b2) const
{
	return (start_time == b2.start_time
		&& stop_time == b2.stop_time
		&& pid == b2.pid
		&& duration == b2.duration);
}