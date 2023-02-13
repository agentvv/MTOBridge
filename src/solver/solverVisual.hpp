#pragma once


#include <QtCharts>
#include <QtWidgets>

#include "../report/report_mocks.hpp"


namespace mtobridge {
class SolverVisual : public QWidget {
	Q_OBJECT

	public:
		SolverVisual(QTabWidget *parent);
		~SolverVisual();

		void visualize();

	signals:
		void runCommand(MockCalculationInputT);

	public slots:
		void errorOccurred(QString);

	private:
		QGroupBox* forceSettingGroup;
		QGroupBox* solverSettingGroup;
		//Force setting window
		//Solver setting window
		QPushButton* calculateButton;
		QGroupBox* saveLoadGroup;
		//QPushButton* saveButton;
		//QPushButton* loadButton;
		//Truck + bridge window

		QChart* mChart;
		QChartView* mChartView;

		void createPage();
};
};  // namespace mtobridge
