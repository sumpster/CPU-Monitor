#pragma once

#include <string>
#include <vector>
#include <deque>
#include <QObject>

#include "../hw/linux.h"

#include "HistogramEntry.h"

struct CoreStats {
	CoreType type;
	std::vector<int> usage;
	std::deque<HistogramEntry*> histogram;
};

class Model : public QObject {
	Q_OBJECT
	
	public:
		Model(CPUAccess *access);
		~Model();
		void update();
		int getSectionCount();
		CoreStats* getSection(CoreType type);
		std::string getNameForType(CoreType type);

	signals:
		void updated();
		void updatedHistogram();

	private:
		void updateUsage();
		void updateHistogram();
		int computeUsage(int used, int idle);

		CPUAccess *access;
		std::vector<CoreStats*> stats;
};
