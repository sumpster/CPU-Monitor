#pragma once

#include <string>
#include <vector>
#include <deque>
#include <QObject>

#include "hw/linux.h"

struct CoreStats {
	CoreType type;
	std::vector<int> usage;
	std::deque<int> avgHistogram;
	std::deque<int> maxHistogram;
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

	private:
		int computeUsage(int used, int idle);

		CPUAccess access;
		std::vector<CoreStats*> stats;
};
