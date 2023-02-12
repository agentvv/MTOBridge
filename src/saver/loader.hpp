#ifndef LOADER_H
#define LOADER_H

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "report_mocks.hpp"

namespace mtobridge{
class loader
{
    
public:


    mtobridge::MockTruckT loadPlatoonConfiguration();
    mtobridge::MockBridgeT loadBridgeConfiguration();
    mtobridge::MockSolverT loadSolverConfiguration();

};
}
#endif // LOADER_H
