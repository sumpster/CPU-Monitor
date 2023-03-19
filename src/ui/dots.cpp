#include <QColor>

#include "dots.h"

Dots::Dots(Palette palette, QWidget *parent) : QWidget(parent), palette(palette) {
	setMinimumSize(QSize(100, 100));
	data = {};
}

void Dots::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);
	QPainter painter(this);
	QRect size = rect();
	painter.fillRect(size, QColor("101010"));

	const int n = data->usage.size();
	const int cols = n / 4;
    const int margin = 5;
    const float dotSize = ((size.width() - margin) / 4.0) - margin;

    float x = margin;
    float y = margin;
	int i = 0;
    for (int u : data->usage) {
		QColor indiCol = blendColors(palette.Inactive, palette.Active, u);
        QRectF dot(x, y, dotSize, dotSize);
		painter.fillRect(dot, indiCol);
        x += dotSize + margin;
        if ((i + 1) % cols == 0) {
            x = margin;
            y += dotSize + margin;
        }
		i++;
    }
}

void Dots::setData(CoreStats* data) {
	this->data = data;
	update();
}

QColor Dots::blendColors(const QColor& from, const QColor& to, int value) {
    value = qBound(0, value, 20);
    double fractionFrom = (20 - value) / 20.0;
    double fractionTo = value / 20.0;

    int red = static_cast<int>(fractionFrom * from.red() + fractionTo * to.red());
    int green = static_cast<int>(fractionFrom * from.green() + fractionTo * to.green());
    int blue = static_cast<int>(fractionFrom * from.blue() + fractionTo * to.blue());

    return QColor(red, green, blue);
}
