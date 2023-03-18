#pragma once

#include <vector>
#include <unordered_map>

enum CoreType {	Performance, Efficiency };

struct CoreUsage {
	int num;
    int used;
    int idle;
	CoreType type;
};

class CPUAccess {
	public:
		CPUAccess();
		std::vector<CoreUsage> getCoreUsage();

	private:
		std::unordered_map<int,CoreType> determineCoreLayout();
		std::vector<std::vector<unsigned long long>> getCoreTimes();

		std::vector<std::vector<unsigned long long>> prev_cpu_times;
		unsigned int num_cores;
		std::unordered_map<int,CoreType> layout;
};
