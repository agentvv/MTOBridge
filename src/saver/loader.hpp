#pragma once

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "util/data_types.hpp"
#include "../bridge/bridgeconfig.hpp"
#include <QCoreApplication>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

namespace mtobridge{
class loader
{
    
public:
    static mtobridge::MockTruckT loadPlatoonConfiguration();
    static mtobridge::BridgeT loadBridgeConfiguration();
    static mtobridge::MockSolverT loadSolverConfiguration();
};
}

