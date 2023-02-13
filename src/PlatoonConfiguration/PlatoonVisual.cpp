#include <iostream>
#include <sstream>

#include "PlatoonConfiguration.hpp"
#include "PlatoonVisual.hpp"

namespace mtobridge {
QGraphicsView *mViewWidget;
QGraphicsScene *mSceneWidget;
PlatoonVisual::PlatoonVisual(QTabWidget *parent) : QWidget(parent) {
  createPage();
  parent->addTab(this, "Platoon");
}
PlatoonVisual::~PlatoonVisual() {}
void PlatoonVisual::buttonClicked() {
  mSceneWidget->clear();

  QBrush redBrush(Qt::red);
  QBrush grayBrush(Qt::lightGray);
  QBrush blackBrush(Qt::black);
  QBrush whiteBrush(Qt::white);
  QPen blackPen(Qt::black);
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
    mSceneWidget->addRect(90, 0, 30, 60, blackPen, redBrush);
    mSceneWidget->addRect(100, 3, 15, 20, blackPen, whiteBrush);
    mSceneWidget->addRect(0, 0, 90, 60, blackPen, grayBrush);
    int x = 105;
    mSceneWidget->addEllipse(x, 57, 5, 10, blackPen, blackBrush);
    while (it != spacings.end()) {
      x = x - (*it * 5);
      mSceneWidget->addEllipse(x, 57, 5, 10, blackPen, blackBrush);
      it++;
    }
  }
  for (int i = 1; i < PlatoonConfiguration::getNumTrucks(); i++) {
    mSceneWidget->addRect(90 + ((120 + PlatoonConfiguration::getHeadway()) * i),
                          0, 30,
                          60, blackPen, redBrush);
    mSceneWidget->addRect(
        100 + ((120 + PlatoonConfiguration::getHeadway()) * i), 3, 15,
                          20, blackPen, whiteBrush);
    mSceneWidget->addRect(0 + ((120 + PlatoonConfiguration::getHeadway()) * i),
                          0, 90, 60,
                          blackPen, grayBrush);
    it = spacings.begin();
    int x = (105 + ((120 + PlatoonConfiguration::getHeadway()) * i));
    mSceneWidget->addEllipse(x, 57, 5, 10, blackPen, blackBrush);
    while (it != spacings.end()) {
      x = x - (*it * 5);
      mSceneWidget->addEllipse(x, 57, 5, 10, blackPen, blackBrush);
      it++;
    }
  }
}

void PlatoonVisual::createPage() {
  this->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                   QSizePolicy::Policy::Expanding));
  auto *pageLayout = new QHBoxLayout();
  this->setLayout(pageLayout);

  // set up all inputs and layout
  {
    auto *inputLayout = new QGridLayout();
    mInputWidget = new QWidget(this);
    mInputWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                            QSizePolicy::Policy::Expanding));
    mInputWidget->setLayout(inputLayout);

    mNumberOfTrucks = new QLineEdit("3", mInputWidget);
    mNumberOfTrucksLabel = new QLabel("Number of Trucks", mInputWidget);

    mHeadway = new QLineEdit("5", mInputWidget);
    mHeadwayLabel = new QLabel("Truck Headway", mInputWidget);

    mAxleLoad = new QLineEdit("53.4 75.6 75.6 75.6 75.6", mInputWidget);
    mAxleLoadLabel = new QLabel("Axle Load", mInputWidget);

    mAxleSpacing = new QLineEdit("3.6576 1.2192 9.4488 1.2192", mInputWidget);
    mAxleSpacingLabel = new QLabel("Axle Spacing", mInputWidget);

    mButton = new QPushButton("Lock-In", this);
    mButton->setDisabled(false);

    inputLayout->addWidget(mNumberOfTrucksLabel, 0, 0);
    inputLayout->addWidget(mNumberOfTrucks, 0, 1);
    inputLayout->addWidget(mHeadwayLabel, 1, 0);
    inputLayout->addWidget(mHeadway, 1, 1);
    inputLayout->addWidget(mAxleLoadLabel, 2, 0);
    inputLayout->addWidget(mAxleLoad, 2, 1);
    inputLayout->addWidget(mAxleSpacingLabel, 3, 0);
    inputLayout->addWidget(mAxleSpacing, 3, 1);
    inputLayout->addWidget(mButton, 4, 0);

    mViewWidget = new QGraphicsView(this);
    mSceneWidget = new QGraphicsScene(this);

    mViewWidget->setScene(mSceneWidget);
    pageLayout->addWidget(mViewWidget);
    pageLayout->addWidget(mInputWidget);

    QObject::connect(mButton, &QPushButton::clicked, this,
                     &PlatoonVisual::buttonClicked);
  }
}
};  // namespace mtobridge