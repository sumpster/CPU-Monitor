#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

#include "section.h"

Section::Section(const QString &title, QWidget *left, QWidget *right, QWidget *parent) : QWidget(parent) {
	QVBoxLayout *rowLayout = new QVBoxLayout();

	QLabel *titleLabel = new QLabel(title);
	rowLayout->addWidget(titleLabel);

	QHBoxLayout *contentLayout = new QHBoxLayout();

	left->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	contentLayout->addWidget(left);

	right->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	contentLayout->addWidget(right);

	rowLayout->addLayout(contentLayout);
	setLayout(rowLayout);
}
