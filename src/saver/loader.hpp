#pragma once

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "../report/report_mocks.hpp"
#include "../bridge/bridgeconfig.hpp"

namespace mtobridge{
class loader
{
    
public:
    static mtobridge::MockTruckT loadPlatoonConfiguration();
    static mtobridge::BridgeT loadBridgeConfiguration();
    static mtobridge::MockSolverT loadSolverConfiguration();
};
}

