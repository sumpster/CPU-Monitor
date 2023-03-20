#include <cassert>
#include <deque>

#include <QColor>
#include <QPalette>
#include <QVariant>

#include "chart.h"

Chart::Chart(QString type, QWidget *parent) : QWidget(parent) {
	setMinimumSize(100, 100);
	setProperty("type", type);
}

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
	for (int i = startX, j = dataIndex; j < (int)values.size(); ++i, ++j) {
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

	for (int i = prevX + 1, j = dataIndex + 1; j < (int)values.size(); ++i, ++j) {
		int x = i;
		int y = widgetHeight - (values[j] * widgetHeight / 100);

		painter.drawLine(prevX, prevY, x, y);

		prevX = x;
		prevY = y;
	}
}
