// Header al structurilor folosite pentru a retine datele unui proces si a unei instante de executie din profilul de executie

struct process
{
	int time = 0;
	int priority = 0;
	int pid = 0;
	int priority_class = 0;
};

struct cpu_burst
{
	int start_time = 0;
	int stop_time = 0;
	int duration = 0;
	int pid = 0;

	cpu_burst();
	cpu_burst(int start_time, int stop_time, int duration, int pid);
	bool operator==(const cpu_burst b2) const;
};