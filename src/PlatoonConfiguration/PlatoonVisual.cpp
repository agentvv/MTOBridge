#include "PlatoonVisual.hpp"

#include <cctype>
#include <iostream>
#include <sstream>
#include <QList>

#include "../saver/loader.hpp"
#include "../saver/saver.hpp"
#include "PlatoonConfiguration.hpp"

namespace mtobridge {
PlatoonVisual::PlatoonVisual(QWidget *parent) : QWidget(parent) {
  createPage();
}
PlatoonVisual::~PlatoonVisual() {}
//Initialize Brushes used for drawing
QBrush redBrush(Qt::red);
QBrush grayBrush(Qt::lightGray);
QBrush blackBrush(Qt::black);
QBrush whiteBrush(Qt::white);
QPen blackPen(Qt::black);

// Function for error checking Axle Load Input
void PlatoonVisual::validateLoadText(QString s) {
    QLineEdit *sender = static_cast<QLineEdit *>(this->sender());
    if (sender == nullptr || axleLoadErrorLabel == nullptr) {
      return;
    }
    int cursorPosition = 0;
    if (sender->text() != "" && 
        sender->validator()->validate(s, cursorPosition) ==
            QValidator::Invalid ||
        sender->validator()->validate(s, cursorPosition) ==
            QValidator::Intermediate) {
      sender->setStyleSheet("border: 1px solid red");
      axleLoadErrorLabel->setVisible(true);
  } else {
      sender->setStyleSheet("");
      axleLoadErrorLabel->setVisible(false);
  }
    
}
// Function for error checking Axle Spacing Input
void PlatoonVisual::validateSpacingText(QString s) {
    QLineEdit *sender = static_cast<QLineEdit *>(this->sender());
  if (sender == nullptr || axleSpacingErrorLabel == nullptr) {
      return;
    }
    int cursorPosition = 0;
    if (sender->text() != "" &&
        (sender->validator()->validate(s, cursorPosition) ==
            QValidator::Invalid ||
        sender->validator()->validate(s, cursorPosition) ==
            QValidator::Intermediate)) {
      sender->setStyleSheet("border: 1px solid red");
      axleSpacingErrorLabel->setVisible(true);
    } else {
      sender->setStyleSheet("");
      axleSpacingErrorLabel->setVisible(false);
    }
}
//Function for drawing extra text boxes when the Number Of Axles Spin Box is updated
void PlatoonVisual::numAxlesChanged(int i) {
  //Special case for program startup
  if (axleLoadList.size() == 0 && axleSpacingList.size() == 0) {
    for (int i = 0; i < 3; i++) {
      //Create new QLineEdit and Set Size
      QLineEdit *axleLoad = new QLineEdit(this->mInputWidget);
      axleLoad->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Maximum,QSizePolicy::Policy::Maximum));
      axleLoad->setMaximumSize(45, 20);
      //Connect new QLineEdit to the function that updates the platoon from user input
      QObject::connect(axleLoad, &QLineEdit::editingFinished, this,
                       &PlatoonVisual::platoonConfigured);
      //Add a QValidator to the new QLineEdit
      QDoubleValidator *axleLoadValidator = new QDoubleValidator(this->mInputWidget);
      axleLoadValidator->setRange(0.1, 1000, 1);
      axleLoad->setValidator(axleLoadValidator);
      QObject::connect(axleLoad, &QLineEdit::textChanged, this,
                       &PlatoonVisual::validateLoadText);
      //Place new QLineEdit on the layout
      this->inputLayout->addWidget(axleLoad, 3, axleLoadList.size() + 1);
      axleLoadList.append(axleLoad);
    }
    for (int i = 0; i < 2; i++) {
      //Create new QLineEdit and Set Size
      QLineEdit *axleSpacing = new QLineEdit(this->mInputWidget);
      axleSpacing->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Maximum,QSizePolicy::Policy::Maximum));
      axleSpacing->setMaximumSize(45, 20);
      // Connect new QLineEdit to the function that updates the platoon from user input
      QObject::connect(axleSpacing, &QLineEdit::editingFinished, this, &PlatoonVisual::platoonConfigured);
      // Add a QValidator to the new QLineEdit
      QDoubleValidator *axleSpacingValidator = new QDoubleValidator(this->mInputWidget);
      axleSpacingValidator->setRange(1.2, 20, 1);
      axleSpacing->setValidator(axleSpacingValidator);
      QObject::connect(axleSpacing, &QLineEdit::textChanged, this,
                       &PlatoonVisual::validateSpacingText);
      // Place new QLineEdit on the layout
      this->inputLayout->addWidget(axleSpacing, 4, axleSpacingList.size() + 1);
      axleSpacingList.append(axleSpacing);
    }
    setTabOrder(axleSpacingList.last(), mSaveButton);
    setTabOrder(mSaveButton, mLoadButton);
    return;
   }
  //Non-Special case for when Number Of Axles is updated
    int num = i - axleLoadList.size();
  //num > 0 means we are adding new boxes
  if (num > 0) {
      for (int i = 0; i < num; i++) {
        // Create new QLineEdit and Set Size
        QLineEdit *axleLoad = new QLineEdit(this->mInputWidget);
        axleLoad->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Maximum,QSizePolicy::Policy::Maximum));
        axleLoad->setMaximumSize(45, 20);
        // Connect new QLineEdit to the function that updates the platoon from user input
        QObject::connect(axleLoad, &QLineEdit::editingFinished, this,&PlatoonVisual::platoonConfigured);
        // Add a QValidator to the new QLineEdit
        QDoubleValidator *axleLoadValidator =
            new QDoubleValidator(this->mInputWidget);
        axleLoadValidator->setRange(0.1, 1000, 1);
        axleLoad->setValidator(axleLoadValidator);
        QObject::connect(axleLoad, &QLineEdit::textChanged, this,
                         &PlatoonVisual::validateLoadText);
        // Place new QLineEdit on the layout
        this->inputLayout->addWidget(axleLoad, 3, axleLoadList.size() + 1);
        setTabOrder(axleLoadList.last(), axleLoad);
        axleLoadList.append(axleLoad);
        // Create new QLineEdit and Set Size
        QLineEdit *axleSpacing = new QLineEdit(this->mInputWidget);
        axleSpacing->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Maximum,QSizePolicy::Policy::Maximum));
        axleSpacing->setMaximumSize(45, 20);
        // Connect new QLineEdit to the function that updates the platoon from user input
        QObject::connect(axleSpacing, &QLineEdit::editingFinished, this,&PlatoonVisual::platoonConfigured);
        // Add a QValidator to the new QLineEdit
        QDoubleValidator *axleSpacingValidator =
            new QDoubleValidator(this->mInputWidget);
        axleSpacingValidator->setRange(1.2, 20, 1);
        axleSpacing->setValidator(axleSpacingValidator);
        QObject::connect(axleSpacing, &QLineEdit::textChanged, this,
                         &PlatoonVisual::validateSpacingText);
        // Place new QLineEdit on the layout
        this->inputLayout->addWidget(axleSpacing, 4,
                                     axleSpacingList.size() + 1);
        setTabOrder(axleSpacingList.last(), axleSpacing);
        axleSpacingList.append(axleSpacing);
      }
      //realign any existing error labels
      this->inputLayout->removeWidget(axleLoadErrorLabel);
      this->inputLayout->addWidget(axleLoadErrorLabel, 3,
                                   axleLoadList.size() + 1);
      this->inputLayout->removeWidget(axleSpacingErrorLabel);
      this->inputLayout->addWidget(axleSpacingErrorLabel, 4,
                                   axleLoadList.size() + 1);
      setTabOrder(axleSpacingList.last(), mSaveButton);
      setTabOrder(mSaveButton, mLoadButton);
  } 
  //num < 0 means we are removing boxes
  else if (num < 0) {
      for (int i = 0; i > num; i--) {
        QLineEdit *victimLoad = axleLoadList.takeLast();
        this->inputLayout->removeWidget(victimLoad);
        QObject::disconnect(victimLoad, &QLineEdit::editingFinished, this,
                         &PlatoonVisual::platoonConfigured);
        delete victimLoad;

        QLineEdit *victimSpacing = axleSpacingList.takeLast();
        this->inputLayout->removeWidget(victimSpacing);
        QObject::disconnect(victimSpacing, &QLineEdit::editingFinished, this,
                            &PlatoonVisual::platoonConfigured);
        delete victimSpacing;
      }
  } 
  else {
    return;
  }
}

  //Creates a truck object
  QGraphicsItemGroup *PlatoonVisual::makeTruck() {
  std::vector<double> spacings = PlatoonConfiguration::getAxleSpacings();
  std::vector<double>::iterator it = spacings.begin();
  int length = 0;
  while (it != spacings.end()) {
    length += *it*5;
    it++;
  }
  blackPen.setWidth(1);
  truck = new QGraphicsItemGroup();

  truckHead = mSceneWidget->addRect(length*3/4, 0, length/4+10, 20, blackPen, redBrush);
  truckHead->setZValue(0);
  truckWindow = mSceneWidget->addRect(length*7/8+10, 3, length/10, 7, blackPen, whiteBrush);
  truckWindow->setZValue(1);
  truckBody = mSceneWidget->addRect(-10, 0, length*3/4+10, 20, blackPen, grayBrush);
  truckBody->setZValue(0);

  truck->addToGroup(truckHead);
  truck->addToGroup(truckWindow);
  truck->addToGroup(truckBody);

  int x = length;
  blackPen.setWidth(0);
  truckWheel = mSceneWidget->addEllipse(x, 18.5, 5, 5, blackPen, blackBrush);
  truckWheel->setZValue(1);
  truck->addToGroup(truckWheel);
  truckRim = mSceneWidget->addEllipse(x + 1, 19.5, 3, 3, blackPen, grayBrush);
  truckRim->setZValue(2);
  truck->addToGroup(truckRim);

  it = spacings.begin();
  while (it != spacings.end()) {
    x = x - (*it * 5);
    truckWheel = mSceneWidget->addEllipse(x, 18.5, 5, 5, blackPen, blackBrush);
    truckWheel->setZValue(1);
    truck->addToGroup(truckWheel);
    truckRim = mSceneWidget->addEllipse(x + 1, 19.5, 3, 3, blackPen, grayBrush);
    truckRim->setZValue(2);
    truck->addToGroup(truckRim);
    it++;
  }
  blackPen.setWidth(1);
  return truck;
  
}
//Keeps the visualization consistent when window is resized
void PlatoonVisual::resizeEvent(QResizeEvent *event)
{
  QWidget::resizeEvent(event);
  QRectF itemRect = mSceneWidget->itemsBoundingRect();
  QRectF PaddedRect(itemRect.left() - itemRect.width() * 0.1, itemRect.top() - itemRect.height() * 0.1,
    itemRect.width() * 1.2, itemRect.height() * 1.2);
  mSceneWidget->setSceneRect(PaddedRect);
  mViewWidget->fitInView(mSceneWidget->sceneRect(), Qt::KeepAspectRatio);
  mViewWidget->centerOn(mSceneWidget->sceneRect().center());
}
//Updates the data structure and creates the visualization when all inputs are valid
void PlatoonVisual::platoonConfigured() {
    //Checking for validity of inputs before proceeding
    for (auto *w : axleLoadList) {
        QString text = w->text();
        int cursorPosition = 0;
        if (w->validator()->validate(text, cursorPosition) ==
            QValidator::Invalid ||
        w->validator()->validate(text, cursorPosition) == 
            QValidator::Intermediate) {
        return;
     }
    }
    for (auto *w : axleSpacingList) {
        QString text = w->text();
        int cursorPosition = 0;
        if (w->validator()->validate(text, cursorPosition) ==
             QValidator::Invalid ||
            w->validator()->validate(text, cursorPosition) ==
             QValidator::Intermediate) {
        return;
     }
    }
     if (mHeadway->text() == "" || mNumberOfTrucks->text() == "") {
        return;
     }
   
  mSceneWidget->clear();
  
  blackPen.setWidth(2);
  QString axleLoads = "";
  QString axleSpacings = "";
  //retrieve axleLoad and spacing data from all individual QLineEdits
  for (auto *w : axleLoadList) {
       axleLoads += w->text();
       axleLoads += " ";
  }
  for (auto *w : axleSpacingList) {
       axleSpacings += w->text();
       axleSpacings += " ";
  }
  QString numTrucks = mNumberOfTrucks->text();
  QString headway = mHeadway->text();
  //Update data structure
  PlatoonConfiguration::updateAxleLoad(axleLoads);
  PlatoonConfiguration::updateAxleSpacing(axleSpacings);
  PlatoonConfiguration::updateNumberOfTrucks(numTrucks);
  PlatoonConfiguration::updateHeadway(headway);
  
  std::vector<double> spacings = PlatoonConfiguration::getAxleSpacings();
  std::vector<double>::iterator it = spacings.begin();
  //make as many trucks as necessary
  if (PlatoonConfiguration::getNumTrucks() > 0) {
       truck = makeTruck();
       mSceneWidget->clear();
       mSceneWidget->addItem(truck);
       truck->setPos(0, 0);
  }
  
  //add the trucks to the visualization and set their positions properly
  for (int i = 1; i < PlatoonConfiguration::getNumTrucks(); i++) {
        QGraphicsItemGroup *truck2 = makeTruck();
        mSceneWidget->addItem(truck2);
        int length = truck2->boundingRect().width();
        truck2->setPos((length - 20 + PlatoonConfiguration::getHeadway()*5) * i, 0);
        truck->setZValue(i+1);
  }
  //Centers the visualization on the trucks
  QRectF itemRect = mSceneWidget->itemsBoundingRect();
  QRectF PaddedRect(itemRect.left() - itemRect.width() * 0.1,itemRect.top() - itemRect.height() * 0.1,
                    itemRect.width() * 1.2, itemRect.height() * 1.2);
  mSceneWidget->setSceneRect(PaddedRect);
  mViewWidget->fitInView(mSceneWidget->sceneRect(), Qt::KeepAspectRatio);
  mViewWidget->centerOn(mSceneWidget->sceneRect().center());
  mSaveButton->setDisabled(false);
}
//Calls the save function when the save button is clicked
void PlatoonVisual::saveButtonClicked() {
  MockTruckT config;
  std::vector<double> axleLoadTemp = PlatoonConfiguration::getAxleLoads();
  std::vector<double> axleSpacingTemp = PlatoonConfiguration::getAxleSpacings();
  config.axleLoad =
      std::vector<double>{axleLoadTemp.begin(), axleLoadTemp.end()};
  config.axleSpacing =
      std::vector<double>{axleSpacingTemp.begin(), axleSpacingTemp.end()};
  config.headway = PlatoonConfiguration::getHeadway();
  config.numberOfTrucks = PlatoonConfiguration::getNumTrucks();
  saver::savePlatoonConfiguration(config);
}
// Calls the load function when the load button is clicked
void PlatoonVisual::loadButtonClicked() {
  MockTruckT config = loader::loadPlatoonConfiguration();

  PlatoonConfiguration::updateAxleSpacing(config.axleSpacing);
  PlatoonConfiguration::updateAxleLoad(config.axleLoad);
  PlatoonConfiguration::updateHeadway(config.headway);
  PlatoonConfiguration::updateNumberOfTrucks(config.numberOfTrucks);

  mNumberOfAxles->setValue(config.axleLoad.size());
  for (int i = 0; i < axleSpacingList.size(); i++) {
        auto spacing = QString::number(config.axleSpacing[i]);
        axleSpacingList[i]->setText(spacing);
  }

  for (int i = 0; i < axleLoadList.size(); i++) {
        auto load = QString::number(config.axleLoad[i]);
        axleLoadList[i]->setText(load);
  }

  mNumberOfTrucks->setValue(config.numberOfTrucks);
  mHeadway->setValue(config.headway);

  platoonConfigured();
}
//makes the Platoon tab
void PlatoonVisual::createPage() {
  this->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                  QSizePolicy::Policy::Expanding));
  auto *pageLayout = new QVBoxLayout();
  this->setLayout(pageLayout);

  // set up all inputs and layout
  {
    //Sets up layout and all widgets that go in it
    inputLayout = new QGridLayout();
    mInputWidget = new QWidget(this);
    mInputWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed));
    mInputWidget->setLayout(inputLayout);

    axleLoadList = {};
    axleSpacingList = {};

    mNumberOfTrucks = new QSpinBox(mInputWidget);
    mNumberOfTrucks->setMinimum(1);
    mNumberOfTrucks->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed,QSizePolicy::Policy::Fixed));
    mNumberOfTrucks->setMaximumSize(45, 20);

    mNumberOfTrucksLabel = new QLabel("Number of Trucks", mInputWidget);
    mNumberOfTrucksLabel->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed));

    mHeadway = new QDoubleSpinBox(mInputWidget);
    mHeadway->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum));
    mHeadway->setMaximumSize(45, 20);
    mHeadway->setMinimum(5);
    mHeadway->setDecimals(1);


    mHeadwayLabel = new QLabel("Truck Headway (Min 5m)", mInputWidget);
    mHeadwayLabel->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed));
   
    mNumberOfAxles = new QSpinBox(mInputWidget);
    mNumberOfAxles->setMinimum(3);
    mNumberOfAxles->setMaximum(17);
    mNumberOfAxles->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Maximum,QSizePolicy::Policy::Maximum));
    mNumberOfAxles->setMaximumSize(45, 20);

    mNumberOfAxlesLabel = new QLabel("Number of Axles (Max 17)", mInputWidget);
    mNumberOfAxlesLabel->setSizePolicy(
        QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed));

    mAxleLoadLabel = new QLabel("Axle Loads (Max 1000 kN) ", mInputWidget);
    mAxleLoadLabel->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed));

    axleLoadErrorLabel = new QLabel("", this->mInputWidget);
    axleLoadErrorLabel->setText(
        "One of your Axle Loads is unrealistically large/small!");
    axleLoadErrorLabel->setStyleSheet("color: red");
    axleLoadErrorLabel->setVisible(false);

    mAxleSpacingLabel = new QLabel("Axle Spacings (Min 1.2m)", mInputWidget);
    mAxleSpacingLabel->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed));
    axleSpacingErrorLabel = new QLabel("", this->mInputWidget);
    axleSpacingErrorLabel->setText(
        "Axles cannot be less than 1.2m apart!");
    axleSpacingErrorLabel->setStyleSheet("color: red");
    axleSpacingErrorLabel->setVisible(false);

    mSaveButton = new QPushButton("Save Truck Configuration", this);
    mSaveButton->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed));
    mSaveButton->setDisabled(true);

    mLoadButton = new QPushButton("Load Truck Configuration", this);
    mLoadButton->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed));

    numAxlesChanged(3);
    //adds everything to the layout
    inputLayout->addWidget(mNumberOfTrucksLabel, 0, 0);
    inputLayout->addWidget(mNumberOfTrucks, 0, 1);
    inputLayout->addWidget(mHeadwayLabel, 1, 0);
    inputLayout->addWidget(mHeadway, 1, 1);
    inputLayout->addWidget(mNumberOfAxlesLabel, 2, 0);
    inputLayout->addWidget(mNumberOfAxles, 2, 1);
    inputLayout->addWidget(mAxleLoadLabel, 3, 0);
    inputLayout->addWidget(axleLoadErrorLabel, 3,axleLoadList.size() + 1);
    inputLayout->addWidget(mAxleSpacingLabel, 4, 0);
    inputLayout->addWidget(axleSpacingErrorLabel, 4, axleLoadList.size() + 1);
    /*inputLayout->addWidget(mSaveButton, 5, 0);
    inputLayout->addWidget(mLoadButton, 6, 0);*/
    inputLayout->setHorizontalSpacing(0);
    
    mViewWidget = new QGraphicsView(this);
    mSceneWidget = new QGraphicsScene(this);
    mViewWidget->setScene(mSceneWidget);
    pageLayout->addWidget(mInputWidget);
    pageLayout->addWidget(mViewWidget);
    pageLayout->addWidget(mSaveButton);
    pageLayout->addWidget(mLoadButton);

    //Listens for any signals to call the appropriate functions
    QObject::connect(mNumberOfAxles, &QSpinBox::valueChanged, this,
                     &PlatoonVisual::numAxlesChanged);
    QObject::connect(mNumberOfTrucks, &QSpinBox::valueChanged, this,
                     &PlatoonVisual::platoonConfigured);
    QObject::connect(mHeadway, &QDoubleSpinBox::valueChanged, this,
                     &PlatoonVisual::platoonConfigured);
    QObject::connect(mSaveButton, &QPushButton::clicked, this,
                     &PlatoonVisual::saveButtonClicked);
    QObject::connect(mLoadButton, &QPushButton::clicked, this,
                     &PlatoonVisual::loadButtonClicked);

  }
}
//For loading from report instead of report button
void PlatoonVisual::loadConfiguration(MockTruckT config)
{
  PlatoonConfiguration::updateAxleSpacing(config.axleSpacing);
  PlatoonConfiguration::updateAxleLoad(config.axleLoad);
  PlatoonConfiguration::updateHeadway(config.headway);
  PlatoonConfiguration::updateNumberOfTrucks(config.numberOfTrucks);

  mNumberOfAxles->setValue(config.axleLoad.size());
  for (int i = 0; i < axleSpacingList.size(); i++)
  {
    auto spacing = QString::number(config.axleSpacing[i]);
    axleSpacingList[i]->setText(spacing);
  }

  for (int i = 0; i < axleLoadList.size(); i++)
  {
    auto load = QString::number(config.axleLoad[i]);
    axleLoadList[i]->setText(load);
  }

  mNumberOfTrucks->setValue(config.numberOfTrucks);
  mHeadway->setValue(config.headway);

  platoonConfigured();
}
};  // namespace mtobridge