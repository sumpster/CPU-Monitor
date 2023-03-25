#include <QColor>
#include <QPalette>
#include <QVariant>

#include "Dots.h"

#define VMAX 100

Dots::Dots(const QString *type, QWidget *parent) : QWidget(parent) {
	setMinimumSize(QSize(100, 100));
	setProperty("type", *type);
	data = {};
}

Dots::~Dots() {}

void Dots::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);

	QColor color = palette().color(QPalette::Text);
	QColor background = palette().color(QPalette::Window);

	QPainter painter(this);
	QRect size = rect();
	painter.fillRect(size, background);

	QPen borderPen(blendColors(background, color, 20));
	painter.setPen(borderPen);

	const int n = data->usage.size();
	const int cols = n / 4;
    const int margin = 5;
    const float dotSize = ((size.width() - margin) / 4.0) - margin;

    float x = margin;
    float y = margin;
	int i = 0;
    for (int u : data->usage) {
		QColor indiCol = blendColors(background, color, u);
        QRect dot(x, y, dotSize, dotSize);
		painter.fillRect(dot, indiCol);
		painter.drawRect(dot);
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
    value = qBound(0, value, VMAX);
    double fractionTo = value / (double)VMAX;
    double fractionFrom = 1 - fractionTo;

    int red = static_cast<int>(fractionFrom * from.red() + fractionTo * to.red());
    int green = static_cast<int>(fractionFrom * from.green() + fractionTo * to.green());
    int blue = static_cast<int>(fractionFrom * from.blue() + fractionTo * to.blue());

    return QColor(red, green, blue);
}
