#include "loader.hpp"

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
        return temptruck;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(nullptr, "Unable to open file",
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

        temptruck.numberOfTrucks = strList[2].toUInt();
        temptruck.headway = strList[3].toDouble();

    }
    return temptruck;
}

mtobridge::MockBridgeT loader::loadBridgeConfiguration()
{
    mtobridge::MockBridgeT tempbridge;

    QString fileName = QFileDialog::getOpenFileName(nullptr,
        "Load Bridge Configuration", "",
        "MTOBridge (*.brg);;All Files (*)");
//! [loadFromFile() function part1]

//! [loadFromFile() function part2]
    if (fileName.isEmpty())
        return tempbridge;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(nullptr, "Unable to open file",
                file.errorString());
            return tempbridge;
        }

        QString temp;
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);

//! [loadFromFile() function part3]

        in >> temp;
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


        tempbridge.numberSpans = strList[0].toUInt();
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
        return tempsolver;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(nullptr, "Unable to open file",
                file.errorString());
            return tempsolver;
        }

        QString temp;
        QTextStream in(&file);

//! [loadFromFile() function part3]

        temp = in.readAll();
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
