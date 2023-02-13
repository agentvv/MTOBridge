#pragma once

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "../report/report_mocks.hpp"

namespace mtobridge{
class loader
{
    
public:
    static mtobridge::MockTruckT loadPlatoonConfiguration();
    static mtobridge::MockBridgeT loadBridgeConfiguration();
    static mtobridge::MockSolverT loadSolverConfiguration();
};
}

