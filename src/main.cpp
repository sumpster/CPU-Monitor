#include <stdio.h>

#include <QObject>
#include <QApplication>
#include <QVBoxLayout>
#include <QTimer>

#include "model.h"
#include "hw/linux.h"
#include "ui/dots.h"
#include "ui/chart.h"
#include "ui/section.h"

#include <vector>

#define PERFORMANCE "performance"
#define EFFICIENCY "efficiency"

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

	CPUAccess access;
	Model model(access);
    QTimer timer;

	Dots performanceDots(PERFORMANCE);
	Chart performanceChart(PERFORMANCE);
	Dots efficiencyDots(EFFICIENCY);
	Chart efficiencyChart(EFFICIENCY);

	performanceDots.setData(model.getSection(CoreType::Performance));
	performanceChart.setData(model.getSection(CoreType::Performance));
	efficiencyDots.setData(model.getSection(CoreType::Efficiency));
	efficiencyChart.setData(model.getSection(CoreType::Efficiency));

	QObject::connect(&model, SIGNAL(updated()), &performanceDots, SLOT(update()));
	QObject::connect(&model, SIGNAL(updated()), &performanceChart, SLOT(update()));
	QObject::connect(&model, SIGNAL(updated()), &efficiencyDots, SLOT(update()));
	QObject::connect(&model, SIGNAL(updated()), &efficiencyChart, SLOT(update()));
    QObject::connect(&timer, &QTimer::timeout, [&]() {
		model.update();
    });

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 10, 0, 0);
    layout->setSpacing(0); 

    Section *perfSection = new Section("Performance Cores", &performanceDots, &performanceChart);
    Section *effSection = new Section("Efficiency Cores", &efficiencyDots, &efficiencyChart);
    layout->addWidget(perfSection);
    layout->addWidget(effSection);

    QWidget widget;
    widget.setLayout(layout);
    widget.setWindowTitle("CPU Monitor");
	widget.setMinimumSize(700, 400);
    widget.show();

    timer.start(100);
    return app.exec();
}
