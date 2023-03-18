#include <deque>
#include <QPainter>

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

	const int widgetHeight = height();
	const int widgetWidth = width();

	auto d = data->histogram;
	int dataIndex = d.size() - widgetWidth;
	if (dataIndex < 0) {
		dataIndex = 0;
	}

	int prevX = widgetWidth - d.size() + dataIndex;
	int prevY = widgetHeight - (d[dataIndex] * widgetHeight / 100);

	for (int i = prevX + 1, j = dataIndex + 1; j < d.size(); ++i, ++j) {
		int x = i;
		int y = widgetHeight - (d[j] * widgetHeight / 100);

		painter.drawLine(prevX, prevY, x, y);

		prevX = x;
		prevY = y;
	}
}
