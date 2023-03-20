#pragma once

#include <QString>
#include <QtWidgets>

#include "../model.h"

class Dots : public QWidget {
	Q_PROPERTY(QString type)
	
	public:
		Dots(QString type, QWidget *parent = nullptr);
		void setData(CoreStats* data);

	protected:
		void paintEvent(QPaintEvent *event) override;

	private:
		QColor blendColors(const QColor& from, const QColor& to, int value);

		CoreStats* data;
};
