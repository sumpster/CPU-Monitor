#include <cassert>
#include <deque>

#include <QColor>
#include <QPalette>
#include <QVariant>

#include "Chart.h"

Chart::Chart(const QString *type, QWidget *parent) : QWidget(parent) {
	setMinimumSize(100, 100);
	setProperty("type", *type);
}

Chart::~Chart() {}

void Chart::setData(CoreStats* data) {
	this->data = data;
	update();
}

void Chart::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);

	QColor color = palette().color(QPalette::Text);
	QColor background = palette().color(QPalette::Window);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QRect size = rect();
	painter.fillRect(size, background);

	QPen pen;
	pen.setColor(color);
	pen.setWidth(1);
	painter.setPen(pen);

	paintBars(painter, data->histogram);
}

void Chart::paintBars(QPainter &painter, std::deque<HistogramEntry*> histogram) {
	QColor avgColor = palette().color(QPalette::Text);
	QColor maxColor = palette().color(QPalette::Text);
	maxColor.setAlpha(50);

	const int widgetHeight = height();
	const int widgetWidth = width();
	const int entryWidth = 4; // 3 pixels wide + 1 pixel free space
	const int maxEntries = widgetWidth / entryWidth;

	int startIndex = 0;
	if ((int)histogram.size() > maxEntries) {
		startIndex = histogram.size() - maxEntries;
	}

	for (int i = startIndex; i < (int)histogram.size(); ++i) {
		const int max = histogram[i]->getScaledMax(widgetHeight);
		const int avg = histogram[i]->getScaledAvg(widgetHeight);
		const int x = (i - startIndex) * entryWidth;

		QRect maxBar(x, widgetHeight - max, 3, max);
		painter.fillRect(maxBar, maxColor);

		QRect avgBar(x, widgetHeight - avg, 3, avg);
		painter.fillRect(avgBar, avgColor);
	}
}
