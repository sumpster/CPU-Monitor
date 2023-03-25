#pragma once

#include <QString>
#include <QtWidgets>

#include "../model/Model.h"

class Dots : public QWidget {
	Q_OBJECT
	
	public:
		Dots(const QString *type, QWidget *parent = nullptr);
		~Dots();
		void setData(CoreStats* data);

	protected:
		void paintEvent(QPaintEvent *event) override;

	private:
		QColor blendColors(const QColor& from, const QColor& to, int value);

		CoreStats* data;
};
