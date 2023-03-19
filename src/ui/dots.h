#pragma once

#include <QtWidgets>

#include "palette.h"
#include "../model.h"

class Dots : public QWidget {
	public:
		Dots(Palette palette, QWidget *parent = nullptr);
		void setData(CoreStats* data);

	protected:
		void paintEvent(QPaintEvent *event) override;

	private:
		QColor blendColors(const QColor& from, const QColor& to, int value);

		Palette palette;
		CoreStats* data;
};
