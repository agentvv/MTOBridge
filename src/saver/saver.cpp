#include "saver.h"
#include "loader.h"
#include "./ui_saver.h"
#include <QDebug>
namespace mtobridge{

void saver::savePlatoonConfiguration(mtobridge::MockTruckT PlatoonT)
{
    QString fileName = QFileDialog::getSaveFileName(nullptr,
        tr("Save Truck Configuration"), "",
        tr("MTOBridge (*.trk);;All Files (*)"));


    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(nullptr, tr("Unable to open file"),
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
    QString fileName = QFileDialog::getSaveFileName(nullptr,
        tr("Save Bridge Configuration"), "",
        tr("MTOBridge (*.brg);;All Files (*)"));


    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(nullptr, tr("Unable to open file"),
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
    QString fileName = QFileDialog::getSaveFileName(nullptr,
        tr("Save Solver Configuration"), "",
        tr("MTOBridge (*.slv);;All Files (*)"));


    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(nullptr, tr("Unable to open file"),
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

void saver::saveReport(mtobridge::MockReportT ReportT)
{
    QString fileName = QFileDialog::getSaveFileName(nullptr,
        tr("Save Solver Configuration"), "",
        tr("MTOBridge (*.txt);;All Files (*)"));


    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(nullptr, tr("Unable to open file"),
                file.errorString());
            return;
        }

    QString inputheader = "Report\n*******\n*******\n*******\n[Platoon]\n";

    QString straxleLoad;
    for(auto it = ReportT.input.truckConfig.axleLoad.begin();it!=ReportT.input.truckConfig.axleLoad.end();it++){
        straxleLoad = straxleLoad + QString::number(*it);
        straxleLoad.append(" ");
    }

    QString straxleSpacing;
    for(auto it = ReportT.input.truckConfig.axleSpacing.begin();it!=ReportT.input.truckConfig.axleSpacing.end();it++){
       straxleSpacing = straxleSpacing + QString::number(*it);
       straxleSpacing.append(" ");
    }


    QString axleloadstr = "axleLoad = " + straxleLoad + "\n";
    QString axlespacestr = "axleSpacing = " + straxleSpacing+ "\n";
    QString headwaystr = "headway = " +  QString::number(ReportT.input.truckConfig.headway) + "\n";
    QString numoftruckstr = "numberofTrucks = " +  QString::number(ReportT.input.truckConfig.numberOfTrucks) + "\n";

    QString truckstr = axleloadstr + axlespacestr + headwaystr + numoftruckstr;


    QString breakLine1 = "\n*******\n[Bridge]\n";

    QString strspanLength;
    for(auto it = ReportT.input.bridgeConfig.spanLength.begin();it!=ReportT.input.bridgeConfig.spanLength.end();it++){
        strspanLength = strspanLength + QString::number(*it);
        strspanLength.append(" ");
    }


    QString numberspansstr = "numberSpans = " + QString::number(ReportT.input.bridgeConfig.numberSpans) + "\n";
    QString spanlengthstr = "spanLength = " + strspanLength + "\n";
    QString concernedsectionstr = "concernedSection = " +  QString::number(ReportT.input.bridgeConfig.concernedSection) + "\n";
    QString discretizationlengthstr = "discretizationLength = " +  QString::number(ReportT.input.bridgeConfig.discretizationLength) + "\n";

    QString bridgestr = numberspansstr + spanlengthstr + concernedsectionstr + discretizationlengthstr;

    QString breakLine2 = "\n*******\n[Solver]\n";



    QString strForce;
    switch (ReportT.input.solverConfig.forceType)
        {
            case mtobridge::MockSolverT::POSITIVE_MOMENT:   strForce = "Positive Moment";
            case mtobridge::MockSolverT::NEGATIVE_MOMENT:   strForce = "Negative Moment";
            case mtobridge::MockSolverT::SHEAR:    strForce = "Shear";
            default:      strForce = "No data";
        }


    QString strSolver;
    switch (ReportT.input.solverConfig.solverType)
        {
            case mtobridge::MockSolverT::CONCERNED:   strSolver = "Concerned";
            case mtobridge::MockSolverT::CRITICAL:    strSolver = "Critical";
            default:      strSolver = "No data";
        }

    QString forcetypestr = "forceType = " + strForce + "\n";
    QString solvertypestr = "solverType = " + strSolver + "\n";

    QString solverstr = forcetypestr + solvertypestr;

    QString resulstheader = "\n*******\n*******\nResults\n*******\n*******\n*******\n[Platoon]\n";


    QString criticalstr;
    if (strSolver == "Critical"){
        criticalstr = "critical section = " + QString::number(ReportT.results.criticalSection) + "\n";
    }


    QString strfirstaxleposition;
    for(auto it = ReportT.results.firstAxlePosition.begin();it!=ReportT.results.firstAxlePosition.end();it++){
        strfirstaxleposition = strfirstaxleposition + QString::number(*it);
        strfirstaxleposition.append(" ");
    }

    QString strfirstaxlepositionforce;
    for(auto it = ReportT.results.firstAxlePositionForceEnvelope.begin();it!=ReportT.results.firstAxlePositionForceEnvelope.end();it++){
        strfirstaxlepositionforce = strfirstaxlepositionforce + QString::number(*it);
        strfirstaxlepositionforce.append(" ");
    }


    QString output = inputheader + truckstr + breakLine1 + bridgestr + breakLine2 + solverstr + resulstheader + criticalstr + strfirstaxlepositionforce; + "\n" + strfirstaxlepositionforce;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    out << output;
    }
}

}
