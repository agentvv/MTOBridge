#include "saver.h"
#include "loader.h"
#include "./ui_saver.h"
#include <QDebug>

saver::saver(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::saver)
{
    ui->setupUi(this);

}


void saver::savePlatoonConfiguration(mtobridge::MockTruckT PlatoonT)
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Truck Configuration"), "",
        tr("MTOBridge (*.trk);;All Files (*)"));


    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

    QString straxleLoad;
    for(auto it = PlatoonT.axleLoad.begin();it!=PlatoonT.axleLoad.end();it++){
        straxleLoad = straxleLoad + QString::number(*it);
        straxleLoad.append(" ");
    }

    QString straxleSpacing;
    for(auto it = PlatoonT.axleSpacing.begin();it!=PlatoonT.axleSpacing.end();it++){
       straxleSpacing = straxleSpacing + QString::number(*it);
       straxleSpacing.append(" ");
    }


    QString output = straxleLoad + "\n" + straxleSpacing + "\n" + QString::number(PlatoonT.headway)+ "\n" + QString::number(PlatoonT.numberOfTrucks);


    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    out << output;
    }
}

void saver::saveBridgeConfiguration(mtobridge::MockBridgeT BridgeT)
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Bridge Configuration"), "",
        tr("MTOBridge (*.brg);;All Files (*)"));


    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

    QString strspanLength;
    for(auto it = BridgeT.spanLength.begin();it!=BridgeT.spanLength.end();it++){
        strspanLength = strspanLength + QString::number(*it);
        strspanLength.append(" ");
    }


    QString output = QString::number(BridgeT.numberSpans) + "\n" + strspanLength + "\n" + QString::number(BridgeT.concernedSection)+ "\n" + QString::number(BridgeT.discretizationLength);


    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    out << output;
    }
}

void saver::saveSolverConfiguration(mtobridge::MockSolverT SolverT)
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Solver Configuration"), "",
        tr("MTOBridge (*.slv);;All Files (*)"));


    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

    QString strForce;
    switch (SolverT.forceType)
        {
            case mtobridge::MockSolverT::POSITIVE_MOMENT:   strForce = "Positive Moment";
            case mtobridge::MockSolverT::NEGATIVE_MOMENT:   strForce = "Negative Moment";
            case mtobridge::MockSolverT::SHEAR:    strForce = "Shear";
            default:      strForce = "No data";
        }


    QString strSolver;
    switch (SolverT.solverType)
        {
            case mtobridge::MockSolverT::CONCERNED:   strSolver = "Concerned";
            case mtobridge::MockSolverT::CRITICAL:    strSolver = "Critical";
            default:      strSolver = "No data";
        }



    QString output = strForce + "\n" + strSolver;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    out << output;
    }
}


saver::~saver()
{
    delete ui;
}


void saver::on_saveTruck_clicked()
{
    mtobridge::MockTruckT temp;
    temp.axleLoad={1,2};
    temp.axleSpacing={1,2};
    temp.headway=4;
    temp.numberOfTrucks=2;

    savePlatoonConfiguration(temp);
}


void saver::on_loadTruck_clicked()
{
    loader l;
    mtobridge::MockTruckT temptruck = l.loadPlatoonConfiguration();

}



void saver::on_loadBridge_clicked()
{
    loader l;
    mtobridge::MockBridgeT tempbridge = l.loadBridgeConfiguration();
}


void saver::on_saveBridge_clicked()
{
    mtobridge::MockBridgeT temp;
    temp.numberSpans=2;
    temp.spanLength={1,2};
    temp.concernedSection=4;
    temp.discretizationLength=2;

    saveBridgeConfiguration(temp);

}


void saver::on_loadSolver_clicked()
{
    loader l;
    mtobridge::MockSolverT tempsolver = l.loadSolverConfiguration();
}


void saver::on_saveSolver_clicked()
{
    mtobridge::MockSolverT temp;
    temp.forceType=mtobridge::MockSolverT::POSITIVE_MOMENT;
    temp.solverType=mtobridge::MockSolverT::CONCERNED;

    saveSolverConfiguration(temp);
}


void saver::on_saveReport_clicked()
{


}

