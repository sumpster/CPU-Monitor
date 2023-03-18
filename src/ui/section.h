#pragma once

#include <QWidget>

class Section : public QWidget {
	public:
		Section(const QString &title, QWidget *left, QWidget *right, QWidget *parent = nullptr);
};
