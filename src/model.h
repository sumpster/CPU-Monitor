#pragma once

#include <string>
#include <vector>
#include <deque>
#include <QObject>

#include "hw/linux.h"
struct HistogramEntry {
    int max;
    int avg;
	int n;
};

struct CoreStats {
	CoreType type;
	std::vector<int> usage;
	std::deque<HistogramEntry*> histogram;
};

class Model : public QObject {
	Q_OBJECT
	
	public:
		Model(CPUAccess access);
		~Model();
		void update();
		int getSectionCount();
		CoreStats* getSection(CoreType type);
		std::string getNameForType(CoreType type);

	signals:
		void updated();
		void updatedHistogram();

	private:
		int computeUsage(int used, int idle);

		CPUAccess access;
		std::vector<CoreStats*> stats;
};
