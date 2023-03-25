#pragma once

class HistogramEntry {
	public:
		HistogramEntry(int n, int avg, int max);

		int getCount();
		int getScaledAvg(int maxValue);
		int getScaledMax(int maxValue);

		void accumulate(int avg, int max);

	private:
		int n;
		int avg;
		int max;
};
