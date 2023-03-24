#pragma once

#include <deque>

#include <QString>
#include <QWidget>
#include <QPainter>

#include "../model.h"

class Chart : public QWidget {
	Q_OBJECT

	public:
		Chart(const QString *type, QWidget *parent = nullptr);
		~Chart();
		void setData(CoreStats *data);

	protected:
		void paintEvent(QPaintEvent *event) override;

	private:
		void paintBars(QPainter &painter, std::deque<HistogramEntry*> histogram);
		void scale(HistogramEntry &scaled, HistogramEntry *source, float scale);

		CoreStats* data;
};
