#pragma once

#include <QWidget>
#include <deque>

#include "palette.h"
#include "../model.h"

class Chart : public QWidget {
	public:
		Chart(Palette palette, QWidget *parent = nullptr);
		void setData(CoreStats* data);

	protected:
		void paintEvent(QPaintEvent *event) override;

	private:
		Palette palette;
		CoreStats* data;
};
