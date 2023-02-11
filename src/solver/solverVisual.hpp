#pragma once


#include <QtCharts>
#include <QtWidgets>


namespace mtobridge {
class SolverVisual : public QWidget {
	Q_OBJECT

	public:
		SolverVisual(QTabWidget *parent);
		~SolverVisual();

		void visualize();

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

		void createPage();
};
};  // namespace mtobridge
