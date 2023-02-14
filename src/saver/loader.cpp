#include "loader.hpp"
#include "../bridge/bridgeconfig.hpp"

namespace mtobridge{

mtobridge::MockTruckT loader::loadPlatoonConfiguration()
{
  mtobridge::MockTruckT temptruck;
    QString fileName = QFileDialog::getOpenFileName(nullptr,
        "Load Truck Configuration", "",
        "MTOBridge (*.trk);;All Files (*)");
//! [loadFromFile() function part1]

//! [loadFromFile() function part2]
    if (fileName.isEmpty())
        return temptruck = { .axleLoad = { 53.4, 75.6, 75.6, 75.6, 75.6 }, .axleSpacing = { 3.6576, 1.2192, 9.4488, 1.2192 }, .numberOfTrucks = 3, .headway = 5 };
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(nullptr, "Unable to open file",
                file.errorString());
            return temptruck;
        }

        QString temp;
        QTextStream in(&file);
        temp = in.readAll();
        file.close();

//! [loadFromFile() function part3]

        
        QList<QString> strList = temp.split("\n", Qt::SkipEmptyParts);


        if (temp.isEmpty()) {
            QMessageBox::information(nullptr, "Nothing in file",
                "The file you are attempting to open contains nothing.");
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

        temptruck.numberOfTrucks = strList[3].toUInt();
        temptruck.headway = strList[2].toDouble();

    }
    return temptruck;
}

mtobridge::BridgeT loader::loadBridgeConfiguration()
{
  mtobridge::BridgeT tempbridge;

    QString fileName = QFileDialog::getOpenFileName(nullptr,
        "Load Bridge Configuration", "",
        "MTOBridge (*.brg);;All Files (*)");
//! [loadFromFile() function part1]

//! [loadFromFile() function part2]
    if (fileName.isEmpty())
        return tempbridge = { .numberSpans = 2, .spanLength = { 20, 20 }, .concernedSection = 10, .discretizationLength = 0.1 };
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(nullptr, "Unable to open file",
                file.errorString());
            return tempbridge;
        }

        QString temp;
        QTextStream in(&file);
        temp = in.readAll();
        file.close();
//! [loadFromFile() function part3]

      
        QList<QString> strList = temp.split("\n", Qt::SkipEmptyParts);


        if (temp.isEmpty()) {
            QMessageBox::information(nullptr, "Nothing in file",
                "The file you are attempting to open contains nothing.");
        }

        QList<QString> spanLengthList = strList[1].split(" ", Qt::SkipEmptyParts);

        for ( const auto& i : spanLengthList)
        {
            tempbridge.spanLength.push_back(i.toDouble());
        }


        tempbridge.numberSpans = strList[0].toInt();
        tempbridge.concernedSection = strList[2].toDouble();
        tempbridge.discretizationLength = strList[3].toDouble();

    }
    return tempbridge;
}

mtobridge::MockSolverT loader::loadSolverConfiguration()
{
  mtobridge::MockSolverT tempsolver;

    QString fileName = QFileDialog::getOpenFileName(nullptr,
        "Load Bridge Configuration", "",
        "MTOBridge (*.slv);;All Files (*)");
//! [loadFromFile() function part1]

//! [loadFromFile() function part2]
    if (fileName.isEmpty())
        return tempsolver = { .forceType = MockSolverT::POSITIVE_MOMENT, .solverType = MockSolverT::CONCERNED };
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(nullptr, "Unable to open file",
                file.errorString());
            return tempsolver;
        }

        QString temp;
        QTextStream in(&file);
        temp = in.readAll();
        file.close();

//! [loadFromFile() function part3]

       
        QList<QString> strList = temp.split("\n", Qt::SkipEmptyParts);


        if (temp.isEmpty()) {
            QMessageBox::information(nullptr, "Nothing in file",
                "The file you are attempting to open contains nothing.");
        }


        if (strList[0] ==  "Positive Moment") tempsolver.forceType = mtobridge::MockSolverT::POSITIVE_MOMENT;
        else if (strList[0] ==  "Negative Moment") tempsolver.forceType = mtobridge::MockSolverT::NEGATIVE_MOMENT;
        else tempsolver.forceType = mtobridge::MockSolverT::SHEAR;

        if (strList[1] ==  "Concerned") tempsolver.solverType = mtobridge::MockSolverT::CONCERNED;
        else tempsolver.solverType = mtobridge::MockSolverT::CRITICAL;

    }
    return tempsolver;
}
}
