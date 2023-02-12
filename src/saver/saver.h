#ifndef SAVER_H
#define SAVER_H

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "report_mocks.hpp"

namespace mtobridge{
class saver : public QWidget
{
    Q_OBJECT

public:
    saver(QWidget *parent = nullptr);
    ~saver();

    static void savePlatoonConfiguration(mtobridge::MockTruckT PlatoonT);
    static void saveBridgeConfiguration(mtobridge::MockBridgeT BridgeT);
    static void saveSolverConfiguration(mtobridge::MockSolverT SolverT);
    static void saveReport(mtobridge::MockReportT ReportT);


private slots:

};
}
#endif // SAVER_H
