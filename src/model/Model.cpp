#include "Model.h"

#define BUCKET_SIZE 3

Model::Model(CPUAccess *access) : QObject(), access(access) {
	update();
}

Model::~Model() {
	for (CoreStats *cs : stats)
		delete cs;
}

int Model::getSectionCount() {
	return stats.size();
}

CoreStats* Model::getSection(CoreType type) {
	for (CoreStats *cs : stats)
		if (type == cs->type)
			return cs;

	return stats[0];
}

std::string Model::getNameForType(CoreType type) {
	switch (type) {
		case Performance: return "Performance";
		case Efficiency: return "Efficiency";
		default: return "Unknown";
	}
}

void Model::update() {
	updateUsage();
	updateHistogram();
}

void Model::updateUsage() {
	for (CoreStats *cs : stats)
		cs->usage.clear();

	std::vector<CoreUsage> usageData = access->getCoreUsage();
	for (CoreUsage cu : usageData) {
		bool exists = false;
		for (CoreStats *cs : stats) {
			if (cu.type == cs->type) {
				int usage = computeUsage(cu.used, cu.idle);
				cs->usage.push_back(usage);
				exists = true;
				break;
			}
		}

		if (!exists) {
			int usage = computeUsage(cu.used, cu.idle);
			CoreStats *cs = new CoreStats;
			cs->type = cu.type;
			cs->usage = std::vector<int>(1, usage);
			cs->histogram = std::deque<HistogramEntry*>();
			stats.push_back(cs);
		}
	}

	emit updated();
}

void Model::updateHistogram() {
	bool updateHistogram = false;
	for (CoreStats *cs : stats) {
		int avg = 0;
		int max = 0;
		for (int usage : cs->usage) {
			avg += usage;
			if (usage > max)
				max = usage;
		}
		avg /= cs->usage.size();

		HistogramEntry *current = cs->histogram.size() == 0 ? nullptr : cs->histogram.back();

		if (current == nullptr || current->getCount() == BUCKET_SIZE) {
			current = new HistogramEntry(1, avg, max);
			cs->histogram.push_back(current);

		} else {
			current->accumulate(avg, max);
		}

		if (current->getCount() == BUCKET_SIZE)
			updateHistogram = true;
	}

	if (updateHistogram)
		emit updatedHistogram();
}

int Model::computeUsage(int used, int idle) {
	if (used + idle == 0)
		return 0;
	return (used * 100) / (used + idle);
}
