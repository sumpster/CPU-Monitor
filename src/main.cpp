#include <stdio.h>

#include <QObject>
#include <QApplication>
#include <QVBoxLayout>
#include <QTimer>

#include "model/Model.h"
#include "hw/linux.h"
#include "ui/Dots.h"
#include "ui/Chart.h"
#include "ui/Section.h"

#include <vector>

const QString *PERFORMANCE = new QString("performance");
const QString *EFFICIENCY = new QString("efficiency");

QString loadStyle() {
    QFile file(":dark.qss");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to load stylesheet.";
        return QString();
    }

    QTextStream in(&file);
    return in.readAll();
}

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	app.setStyleSheet(loadStyle());

	CPUAccess* access = new CPUAccess();
	Model* model = new Model(access);
	QTimer* timer = new QTimer();

	Dots* performanceDots = new Dots(PERFORMANCE);
	Chart* performanceChart = new Chart(PERFORMANCE);
	Dots* efficiencyDots = new Dots(EFFICIENCY);
	Chart* efficiencyChart = new Chart(EFFICIENCY);

	performanceDots->setData(model->getSection(CoreType::Performance));
	performanceChart->setData(model->getSection(CoreType::Performance));
	efficiencyDots->setData(model->getSection(CoreType::Efficiency));
	efficiencyChart->setData(model->getSection(CoreType::Efficiency));

	QObject::connect(model, SIGNAL(updated()), performanceDots, SLOT(update()));
	QObject::connect(model, SIGNAL(updatedHistogram()), performanceChart, SLOT(update()));
	QObject::connect(model, SIGNAL(updated()), efficiencyDots, SLOT(update()));
	QObject::connect(model, SIGNAL(updatedHistogram()), efficiencyChart, SLOT(update()));
	QObject::connect(timer, &QTimer::timeout, [&]() {
		model->update();
	});

	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins(0, 10, 0, 0);
	layout->setSpacing(0);

	Section* perfSection = new Section("Performance Cores", performanceDots, performanceChart);
	Section* effSection = new Section("Efficiency Cores", efficiencyDots, efficiencyChart);
	layout->addWidget(perfSection);
	layout->addWidget(effSection);

	QWidget* widget = new QWidget();
	widget->setLayout(layout);
	widget->setWindowTitle("CPU Monitor");
	widget->setMinimumSize(700, 400);
	widget->show();

	timer->start(100);
	int ret = app.exec();

	delete widget;

	return ret;
}