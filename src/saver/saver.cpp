#include "saver.hpp"
#include "util/data_types.hpp"
#include "../bridge/bridgeconfig.hpp"

//! The following code is responsible for saving the different data types in MTOBridge.
//! These incldue the truck, bridge and the solver configuration.
namespace mtobridge{


//! savePlatoonConfiguration takes in an input of a truck object and saves the data to a text file in a specific format 
void saver::savePlatoonConfiguration(mtobridge::MockTruckT PlatoonT)
{
//! Used custom extensions which would allow easier navigation as well as loading 
    QString fileName = QFileDialog::getSaveFileName(nullptr,
        "Save Truck Configuration", "",
        "MTOBridge (*.trk);;All Files (*)");

//! Check to see if the file is empty and it can be opened
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(nullptr, "Unable to open file",
                file.errorString());
            return;
        }

//! The truck object has four fields which include axleLoad, axleSpacing, headway and # of truck. 
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


    QTextStream out(&file);
    out << output;
    file.close();
    }
}

//! saveBridgeConfiguration takes in an input of a bridge object and saves the data to a text file in a specific format 
void saver::saveBridgeConfiguration(mtobridge::BridgeT BridgeT) {
//! Used custom extensions which would allow easier navigation as well as loading
    QString fileName = QFileDialog::getSaveFileName(nullptr,
        "Save Bridge Configuration", "",
        "MTOBridge (*.brg);;All Files (*)");

//! Check to see if the file is empty and it can be opened
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(nullptr, "Unable to open file",
                file.errorString());
            return;
        }

//! The bridge object has four fields which include # of spans, spanLength, concernedSection and discretizationLength. 
    QString strspanLength;
    for(auto it = BridgeT.spanLength.begin();it!=BridgeT.spanLength.end();it++){
        strspanLength = strspanLength + QString::number(*it);
        strspanLength.append(" ");
    }


    QString output = QString::number(BridgeT.numberSpans) + "\n" + strspanLength + "\n" + QString::number(BridgeT.concernedSection)+ "\n" + QString::number(BridgeT.discretizationLength);


    QTextStream out(&file);
    out << output;
    file.close();
    }
}


//! saveSolverConfiguration takes in an input of a solver object and saves the
//! data to a text file in a specific format
void saver::saveSolverConfiguration(mtobridge::MockSolverT SolverT) {
    //! Used custom extensions which would allow easier navigation as well as
    //! loading
    QString fileName =
        QFileDialog::getSaveFileName(nullptr, "Save Solver Configuration", "",
                                     "MTOBridge (*.slv);;All Files (*)");

    //! Check to see if the file is empty and it can be opened
    if (fileName.isEmpty())
    return;
    else {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(nullptr, "Unable to open file",
                                 file.errorString());
        return;
    }
    //! The solver object has two feilds which include forceType and solverType
    //! both of which are enums.
    QString strForce;
    switch (SolverT.forceType) {
        case mtobridge::MockSolverT::POSITIVE_MOMENT:
          strForce = "Positive Moment";
          break;
        case mtobridge::MockSolverT::NEGATIVE_MOMENT:
          strForce = "Negative Moment";
          break;
        case mtobridge::MockSolverT::SHEAR:
          strForce = "Shear";
          break;
        default:
          strForce = "No data";
    }

    QString strSolver;
    switch (SolverT.solverType) {
        case mtobridge::MockSolverT::CONCERNED:
          strSolver = "Concerned";
          break;
        case mtobridge::MockSolverT::CRITICAL:
          strSolver = "Critical";
          break;
        default:
          strSolver = "No data";
    }

    QString output = strForce + "\n" + strSolver;

    QTextStream out(&file);
    out << output;
    file.close();
    }
}

void saver::saveSolverFigure(QGraphicsScene &scene) {
    QString filePath = QFileDialog::getSaveFileName(
        nullptr, "Save File As", "", "PNG Files (*.png);;All Files (*)");

    if (filePath.isEmpty()) {
        qDebug() << "No file selected.";
        return;
    }

    // Get the scene's bounding rect
    QRectF boundingRect = scene.itemsBoundingRect();

    // Create a QImage object based on the bounding rect's dimensions
    QImage image(boundingRect.width(), boundingRect.height(),
                    QImage::Format_ARGB32);
    image.fill(Qt::white);

    // Create a QPainter and render the scene onto the QImage
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene.render(&painter);

    // Save the QImage as a PNG file
    bool saveSuccess = image.save(filePath, "PNG");

    if (saveSuccess) {
        qDebug() << "Image saved successfully!";
    } else {
        qDebug() << "Failed to save image.";
    }
}

