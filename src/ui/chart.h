#pragma once

#include <deque>

#include <QWidget>
#include <QPainter>

#include "palette.h"
#include "../model.h"

class Chart : public QWidget {
	public:
		Chart(Palette palette, QWidget *parent = nullptr);
		void setData(CoreStats *data);

	protected:
		void paintEvent(QPaintEvent *event) override;

	private:
		void paintAvg(QPainter &painter, std::deque<int> values);
		void paintMax(QPainter &painter, std::deque<int> values);

		Palette palette;
		CoreStats* data;
};
