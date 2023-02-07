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
        tr("Save Truck Data Format"), "",
        tr("Address Book (*.trk);;All Files (*)"));


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
//! [saveToFile() function part3]

//! [loadFromFile() function part1]
void saver::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("Address Book (*.trk);;All Files (*)"));
//! [loadFromFile() function part1]

//! [loadFromFile() function part2]
    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }
        QString temp;
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);

        in >> temp;
        qDebug() << temp;


//! [loadFromFile() function part2]

//! [loadFromFile() function part3]
        if (temp.isEmpty()) {
            QMessageBox::information(this, tr("No contacts in file"),
                tr("The file you are attempting to open contains no contacts."));
        }

        ui->labelName->setText("hello");
    }
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




