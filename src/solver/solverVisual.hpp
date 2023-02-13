#pragma once


#include <QtCharts>
#include <QtWidgets>

#include "../report/report_mocks.hpp"
#include "../PlatoonConfiguration/PlatoonVisual.hpp"
#include "../gui/window.hpp"


namespace mtobridge {
class SolverVisual : public QWidget {
	Q_OBJECT

	public:
		SolverVisual(QTabWidget *parent, PlatoonVisual* platoonVisualIn, Window* windowIn);
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

		QRadioButton* positiveMomentButton;
		QRadioButton* negativeMomentButton;
		QRadioButton* shearButton;
		QRadioButton* concernedButton;
		QRadioButton* criticalButton;

		QGraphicsView* truckVisual;
		QGraphicsView* bridgeVisual;

		PlatoonVisual* platoonVisual;
		Window* window;

		void createPage();
		void updatePage();
};
};  // namespace mtobridge
