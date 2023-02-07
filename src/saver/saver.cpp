#include "saver.h"
#include "./ui_saver.h"
#include <QDebug>

saver::saver(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::saver)
{
    ui->setupUi(this);

}


void saver::savePlatoonConfiguration(MockTruckT PlatoonT)
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

void saver::saveBridgeConfiguration(MockBridgeT BridgeT)
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

void saver::saveSolverConfiguration(MockSolverT SolverT)
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
            case MockSolverT::POSITIVE_MOMENT:   strForce = "Positive Moment";
            case MockSolverT::NEGATIVE_MOMENT:   strForce = "Negative Moment";
            case MockSolverT::SHEAR:    strForce = "Shear";
            default:      strForce = "No data";
        }


    QString strSolver;
    switch (SolverT.solverType)
        {
            case MockSolverT::CONCERNED:   strSolver = "Concerned";
            case MockSolverT::CRITICAL:    strSolver = "Critical";
            default:      strSolver = "No data";
        }



    QString output = strForce + "\n" + strSolver;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    out << output;
    }
}


//! [saveToFile() function part3]

//! [loadFromFile() function part1]
saver::MockTruckT saver::loadFromFile()
{
    MockTruckT temptruck;
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Truck Configuration"), "",
        tr("MTOBridge (*.trk);;All Files (*)"));
//! [loadFromFile() function part1]

//! [loadFromFile() function part2]
    if (fileName.isEmpty())
        return temptruck;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return temptruck;
        }

        QString temp;
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);

//! [loadFromFile() function part3]

        in >> temp;
        QList<QString> strList = temp.split("\n", Qt::SkipEmptyParts);


        if (temp.isEmpty()) {
            QMessageBox::information(this, tr("Nothing in file"),
                tr("The file you are attempting to open contains nothing."));
        }

        QList<QString> axleLoadList = strList[0].split(" ", Qt::SkipEmptyParts);
        QList<QString> axleSpaceList = strList[1].split(" ", Qt::SkipEmptyParts);



        for ( const auto& i : axleLoadList)
        {
            temptruck.axleLoad.push_back(i.toDouble());
        }

        for ( const auto& i : axleSpaceList)
        {
            temptruck.axleSpacing.push_back(i.toDouble());
        }

        temptruck.numberOfTrucks = strList[2].toDouble();
        temptruck.headway = strList[3].toDouble();

    }
    return temptruck;
}


saver::~saver()
{
    delete ui;
}


void saver::on_saveTruck_clicked()
{
    MockTruckT temp;
    temp.axleLoad={1,2};
    temp.axleSpacing={1,2};
    temp.headway=4;
    temp.numberOfTrucks=2;

    savePlatoonConfiguration(temp);
}


void saver::on_loadTruck_clicked()
{
    loadFromFile();
}





void saver::on_loadBridge_clicked()
{

}


void saver::on_saveBridge_clicked()
{
    MockBridgeT temp;
    temp.numberSpans=2;
    temp.spanLength={1,2};
    temp.concernedSection=4;
    temp.discretizationLength=2;

    saveBridgeConfiguration(temp);

}


void saver::on_loadSolver_clicked()
{

}


void saver::on_saveSolver_clicked()
{
    MockSolverT temp;
    temp.forceType=MockSolverT::POSITIVE_MOMENT;
    temp.solverType=MockSolverT::CONCERNED;

    saveSolverConfiguration(temp);
}


void saver::on_saveReport_clicked()
{


}

