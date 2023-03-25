#include "HistogramEntry.h"

HistogramEntry::HistogramEntry(int n, int avg, int max) : n(n), avg(avg), max(max) {}

int HistogramEntry::getCount() {
	return n;
}

int HistogramEntry::getScaledAvg(int maxValue) {
	const float scaling = maxValue / 100.0;
	return scaling * (float)avg;
}

int HistogramEntry::getScaledMax(int maxValue) {
	const float scaling = maxValue / 100.0;
	return scaling * (float)max;
}

void HistogramEntry::accumulate(int avg, int max) {
	this->n++;
	this->avg += avg;
	if (max > this->max)
		this->max = max;
}
