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
#include <QStringList>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "../report/report.hpp"
#include "../bridge/bridgeconfig.hpp"

namespace mtobridge{
class loader
{
    
public:
    static mtobridge::MockTruckT loadPlatoonConfiguration();
    static mtobridge::BridgeT loadBridgeConfiguration();
    static mtobridge::MockSolverT loadSolverConfiguration();
    static mtobridge::Report loadReportConfiguration();
};
}

