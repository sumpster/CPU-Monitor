#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "linux.h"

CPUAccess::CPUAccess() {
	layout = determineCoreLayout();
	num_cores = layout.size();
	prev_cpu_times = getCoreTimes();
}

std::vector<CoreUsage> CPUAccess::getCoreUsage() {
	std::vector<std::vector<unsigned long long>> curr_cpu_times = getCoreTimes();
	std::vector<CoreUsage> cpu_data(num_cores);
	for (unsigned int i = 0; i < num_cores; ++i) {
		cpu_data[i].used = curr_cpu_times[i][0] - prev_cpu_times[i][0];
		cpu_data[i].idle = curr_cpu_times[i][1] - prev_cpu_times[i][1];
		cpu_data[i].type = layout[i];
	}
	prev_cpu_times = curr_cpu_times;
	return cpu_data;
}

std::vector<std::vector<unsigned long long>> CPUAccess::getCoreTimes() {
	std::ifstream ifs("/proc/stat");
	std::string line;
	std::vector<std::vector<unsigned long long>> cpu_times;
	while (std::getline(ifs, line)) {
		std::istringstream iss(line);
		std::string cpu_name;
		iss >> cpu_name;
		if (cpu_name.find("cpu") == 0 && cpu_name != "cpu") {
			unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
			iss >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
			unsigned long long usedSum = user + nice + system + iowait + irq + softirq + steal + guest + guest_nice;
			unsigned long long idleSum = idle;
			cpu_times.push_back({usedSum, idleSum});
		}
	}
	return cpu_times;
}

std::unordered_map<int,CoreType> CPUAccess::determineCoreLayout() {
	std::unordered_map<int, std::vector<int>> collector;

    std::ifstream cpuinfoFile("/proc/cpuinfo");
    std::string line;
	int currentProcessorId = -1;
    while (std::getline(cpuinfoFile, line)) {

        if (line.find("processor") != std::string::npos) {
			currentProcessorId = std::stoi(line.substr(line.find(":") + 2));

        } else if (line.find("core id") != std::string::npos) {
			int coreID = std::stoi(line.substr(line.find(":") + 2));

			if (collector.count(coreID) == 0) {
				collector[coreID] = {currentProcessorId};
			} else {
				collector[coreID].push_back(currentProcessorId);
			}
        }
    }
    cpuinfoFile.close();

	std::unordered_map<int, CoreType> result;
	for (const auto& pair : collector) {
        std::vector<int> processorIds = pair.second;
		CoreType type = processorIds.size() > 1 ? Performance : Efficiency;
		for (int id : processorIds)
			result[id] = type;
    }
	return result;
}
