#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

#include "section.h"

Section::Section(const QString &title, QWidget *left, QWidget *right, QWidget *parent) : QWidget(parent), left(left) {
	QVBoxLayout *rowLayout = new QVBoxLayout();
    rowLayout->setContentsMargins(10, 0, 10, 10); // Set layout margins
    rowLayout->setSpacing(5); 

	QLabel *titleLabel = new QLabel(title);
	rowLayout->addWidget(titleLabel);

	QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->setSpacing(10); 

	left->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	contentLayout->addWidget(left);

	right->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	contentLayout->addWidget(right);

	rowLayout->addLayout(contentLayout);
	setLayout(rowLayout);
}

void Section::resizeEvent(QResizeEvent *event) {
	Q_UNUSED(event);
	int h = left->height();
    left->setMinimumWidth(h);
	left->setMaximumWidth(h);
}
