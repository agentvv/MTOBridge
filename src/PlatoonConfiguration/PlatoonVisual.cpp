#include "PlatoonVisual.hpp"

#include <cctype>
#include <iostream>
#include <sstream>

#include "../saver/loader.hpp"
#include "../saver/saver.hpp"
#include "PlatoonConfiguration.hpp"

namespace mtobridge {
PlatoonVisual::PlatoonVisual(QWidget *parent) : QWidget(parent) {
  createPage();
}
PlatoonVisual::~PlatoonVisual() {}
QBrush redBrush(Qt::red);
QBrush grayBrush(Qt::lightGray);
QBrush blackBrush(Qt::black);
QBrush whiteBrush(Qt::white);
QPen blackPen(Qt::black);

QGraphicsItemGroup *PlatoonVisual::makeTruck() {
  std::list<double> spacings = PlatoonConfiguration::getAxleSpacings();
  std::list<double>::iterator it = spacings.begin();
  int length = 0;
  while (it != spacings.end()) {
    length += *it*5;
    it++;
  }
  blackPen.setWidth(2);
  truck = new QGraphicsItemGroup();

  truckHead = mSceneWidget->addRect(length*3/4, 0, length/4+10, 40, blackPen, redBrush);
  truckHead->setZValue(0);

  truckWindow = mSceneWidget->addRect(length*7/8+10, 3, length/10, 14, blackPen, whiteBrush);
  truckWindow->setZValue(1);

  truckBody = mSceneWidget->addRect(-10, 0, length*3/4+10, 40, blackPen, grayBrush);
  truckBody->setZValue(0);

  truck->addToGroup(truckHead);
  truck->addToGroup(truckWindow);
  truck->addToGroup(truckBody);

  int x = length;
  truckWheel = mSceneWidget->addEllipse(x, 36, 10, 10, blackPen, blackBrush);
  truckWheel->setZValue(1);
  truck->addToGroup(truckWheel);
  truckRim = mSceneWidget->addEllipse(x+2, 38, 6, 6, blackPen, grayBrush);
  truckRim->setZValue(2);
  truck->addToGroup(truckRim);

  it = spacings.begin();
  while (it != spacings.end()) {
    x = x - (*it * 5);
    truckWheel = mSceneWidget->addEllipse(x, 36, 10, 10, blackPen, blackBrush);
    truck->addToGroup(truckWheel);
    truckRim = mSceneWidget->addEllipse(x + 2, 38, 6, 6, blackPen, grayBrush);
    truck->addToGroup(truckRim);
    it++;
  }
  return truck;
  
}
void PlatoonVisual::platoonConfigured() {
  if (mAxleSpacing->text() == "" || mAxleLoad->text() == "" ||
      mHeadway->text() == "" || mNumberOfTrucks->text() == "") {
       return;
  }
  if (!isdigit(mNumberOfTrucks->text().toStdString()[0]) ||!isdigit(mHeadway->text().toStdString()[0]) 
      || !isdigit(mAxleLoad->text().toStdString()[0]) || !isdigit(mAxleSpacing->text().toStdString()[0])) {
       return;
  }
  mSceneWidget->clear();
  
  blackPen.setWidth(2);

  QString axleLoads = mAxleLoad->text();
  QString axleSpacings = mAxleSpacing->text();
  QString numTrucks = mNumberOfTrucks->text();
  QString headway = mHeadway->text();

  PlatoonConfiguration::updateAxleLoad(axleLoads);
  PlatoonConfiguration::updateAxleSpacing(axleSpacings);
  PlatoonConfiguration::updateNumberOfTrucks(numTrucks);
  PlatoonConfiguration::updateHeadway(headway);

  std::list<double> spacings = PlatoonConfiguration::getAxleSpacings();
  std::list<double>::iterator it = spacings.begin();
  if (PlatoonConfiguration::getNumTrucks() > 0) {
       truck = makeTruck();
       mSceneWidget->clear();
       mSceneWidget->addItem(truck);
       truck->setPos(0, 0);
  }
  

  for (int i = 1; i < PlatoonConfiguration::getNumTrucks(); i++) {
        QGraphicsItemGroup *truck2 = makeTruck();
        mSceneWidget->addItem(truck2);
        int length = truck2->boundingRect().width();
        truck2->setPos((length - 20 + PlatoonConfiguration::getHeadway()*5) * i, 0);
        truck->setZValue(i+1);
  }
}
void PlatoonVisual::saveButtonClicked() {
  MockTruckT config;
  std::list<double> axleLoadTemp = PlatoonConfiguration::getAxleLoads();
  std::list<double> axleSpacingTemp = PlatoonConfiguration::getAxleSpacings();
  config.axleLoad =
      std::vector<double>{axleLoadTemp.begin(), axleLoadTemp.end()};
  config.axleSpacing =
      std::vector<double>{axleSpacingTemp.begin(), axleSpacingTemp.end()};
  config.headway = PlatoonConfiguration::getHeadway();
  config.numberOfTrucks = PlatoonConfiguration::getNumTrucks();
  saver::savePlatoonConfiguration(config);
}
void PlatoonVisual::loadButtonClicked() {
  MockTruckT config = loader::loadPlatoonConfiguration();

  QString spacings;
  std::vector<double>::iterator it = config.axleSpacing.begin();
  while (it != config.axleSpacing.end()) {
    spacings += QString::number(*it) + " ";
    it++;
  }
  PlatoonConfiguration::updateAxleSpacing(spacings);
  QString spacings2;
  std::vector<double>::iterator it2 = config.axleLoad.begin();
  while (it2 != config.axleLoad.end()) {
    spacings2 += QString::number(*it2) + " ";
    it2++;
  }

  PlatoonConfiguration::updateAxleLoad(spacings2);
  PlatoonConfiguration::updateHeadway(QString::number(config.headway));
  PlatoonConfiguration::updateNumberOfTrucks(
      QString::number(config.numberOfTrucks));

  mAxleSpacing->setText(spacings);
  mAxleLoad->setText(spacings2);
  mNumberOfTrucks->setText(QString::number(config.numberOfTrucks));
  mHeadway->setText(QString::number(config.headway));

  platoonConfigured();
}

void PlatoonVisual::createPage() {
  this->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                  QSizePolicy::Policy::Expanding));
  auto *pageLayout = new QVBoxLayout();
  this->setLayout(pageLayout);

  // set up all inputs and layout
  {
    auto *inputLayout = new QGridLayout();
    mInputWidget = new QWidget(this);
    mInputWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                            QSizePolicy::Policy::Expanding));
    mInputWidget->setLayout(inputLayout);

    mNumberOfTrucks = new QLineEdit("", mInputWidget);
    mNumberOfTrucksLabel = new QLabel("Number of Trucks", mInputWidget);

    mHeadway = new QLineEdit("", mInputWidget);
    mHeadwayLabel = new QLabel("Truck Headway", mInputWidget);

    mAxleLoad = new QLineEdit("", mInputWidget);
    mAxleLoadLabel = new QLabel("Axle Load", mInputWidget);

    mAxleSpacing = new QLineEdit("", mInputWidget);
    mAxleSpacingLabel = new QLabel("Axle Spacing", mInputWidget);

    mSaveButton = new QPushButton("Save Truck Configuration", this);
    mLoadButton = new QPushButton("Load Truck Configuration", this);

    inputLayout->addWidget(mNumberOfTrucksLabel, 0, 0);
    inputLayout->addWidget(mNumberOfTrucks, 0, 1);
    inputLayout->addWidget(mHeadwayLabel, 1, 0);
    inputLayout->addWidget(mHeadway, 1, 1);
    inputLayout->addWidget(mAxleLoadLabel, 2, 0);
    inputLayout->addWidget(mAxleLoad, 2, 1);
    inputLayout->addWidget(mAxleSpacingLabel, 3, 0);
    inputLayout->addWidget(mAxleSpacing, 3, 1);
    inputLayout->addWidget(mSaveButton, 4, 0);
    inputLayout->addWidget(mLoadButton, 5, 0);

    mViewWidget = new QGraphicsView(this);
    mSceneWidget = new QGraphicsScene(this);
    mViewWidget->setScene(mSceneWidget);
    pageLayout->addWidget(mInputWidget);
    pageLayout->addWidget(mViewWidget);

    QObject::connect(mNumberOfTrucks, &QLineEdit::editingFinished, this,
                     &PlatoonVisual::platoonConfigured);
    QObject::connect(mHeadway, &QLineEdit::editingFinished, this,
                     &PlatoonVisual::platoonConfigured);
    QObject::connect(mAxleLoad, &QLineEdit::editingFinished, this,
                     &PlatoonVisual::platoonConfigured);
    QObject::connect(mAxleSpacing, &QLineEdit::editingFinished, this,
                     &PlatoonVisual::platoonConfigured);
    QObject::connect(mSaveButton, &QPushButton::clicked, this,
                     &PlatoonVisual::saveButtonClicked);
    QObject::connect(mLoadButton, &QPushButton::clicked, this,
                     &PlatoonVisual::loadButtonClicked);

  }
}
};  // namespace mtobridge