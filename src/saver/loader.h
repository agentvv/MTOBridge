#ifndef LOADER_H
#define LOADER_H

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "report_mocks.hpp"


class loader : public QWidget
{
    Q_OBJECT
public:
    explicit loader(QWidget *parent = nullptr);

    mtobridge::MockTruckT loadPlatoonConfiguration();
    mtobridge::MockBridgeT loadBridgeConfiguration();
    mtobridge::MockSolverT loadSolverConfiguration();


public slots:


signals:

};

#endif // LOADER_H
