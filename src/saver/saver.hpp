#pragma once

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include <QFileDialog>
#include "../report/report.hpp"
#include "../bridge/bridgeconfig.hpp"

namespace mtobridge{
class saver 
{
public:

    static void savePlatoonConfiguration(mtobridge::MockTruckT PlatoonT);
    static void saveBridgeConfiguration(mtobridge::BridgeT BridgeT);
    static void saveSolverConfiguration(mtobridge::MockSolverT SolverT);
    static void saveSolverFigure(QGraphicsScene &scene);
    static void saveReport(mtobridge::Report ReportT);


};
}
