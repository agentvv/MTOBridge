#ifndef SAVER_H
#define SAVER_H

#include <QWidget>
#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "report_mocks.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class saver;
             }
QT_END_NAMESPACE

class saver : public QWidget
{
    Q_OBJECT

public:
    saver(QWidget *parent = nullptr);
    ~saver();


public slots:
    void savePlatoonConfiguration(mtobridge::MockTruckT PlatoonT);
    void saveBridgeConfiguration(mtobridge::MockBridgeT BridgeT);
    void saveSolverConfiguration(mtobridge::MockSolverT SolverT);


private slots:
    void on_saveTruck_clicked();
    void on_loadTruck_clicked();
    void on_loadBridge_clicked();
    void on_saveBridge_clicked();
    void on_loadSolver_clicked();
    void on_saveSolver_clicked();
    void on_saveReport_clicked();

private:
    Ui::saver *ui;
};
#endif // SAVER_H
