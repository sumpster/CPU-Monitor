#pragma once

#include <QWidget>

class Section : public QWidget {
	Q_OBJECT

	public:
		Section(const QString &title, QWidget *left, QWidget *right, QWidget *parent = nullptr);
		~Section();
		void resizeEvent(QResizeEvent *event) override;

	private:
		QWidget *left;
};
