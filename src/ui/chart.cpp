#include <cassert>
#include <deque>

#include "chart.h"

Chart::Chart(Palette palette, QWidget *parent) : QWidget(parent), palette(palette) {
	setMinimumSize(100, 100);
}

void Chart::setData(CoreStats* data) {
	this->data = data;
	update();
}

void Chart::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QRect size = rect();
	painter.fillRect(size, QColor("101010"));

	QPen pen;
	pen.setColor(palette.Active);
	pen.setWidth(1);
	painter.setPen(pen);

	paintAvg(painter, data->avgHistogram);
	paintMax(painter, data->maxHistogram);
}

void Chart::paintAvg(QPainter &painter, std::deque<int> values) {
	const int widgetHeight = height();
	const int widgetWidth = width();

	int dataIndex = values.size() - widgetWidth;
	if (dataIndex < 0) {
		dataIndex = 0;
	}

	int startX = widgetWidth - values.size() + dataIndex;
	for (int i = startX, j = dataIndex; j < values.size(); ++i, ++j) {
		int x = i;
		int y = widgetHeight - (values[j] * widgetHeight / 100);

		painter.drawLine(x, widgetHeight, x, y);
	}
}

void Chart::paintMax(QPainter &painter, std::deque<int> values) {
	const int widgetHeight = height();
	const int widgetWidth = width();

	int dataIndex = values.size() - widgetWidth;
	if (dataIndex < 0) {
		dataIndex = 0;
	}

	int prevX = widgetWidth - values.size() + dataIndex;
	int prevY = widgetHeight - (values[dataIndex] * widgetHeight / 100);

	for (int i = prevX + 1, j = dataIndex + 1; j < values.size(); ++i, ++j) {
		int x = i;
		int y = widgetHeight - (values[j] * widgetHeight / 100);

		painter.drawLine(prevX, prevY, x, y);

		prevX = x;
		prevY = y;
	}
}
