#ifndef LOADER_H
#define LOADER_H

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "report_mocks.hpp"

namespace mtobridge{
class loader : public QWidget
{
    Q_OBJECT
public:


    mtobridge::MockTruckT loadPlatoonConfiguration();
    mtobridge::MockBridgeT loadBridgeConfiguration();
    mtobridge::MockSolverT loadSolverConfiguration();


public slots:


signals:

};
}
#endif // LOADER_H