//! saveReport takes in an input of a report object and saves the data to a text file in a specific format 
//! This is the main function for displaying the actual results of the calculation. 
//! The report object file is made up of the truck, bridge and solver objects along with the results.
void saver::saveReport(mtobridge::Report ReportT)
{
    QString fileName = QFileDialog::getSaveFileName(nullptr,
        "Save Solver Configuration", "",
        "MTOBridge (*.txt);;All Files (*)");

//! Check to see if the file is empty and it can be opened
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(nullptr, "Unable to open file",
                file.errorString());
            return;
        }
//! The code first outputs the data for each input object including truck, bridge and the solver. 
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
    QString concernedSectionStr =
        QString::number(ReportT.input.bridgeConfig.concernedSection);
    if (!concernedSectionStr.isEmpty()) {
        concernedSectionStr =
            "concernedSection = " +
            QString::number(ReportT.input.bridgeConfig.concernedSection) + "\n";
    }
    
    QString discretizationlengthstr = "discretizationLength = " +  QString::number(ReportT.input.bridgeConfig.discretizationLength) + "\n";

    QString bridgestr = numberspansstr + spanlengthstr + concernedSectionStr + discretizationlengthstr;

    QString breakLine2 = "\n*******\n[Solver]\n";



    QString strForce;
    switch (ReportT.input.solverConfig.forceType)
        {
            case mtobridge::MockSolverT::POSITIVE_MOMENT:
                strForce = "Positive Moment";
                break;
            case mtobridge::MockSolverT::NEGATIVE_MOMENT:
                strForce = "Negative Moment";
                break;
            case mtobridge::MockSolverT::SHEAR:
                strForce = "Shear";
                break;
            default:
                strForce = "No data";
        }


    QString strSolver;
    switch (ReportT.input.solverConfig.solverType)
        {
            case mtobridge::MockSolverT::CONCERNED:
                strSolver = "Concerned";
                break;
            case mtobridge::MockSolverT::CRITICAL:
                strSolver = "Critical";
                break;
            default:
                strSolver = "No data";
        }

    QString forcetypestr = "forceType = " + strForce + "\n";
    QString solvertypestr = "solverType = " + strSolver + "\n";

    QString solverstr = forcetypestr + solvertypestr;

//! The code then outputs the data for the actual result. 

    QString resulstheader = "\n*******\n[Results]\n";


    QString criticalstr;
    if (strSolver == "Critical") {
            criticalstr = "critical section of " + strForce + " = " +
                          QString::number(ReportT.results.criticalSection) +
                          "\n";
    } else {
            criticalstr = "concerned section = " +
                          QString::number(ReportT.results.criticalSection) +
                          "\n";
    }

    QString maxForce = "Maximum " + strForce + " at " + strSolver +
               "section = " + QString::number(ReportT.results.maxForce) + "\n";

    QString stroutputheader = strForce + " at " + strSolver + "\n";

    QString strfirstaxleposition = "First Axle Position, Response\n";
    for (int i = 0; i < ReportT.results.firstAxlePosition.size(); i++)
    {
      strfirstaxleposition += QString("%1, %2\n")
        .arg(ReportT.results.firstAxlePosition[i])
        .arg(ReportT.input.solverConfig.solverType == MockSolverT::CONCERNED ? 
          ReportT.results.forceConcernedSection[i] : 
          ReportT.results.forceCriticalSection[i]);
    }


    QString envelope;
    if (strSolver == "Critical") {
      QString envelopeheader =
          "\n*******\n[Results]\n" + strForce + "envelope\n";
      envelope = envelopeheader + "Envelope (Section, Response)\n";
      for (int i = 0; i < ReportT.results.sections.size(); i++)
      {
          envelope += QString("%1, %2\n")
              .arg(ReportT.results.sections[i])
              .arg(ReportT.results.forceEnvelope[i]);
      }
    }

    QString output = inputheader + truckstr + breakLine1 + bridgestr + breakLine2 + solverstr 
        + resulstheader + criticalstr +
                     maxForce + resulstheader +
                     stroutputheader +  strfirstaxleposition + envelope + "\n";

    QTextStream out(&file);
    out << output;
    file.close();
    }
}

}
