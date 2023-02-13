#ifndef SAVER_H
#define SAVER_H

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "../report/report.hpp"

namespace mtobridge{
class saver 
{
public:

    static void savePlatoonConfiguration(mtobridge::MockTruckT PlatoonT);
    static void saveBridgeConfiguration(mtobridge::MockBridgeT BridgeT);
    static void saveSolverConfiguration(mtobridge::MockSolverT SolverT);
    static void saveReport(mtobridge::Report ReportT);


};
}
#endif // SAVER_H
