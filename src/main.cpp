#include <stdio.h>

#include <QObject>
#include <QApplication>
#include <QVBoxLayout>
#include <QTimer>

#include "model.h"
#include "hw/linux.h"
#include "ui/dots.h"
#include "ui/chart.h"
#include "ui/style.h"
#include "ui/section.h"

#include <vector>

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

	Dots performanceDots(Color::Performance);
	Chart performanceChart(Color::Performance);
	Dots efficiencyDots(Color::Efficiency);
	Chart efficiencyChart(Color::Efficiency);

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
    Section *perfSection = new Section("Performance Cores", &performanceDots, &performanceChart);
    Section *effSection = new Section("Efficiency Cores", &efficiencyDots, &efficiencyChart);
    layout->addWidget(perfSection);
    layout->addWidget(effSection);

    QWidget widget;
    widget.setLayout(layout);
    widget.setWindowTitle("CPU Monitor");
	widget.setMinimumSize(700, 400);
    widget.show();

    timer.start(200);
    return app.exec();
}
