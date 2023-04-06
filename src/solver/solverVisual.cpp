#include "solverVisual.hpp"

#include "../PlatoonConfiguration/PlatoonConfiguration.hpp"
#include "../engine/engine.hpp"
#include "../saver/loader.hpp"
#include "../saver/saver.hpp"
#include "solver.hpp"
#include <math.h>

namespace mtobridge {
//Function triggered when a mouse button is released on the force response chart
void ChartView::mouseReleaseEvent(QMouseEvent* event) {
  //Get the SolverVisual object that this chart is in
  SolverVisual* solver = (SolverVisual*)this->parent()->parent()->parent()->parent();

  //Ignore the input if the animation is not paused
  auto status = solver->animationStatus;
  if (status == Paused || status == AtBeginning || status == AtEnd) {
    //Get chart x coordinate where mouse button was released
    //Mapping taken from https://stackoverflow.com/questions/44067831/get-mouse-coordinates-in-qchartviews-axis-system
    double x = this->chart()->mapToValue(this->chart()->mapFromScene(this->mapToScene(event->pos().x(), 0))).x();

    //Calculate and set the truck position based on the chart x coordinate
    solver->setTruckPosition(solver->animationMin + x * PIXELS_PER_METER);

    //Enable or disable animation buttons based on new truck position
    if (solver->truckGroup->x() == solver->animationMax) {
      solver->animationStatus = AtEnd;
      solver->nextFrameButton->setDisabled(true);
      solver->lastFrameButton->setDisabled(true);
      solver->backFrameButton->setDisabled(false);
      solver->firstFrameButton->setDisabled(false);
      solver->animationButton->setText("Restart");
    }
    else if (solver->truckGroup->x() == solver->animationMin) {
      solver->animationStatus = AtBeginning;
      solver->backFrameButton->setDisabled(true);
      solver->firstFrameButton->setDisabled(true);
      solver->nextFrameButton->setDisabled(false);
      solver->lastFrameButton->setDisabled(false);
      solver->animationButton->setText("Play");
    }
    else {
      solver->animationStatus = Paused;
      solver->backFrameButton->setDisabled(false);
      solver->firstFrameButton->setDisabled(false);
      solver->nextFrameButton->setDisabled(false);
      solver->lastFrameButton->setDisabled(false);
      solver->animationButton->setText("Play");
    }
  }
  //Trigger QChartView mouseReleaseEvent (which we initially overrode) to avoid potential issues
  QChartView::mouseReleaseEvent(event);
}

//The slot triggered when an error is encountered
void SolverVisual::errorOccurred(QString error) {
  //Display the error to the user
  QMessageBox::critical(this, QString("Error!"), error);
}

//Initial creation of the UI page
void SolverVisual::createPage() {
  //Set overall page layout
  setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                            QSizePolicy::Policy::Expanding));
  QVBoxLayout* pageLayout = new QVBoxLayout();
  setLayout(pageLayout);

  //Create widget for the top half of the page (results charts and settings buttons)
  QWidget* topHalf = new QWidget(this);
  QHBoxLayout* topHalfLayout = new QHBoxLayout();
  topHalf->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                     QSizePolicy::Policy::Expanding));
  topHalf->setLayout(topHalfLayout);

  //Set up result charts
  mChartTabWidget = new QTabWidget(this);
  mChart = new QChart();
  mChart->legend()->hide();
  mChart->createDefaultAxes();
  mChartView = new ChartView(mChart, mChartTabWidget);
  mChartView->setRenderHint(QPainter::Antialiasing);
  mChartView->resize(300, 300);
  mChartView->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                        QSizePolicy::Policy::Expanding));
  mChartTabWidget->addTab(mChartView, "Force Response");
  mEnvelopeChart = new QChart();
  mEnvelopeChart->legend()->hide();
  mEnvelopeChart->createDefaultAxes();
  mEnvelopeChartView = new QChartView(mEnvelopeChart, nullptr);
  mEnvelopeChartView->setRenderHint(QPainter::Antialiasing);
  mEnvelopeChartView->resize(300, 300);
  mEnvelopeChartView->setSizePolicy(QSizePolicy(
      QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
  mChartTabWidget->addTab(mEnvelopeChartView, "Force Envelope");
  //Set force envelope chart as not shown
  mChartTabWidget->setTabVisible(1, false);
  topHalfLayout->addWidget(mChartTabWidget);

  //Create input widget group that will contain all settings buttons
  QVBoxLayout* inputLayout = new QVBoxLayout();
  QWidget* mInputWidget = new QWidget(this);
  mInputWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                          QSizePolicy::Policy::Expanding));
  mInputWidget->setLayout(inputLayout);
  mInputWidget->setFixedWidth(200);

  //Create force response settings buttons
  this->forceSettingGroup = new QGroupBox("Force Response", this);
  inputLayout->addWidget(this->forceSettingGroup);
  QVBoxLayout* forceBox = new QVBoxLayout;
  this->forceSettingGroup->setLayout(forceBox);
  positiveMomentButton = new QRadioButton("Positive Moment");
  positiveMomentButton->setChecked(true);
  QObject::connect(positiveMomentButton, &QPushButton::clicked, this, [&]() {
    //When positiveMomentButton is clicked, update the current force response type and update the UI elements to match
    Solver::updateForceType("Positive Moment");
    updatePage();
    });
  forceBox->addWidget(positiveMomentButton);
  negativeMomentButton = new QRadioButton("Negative Moment");
  negativeMomentButton->setEnabled(false);
  QObject::connect(negativeMomentButton, &QPushButton::clicked, this, [&]() {
    //When negativeMomentButton is clicked, update the current force response type and update the UI elements to match
    Solver::updateForceType("Negative Moment");
    updatePage();
    });;
  forceBox->addWidget(negativeMomentButton);
  shearButton = new QRadioButton("Shear");
  QObject::connect(shearButton, &QPushButton::clicked, this, [&]() {
    //When shearButton is clicked, update the current force response type and update the UI elements to match
    Solver::updateForceType("Shear");
    updatePage();
    });
  forceBox->addWidget(shearButton);
  forceBox->addStretch(1);
  this->forceSettingGroup->setFixedHeight(100);

  //Create solver type settings buttons
  this->solverSettingGroup = new QGroupBox("Solver Type", this);
  inputLayout->addWidget(this->solverSettingGroup);
  QVBoxLayout* solverBox = new QVBoxLayout;
  this->solverSettingGroup->setLayout(solverBox);
  concernedButton = new QRadioButton("Concerned Section");
  concernedButton->setChecked(true);
  QObject::connect(concernedButton, &QPushButton::clicked, this, [&]() {
    //When concernedButton is clicked, update the current solver type and update the UI elements to match
    Solver::updateSolverType("Concerned Section");
    updatePage();
    });
  solverBox->addWidget(concernedButton);
  criticalButton = new QRadioButton("Critical Section");
  QObject::connect(criticalButton, &QPushButton::clicked, this, [&]() {
    //When concernedButton is clicked, update the current solver type and update the UI elements to match
    Solver::updateSolverType("Critical Section");
    updatePage();
    });
  solverBox->addWidget(criticalButton);
  solverBox->addStretch(1);
  this->solverSettingGroup->setFixedHeight(80);

  //Create calculate button and connect it being clicked to the calculateClicked() function
  this->calculateButton = new QPushButton("Initialising...", this);
  this->calculateButton->setDisabled(true);
  QObject::connect(this->calculateButton, &QPushButton::clicked, this, &SolverVisual::calculateClicked);
  inputLayout->addWidget(calculateButton);

  //Create button hold timer that will be used for backFrame and forwardFrame buttons
  this->buttonHoldTimer = new QTimer(this);
  this->buttonHoldTimer->setInterval(BUTTON_HOLD_TIME);
  this->buttonHoldTimer->setSingleShot(true);

  //Set initial animation status
  this->animationStatus = NotLoaded;

  //Crate animation button group widget
  QWidget* animationWidget = new QWidget(this);
  QHBoxLayout* animationLayout = new QHBoxLayout();
  animationLayout->setSpacing(0);
  animationWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
  animationWidget->setLayout(animationLayout);

  //Create skip to first frame button
  this->firstFrameButton = new QPushButton("<<", this);
  this->firstFrameButton->setDisabled(true);
  this->firstFrameButton->setFixedWidth(25);
  QObject::connect(this->firstFrameButton, &QPushButton::clicked, this, [&]() {
    //When firstFrameButton is clicked, jump to the first frame of the animation and enable or disable buttons appropriately
    this->setTruckPosition(this->animationMin);
    this->animationStatus = AtBeginning;
    this->backFrameButton->setDisabled(true);
    this->firstFrameButton->setDisabled(true);
    this->nextFrameButton->setDisabled(false);
    this->lastFrameButton->setDisabled(false);
    this->animationButton->setText("Play");
    });

  //Create backFrame button
  this->backFrameButton = new QPushButton("<", this);
  this->backFrameButton->setDisabled(true);
  this->backFrameButton->setFixedWidth(25);
  QObject::connect(this->backFrameButton, &QPushButton::pressed, this, [&]() {
    //When backFrameButton is pressed, move the animation back by one frame
    if (moveFrames(-1)) {
      //We are not yet at the beginning of the animation, start the button hold timer to see if the button is being held down
      if (this->animationStatus == AtEnd) {
        //Update UI elements if we were at the end of the animation
        this->animationStatus = Paused;
        this->nextFrameButton->setDisabled(false);
        this->lastFrameButton->setDisabled(false);
        this->animationButton->setText("Play");
      }
      this->buttonHoldTimer->start();
      QObject::connect(this->buttonHoldTimer, &QTimer::timeout, this, [&]() {
        //This will trigger if the button is still being held down after BUTTON_HOLD_TIME miliseconds, start the animation playing backwards
        this->animationStatus = RunningBackward;
        this->animateBackward();
        });
    }
    else {
      //We've hit the beginning of the animation, set UI elements appropriately
      this->animationStatus = AtBeginning;
      this->backFrameButton->setDisabled(true);
      this->firstFrameButton->setDisabled(true);
    }
    });
  QObject::connect(this->backFrameButton, &QPushButton::released, this, [&]() {
    //The backFrameButton is released, stop the button hold timer and pause any current animation
    this->buttonHoldTimer->disconnect();
    if (this->buttonHoldTimer->isActive()) {
      this->buttonHoldTimer->stop();
    }
    else if (this->animationStatus == RunningBackward) {
      this->animationStatus = Paused;
    }
    });


  //Create animation play/pause button
  this->animationButton = new QPushButton("Play", this);
  this->animationButton->setDisabled(true);
  this->animationButton->setFixedWidth(60);
  QObject::connect(this->animationButton, &QPushButton::clicked, this, [&]() {
    //When the animation button is clicked, perform actions based on the current animation status
    switch (this->animationStatus) {
    case RunningBackward:
    case RunningForward:
      //Pause the current running animation
      this->animationStatus = Paused;
      this->backFrameButton->setDisabled(false);
      this->firstFrameButton->setDisabled(false);
      this->nextFrameButton->setDisabled(false);
      this->lastFrameButton->setDisabled(false);
      this->animationButton->setText("Play");
      break;
    case AtEnd:
      //Reset the animation to the first frame
      this->setTruckPosition(this->animationMin);
      //This is intended to roll over into the next case statements
    case Paused:
    case AtBeginning:
      //Start the animation running forward from the current animation frame
      this->animationStatus = RunningForward;
      this->backFrameButton->setDisabled(true);
      this->firstFrameButton->setDisabled(true);
      this->nextFrameButton->setDisabled(true);
      this->lastFrameButton->setDisabled(true);
      this->animationButton->setText("Pause");
      this->animateForward();
      break;
    }
    });


  //Create next frame button
  this->nextFrameButton = new QPushButton(">", this);
  this->nextFrameButton->setDisabled(true);
  this->nextFrameButton->setFixedWidth(25);
  QObject::connect(this->nextFrameButton, &QPushButton::pressed, this, [&]() {
    //When nextFrameButton is pressed, move the animation forward by one frame
    if (moveFrames(1)) {
      //We are not yet at the end of the animation, start the button hold timer to see if the button is being held down
      if (this->animationStatus == AtBeginning) {
        //Update UI elements if we were at the beginning of the animation
        this->animationStatus = Paused;
        this->backFrameButton->setDisabled(false);
        this->firstFrameButton->setDisabled(false);
      }
      this->buttonHoldTimer->start();
      QObject::connect(this->buttonHoldTimer, &QTimer::timeout, this, [&]() {
        //This will trigger if the button is still being held down after BUTTON_HOLD_TIME miliseconds, start the animation playing forwards
        this->animationStatus = RunningForward;
        this->animateForward();
        });
    }
    else {
      //We've hit the end of the animation, set UI elements appropriately
      this->animationStatus = AtEnd;
      this->nextFrameButton->setDisabled(true);
      this->lastFrameButton->setDisabled(true);
      this->animationButton->setText("Restart");
    }
    });
  QObject::connect(this->nextFrameButton, &QPushButton::released, this, [&]() {
    //The nextFrameButton is released, stop the button hold timer and pause any current animation
    this->buttonHoldTimer->disconnect();
    if (this->buttonHoldTimer->isActive()) {
      this->buttonHoldTimer->stop();
    }
    else if (this->animationStatus == RunningForward) {
      this->animationStatus = Paused;
    }
    });


  //Create skip to last frame button
  this->lastFrameButton = new QPushButton(">>", this);
  this->lastFrameButton->setDisabled(true);
  this->lastFrameButton->setFixedWidth(25);
  QObject::connect(this->lastFrameButton, &QPushButton::clicked, this, [&]() {
    //When firstFrameButton is clicked, jump to the last frame of the animation and enable or disable buttons appropriately
    this->setTruckPosition(this->animationMax);
    this->animationStatus = AtEnd;
    this->nextFrameButton->setDisabled(true);
    this->lastFrameButton->setDisabled(true);
    this->backFrameButton->setDisabled(false);
    this->firstFrameButton->setDisabled(false);
    this->animationButton->setText("Restart");
    });
  animationLayout->addWidget(this->firstFrameButton);
  animationLayout->addWidget(this->backFrameButton);
  animationLayout->addWidget(this->animationButton);
  animationLayout->addWidget(this->nextFrameButton);
  animationLayout->addWidget(this->lastFrameButton);
  inputLayout->addWidget(animationWidget);
  topHalfLayout->addWidget(mInputWidget);
  pageLayout->addWidget(topHalf);

  //Create UI group for saving and loading to files
  this->saveLoadGroup = new QGroupBox("Save/Load From File", this);
  inputLayout->addWidget(this->saveLoadGroup);
  QVBoxLayout* saveLoadBox = new QVBoxLayout;
  this->saveLoadGroup->setLayout(saveLoadBox);

  //Create save chart button to save the force response chart to an image file
  this->saveChartButton = new QPushButton("Save Chart", this);
  this->saveChartButton->setDisabled(true);
  QObject::connect(this->saveChartButton, &QPushButton::clicked, this, [&]() {
    //When saveChartButton is clicked, first fill out the chart with all data (so that the saved image has all data points, not only those at the current animation frame)
    std::vector<double> x_vals = this->mReport.results.firstAxlePosition;
    std::vector<double> y_vals;
    if (this->mReport.input.solverConfig.solverType == MockSolverT::CONCERNED) {
      y_vals = this->mReport.results.forceConcernedSection;
    }
    else {
      y_vals = this->mReport.results.forceCriticalSection;
    }
    QLineSeries* series = new QLineSeries(this->mChart);
    for (int i = 0; i < x_vals.size(); i++) {
      series->append(QPointF(x_vals[i], y_vals[i]));
    }
    this->mChart->removeAllSeries();
    this->mChart->addSeries(series);
    foreach(QAbstractAxis * axis, this->mChart->axes()) {
      series->attachAxis(axis);
    }

    //Call saver to save the chart as an image file
    saver::saveSolverFigure(*mChartView->scene());

    //Set the chart back to match the current animation frame
    double xMax = (this->truckGroup->x() - this->animationMin) / PIXELS_PER_METER;
    series = new QLineSeries(this->mChart);
    for (int i = 0; i < x_vals.size(); i++) {
      if (x_vals[i] > xMax) break;
      series->append(QPointF(x_vals[i], y_vals[i]));
    }
    this->mChart->removeAllSeries();
    this->mChart->addSeries(series);
    foreach(QAbstractAxis * axis, this->mChart->axes()) {
      series->attachAxis(axis);
    }
    });
  saveLoadBox->addWidget(this->saveChartButton);

  //Create the save report button
  this->saveReportButton = new QPushButton("Save Report", this);
  this->saveReportButton->setDisabled(true);
  QObject::connect(this->saveReportButton, &QPushButton::clicked, this, [&]() {
    //When saveReportButton is clicked, temporarily disable the button, call saver to save the report, then re-enable the button
    this->saveReportButton->setDisabled(true);
    mtobridge::saver::saveReport(mReport);
    this->saveReportButton->setDisabled(false);
    });
  saveLoadBox->addWidget(this->saveReportButton);

  //Create the load report button
  this->loadReportButton = new QPushButton("Load From Report", this);
  this->loadReportButton->setDisabled(true);
  QObject::connect(this->loadReportButton, &QPushButton::clicked, this, [&]() {
    //When loadReportButton is clicked, emit the loadReport signal
    //This signal will be caught by the window class, which will load the report data and send it back into SolverVisual through the loadedReport slot
    emit loadReport();
    updatePage();
    });
  saveLoadBox->addWidget(this->loadReportButton);

  saveLoadBox->addStretch(1);
  this->saveLoadGroup->setFixedHeight(120);
  
  //Create the scene in which the truck and bridsge visualisations will be combined and shown to the user
  this->truckBridgeVisual = new QGraphicsView(this);
  this->truckBridgeVisual->setFixedHeight(115);
  QGraphicsScene* truckBridgeScene = new QGraphicsScene;
  this->truckBridgeVisual->setScene(truckBridgeScene);
  this->truckBridgeVisual->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  pageLayout->addWidget(this->truckBridgeVisual);
  //Set the initial values of some scene-related variables
  this->truckGroup = new QGraphicsItemGroup();
  this->bridgeGroup = new QGraphicsItemGroup();
  this->concernedSectionLine = NULL;
  this->discretizationLengthText = NULL;
  this->criticalSectionLine = NULL;

  //Get an instance of the Engine class
  auto& engine = Engine::getInstance();

  //Connect the runCommand signal of this class to the runCommand slot of Engine
  //This will run the matlab code when we emit the runCommand signal
  QObject::connect(this, &SolverVisual::runCommand, &engine,
                   &Engine::runCommand);

  QObject::connect(&engine, &Engine::engineStarted, this, [&]() {
    //Once Engine has been started (the MATLAB code has been loaded), enable the calculate and load report buttons
    this->calculateButton->setText("Run Analysis");
    this->loadReportButton->setDisabled(false);
    //Only enable the calculate button if a truck platoon and bridge have been configured
    if (this->truckGroup->childItems().size() != 0 && this->bridgeGroup->childItems().size() != 0) {
      this->calculateButton->setDisabled(false);
    }
  });

  //Connect the finishedCommand signal of engine to the updateChart slot of this class
  //This will update the chart when engine emits the finishedCommand signal
  QObject::connect(&engine, &Engine::finishedCommand, this,
                   &SolverVisual::updateChart);
}

//Updates UI elements when a new force response or solver type is selected
void SolverVisual::updatePage() {
  //First unselect all force response and solver type buttons
  positiveMomentButton->setChecked(false);
  negativeMomentButton->setChecked(false);
  shearButton->setChecked(false);
  concernedButton->setChecked(false);
  criticalButton->setChecked(false);

  //Select the correct force response button
  if (Solver::getForceType() == "Positive Moment") {
    positiveMomentButton->setChecked(true);
  } else if (Solver::getForceType() == "Negative Moment") {
    negativeMomentButton->setChecked(true);
  } else if (Solver::getForceType() == "Shear") {
    shearButton->setChecked(true);
  }

  //Select the correct solver type button
  if (Solver::getSolverType() == "Concerned Section") {
    concernedButton->setChecked(true);
    mChartTabWidget->setTabVisible(1, false);
  } else if (Solver::getSolverType() == "Critical Section") {
    criticalButton->setChecked(true);
    mChartTabWidget->setTabVisible(1, true);
  }

  //Update the animation to match the newly update UI
  this->setUpAnimation();
}

//Set the current truck position to a given x coordinate and update the chart to match truck position
void SolverVisual::setTruckPosition(double x) {
  //If the given coordinate is above the max or below the min, set it to be within bounds
  if (x > this->animationMax) x = this->animationMax;
  else if (x < this->animationMin) x = this->animationMin;

  //Set the truck platoon position
  this->truckGroup->setPos(x, 5);

  //Clear the chart and add the appropriate data points for the new truck position
  double xMax = (x - this->animationMin) / PIXELS_PER_METER;
  std::vector<double> x_vals = this->mReport.results.firstAxlePosition;
  std::vector<double> y_vals;
  if (this->mReport.input.solverConfig.solverType == MockSolverT::CONCERNED) {
    y_vals = this->mReport.results.forceConcernedSection;
  }
  else {
    y_vals = this->mReport.results.forceCriticalSection;
  }
  QLineSeries* series = new QLineSeries(this->mChart);
  for (int i = 0; i < x_vals.size(); i++) {
    if (x_vals[i] > xMax) break;
    series->append(QPointF(x_vals[i], y_vals[i]));
  }
  this->mChart->removeAllSeries();
  this->mChart->addSeries(series);
  foreach(QAbstractAxis * axis, this->mChart->axes()) {
    series->attachAxis(axis);
  }
}

//Move the animation by a given number of frames
bool SolverVisual::moveFrames(int numFrames) {
  //Move the truck position by the number of frames multiplied by the number of pixels per animation frame
  this->setTruckPosition(this->truckGroup->x() + numFrames * this->animationInc);

  //Return false if we are at the animation minimum or maximum, true otherwise
  if (this->truckGroup->x() >= this->animationMax || this->truckGroup->x() <= this->animationMin) return false;
  else return true;
}

//Start animation running forwards
void SolverVisual::animateForward() {
  //If the animation is no longer running forwards then return
  if (this->animationStatus != RunningForward) return;

  //Move the animation 1 frame forward
  if (moveFrames(1)) {
    //If we are not at the end of the animation, set a timer to call this function again in animationSpeed number of miliseconds
    QTimer::singleShot(this->animationSpeed, this, &SolverVisual::animateForward);
  }
  else {
    //If we are at the end of the animation then update the UI elements
    this->animationStatus = AtEnd;
    this->animationButton->setText("Restart");
    this->backFrameButton->setDisabled(false);
    this->firstFrameButton->setDisabled(false);
    this->nextFrameButton->setDisabled(true);
    this->lastFrameButton->setDisabled(true);
  }
}

//Start animation running backwards
//This must be a seperate function from animateForward() because QTimer::singleShot() cannot call a function with parameters
void SolverVisual::animateBackward() {
  //If the animation is no longer running backwards then return
  if (this->animationStatus != RunningBackward) return;

  //Move the animation 1 frame backwards
  if (moveFrames(-1)) {
    //If we are not at the beginning of the animation, set a timer to call this function again in animationSpeed number of miliseconds
    QTimer::singleShot(this->animationSpeed, this, &SolverVisual::animateBackward);
  }
  else {
    //If we are at the beginning of the animation thrn update the UI elements
    this->animationStatus = AtBeginning;
    this->animationButton->setText("Play");
    this->backFrameButton->setDisabled(true);
    this->firstFrameButton->setDisabled(true);
    this->nextFrameButton->setDisabled(false);
    this->lastFrameButton->setDisabled(false);
  }
}

//The slot triggered when the calculation results are returned
void SolverVisual::updateChart(MockCalculationInputT in,
                               MockCalculationOutputT out) {
  //Fill report member of the class
  this->mReport.input = in;
  this->mReport.results = out;
  
  //Get the graph point data
  std::vector<double> x_vals = std::move(out.firstAxlePosition);
  if (x_vals.empty()) {
    //Ff the output data is empty then stop the function
    this->calculateButton->setText("Run Analysis");
    this->calculateButton->setDisabled(false);
    return;
  }
  std::vector<double> y_vals;
  //Must get the y values for the appropriate solver type
  if (in.solverConfig.solverType == MockSolverT::CONCERNED) {
    y_vals = std::move(out.forceConcernedSection);
  } else {
    y_vals = std::move(out.forceCriticalSection);
  }

  //Remove the axis currently on the chart
  for (auto& axis : this->mChart->axes()) {
    this->mChart->removeAxis(axis);
  }

  //Get the force response type that was used in the calculations
  QString force;
  if (in.solverConfig.forceType == MockSolverT::POSITIVE_MOMENT) {
    force = "Positive Moment";
  } else if (in.solverConfig.forceType == MockSolverT::NEGATIVE_MOMENT) {
    force = "Negative Moment";
  } else {
    force = "Shear";
  }

  //Get the bridge section that was used in the calculations
  double position;
  if (in.solverConfig.solverType == MockSolverT::CONCERNED) {
    position = in.bridgeConfig.concernedSection;
  } else {
    position = out.criticalSection;

    //Draw the critical section line on the bridge display
    int x = this->bridgeGroup->mapRectToScene(this->bridgeGroup->boundingRect()).x() + 4 * PIXELS_PER_METER + position * PIXELS_PER_METER;
    int y = this->bridgeGroup->mapRectToScene(this->bridgeGroup->boundingRect()).y() + 1 * PIXELS_PER_METER + 2;
    this->criticalSectionLine = this->truckBridgeVisual->scene()->addLine(x, y, x, y + 2 * PIXELS_PER_METER - 2, this->concernedSectionLine->pen());
    criticalSectionLine->setZValue(this->concernedSectionLine->zValue());
  }

  //Set the title of the chart and create the chart axes
  this->mChart->setTitle(QString("%1 at %2 meters").arg(force).arg(position));
  QValueAxis* xAxis = new QValueAxis();
  xAxis->setTitleText(QString("First Axle Position (m)"));
  xAxis->setMin(x_vals.front());
  xAxis->setMax(x_vals.back());
  this->mChart->addAxis(xAxis, Qt::AlignBottom);
  QValueAxis* yAxis = new QValueAxis();
  yAxis->setTitleText(
    QString("%1 at %2 Section (kNm)")
    .arg(force)
    .arg(in.solverConfig.solverType == MockSolverT::CONCERNED
      ? "Concerned"
      : "Critical"));
  yAxis->setMin(*std::min_element(y_vals.begin(), y_vals.end()));
  yAxis->setMax(*std::max_element(y_vals.begin(), y_vals.end()));
  this->mChart->addAxis(yAxis, Qt::AlignLeft);

  //Set the chart view to be the chart
  this->mChartView->setChart(this->mChart);

  //If the solver type is critical, create the force envelope chart
  if (in.solverConfig.solverType == CRITICAL) {
    //Get the x and y values of the points on the chart
    x_vals = std::move(out.sections);
    y_vals = std::move(out.forceEnvelope);

    //Create a new series using the data points
    QLineSeries* series = new QLineSeries(mEnvelopeChart);
    for (int i = 0; i < x_vals.size(); i++) {
      series->append(QPointF(x_vals[i], y_vals[i]));
    }
    
    //Clear the current series and axes from the chart
    mEnvelopeChart->removeAllSeries();
    for (auto& axis : mEnvelopeChart->axes()) {
      mEnvelopeChart->removeAxis(axis);
    }
    //Add the new series to the chart
    mEnvelopeChart->addSeries(series);

    //Set the title of the chart and create the chart axes
    mEnvelopeChart->setTitle(QString("%1 Envelope").arg(force));
    mEnvelopeChart->createDefaultAxes();
    mEnvelopeChart->axes(Qt::Horizontal).first()->setMin(x_vals.front());
    mEnvelopeChart->axes(Qt::Horizontal).first()->setMax(x_vals.back());
    mEnvelopeChart->axes(Qt::Horizontal).first()->setTitleText("Bridge Section (m)");
    mEnvelopeChart->axes(Qt::Vertical)
        .first()
        ->setMin(*std::min_element(y_vals.begin(), y_vals.end()));
    mEnvelopeChart->axes(Qt::Vertical)
        .first()
        ->setMax(*std::max_element(y_vals.begin(), y_vals.end()));
    mEnvelopeChart->axes(Qt::Vertical).first()->setTitleText(
      QString("%1 (kNm)")
      .arg(force));

    //Set the chart view to be the chart
    mEnvelopeChartView->setChart(mEnvelopeChart);
  }

  //Update the appropriate UI elements and start the animation running forward
  this->saveReportButton->setDisabled(false);
  this->saveChartButton->setDisabled(false);
  this->animationStatus = RunningForward;
  this->backFrameButton->setDisabled(true);
  this->firstFrameButton->setDisabled(true);
  this->nextFrameButton->setDisabled(true);
  this->lastFrameButton->setDisabled(true);
  this->animationButton->setText("Pause");
  this->animationButton->setDisabled(false);
  this->calculateButton->setText("Results Are Displayed");
  this->calculateButton->setDisabled(true);
  this->animateForward();
}

//Used to set up animation, involves calculating animation settings and setting truck and brdige positions
void SolverVisual::setUpAnimation() {
  //First we must set all the UI elements to be disabled and in their default states
  this->animationStatus = NotLoaded;
  this->backFrameButton->setDisabled(true);
  this->firstFrameButton->setDisabled(true);
  this->nextFrameButton->setDisabled(true);
  this->lastFrameButton->setDisabled(true);
  this->animationButton->setText("Play");
  this->animationButton->setDisabled(true);
  this->saveReportButton->setDisabled(true);
  this->saveChartButton->setDisabled(true);
  if (this->calculateButton->text() != "Initialising...") {
    this->calculateButton->setText("Run Analysis");
    this->calculateButton->setDisabled(true);
  }

  //Remove all series and axes from the force response chart and reset its title
  this->mChart->removeAllSeries();
  for (auto& axis : this->mChart->axes()) {
    this->mChart->removeAxis(axis);
  }
  this->mChart->setTitle("");

  //Remove all series and axes from the force envelope chart and reset its title
  this->mEnvelopeChart->removeAllSeries();
  for (auto& axis : this->mEnvelopeChart->axes()) {
    this->mEnvelopeChart->removeAxis(axis);
  }
  this->mEnvelopeChart->setTitle("");

  //Remove the current critical section line if there is one
  if (this->criticalSectionLine != NULL) {
    this->truckBridgeVisual->scene()->removeItem(this->criticalSectionLine);
    delete this->criticalSectionLine;
    this->criticalSectionLine = NULL;
  }

  //If the bridge settings are completed and there is a bridge to be displayed
  if (this->bridgeGroup->childItems().size() != 0) {
    //Get the width of the truck and bridge visualisation scene
    double width = (this->bridgeGroup->boundingRect().width() + 10 < this->truckBridgeVisual->maximumViewportSize().width()) ? this->truckBridgeVisual->maximumViewportSize().width() : this->bridgeGroup->boundingRect().width() + 10;

    //Set the scene size
    this->truckBridgeVisual->setSceneRect(0, 0, width, 95);

    //Set the bridge location to be the middle of the scene
    this->bridgeGroup->setPos(( width - this->bridgeGroup->boundingRect().width() ) / 2, 29);

    //Enable or disable the discretization length text and concerned section line based on the currently selected solver type
    if (this->concernedButton->isChecked()) {
      if (this->discretizationLengthText != NULL) {
        this->discretizationLengthText->hide();
      }

      if (this->concernedSectionLine != NULL) {
        this->concernedSectionLine->show();
      }
    }
    else if (this->criticalButton->isChecked()) {
      if (this->concernedSectionLine != NULL) {
        this->concernedSectionLine->hide();
      }

      if (this->discretizationLengthText != NULL) {
        this->discretizationLengthText->show();
        this->discretizationLengthText->setPos((width - this->discretizationLengthText->boundingRect().width()) / 2, 69);
      }
    }
  }

  //If the truck and bridge settings are completed and there is a truck and bridge to be displayed
  if (this->truckGroup->childItems().size() != 0 && this->bridgeGroup->childItems().size() != 0) {
    //Enable the calculation button if the MATLAB engine has loaded
    if (this->calculateButton->text() != "Initialising...") {
      this->calculateButton->setDisabled(false);
    }

    //Get the length of the truck platoon and the bridge
    double platoonLength = this->truckGroup->boundingRect().width() - 2;
    double bridgeLength = this->bridgeGroup->boundingRect().width() - 8 * PIXELS_PER_METER - 1;

    //Calculate various animation variables based on the scene width, platoon length, and bridge length
    //The animation minimum is calculated so that the first axle of the first truck starts right at the beginning of the bridge
    //The animation maximum is calculated so that the last axle of the last truck ends right off the edge the bridge
    this->animationMin = (this->truckBridgeVisual->sceneRect().width() / 2 + 10) + (PIXELS_PER_METER - platoonLength) - (bridgeLength / 2);
    this->animationMax = this->animationMin + (platoonLength - 2 * PIXELS_PER_METER - 2 * PIXELS_PER_METER) + bridgeLength;
    this->animationInc = (int)ceil(PIXELS_PER_METER * TRUCK_POSITION_INCREMENT);
    this->animationSpeed = ANIMATION_TIME / ((this->animationMax - this->animationMin) / this->animationInc);

    //Set the position of the trucks to the beginning of the animation
    this->truckGroup->setPos(this->animationMin, 5);
  }
  //If the truck settings are completed, but the bridge settings are not
  else if (this->truckGroup->childItems().size() != 0) {
    //Set the scene size and truck position
    this->truckBridgeVisual->setSceneRect(0, 0, this->truckBridgeVisual->maximumViewportSize().width(), 95);
    this->truckGroup->setPos(10, 5);
  }
}

//The slot called when a scene (either truck or bridge visuals) is updated
void SolverVisual::updateScene(std::string sceneType, QGraphicsScene* scene) {
  //Initialise a new graphics item group
  QGraphicsItemGroup* group = new QGraphicsItemGroup();
  if (sceneType == "Truck") {
    //If we are updating the truck scene, remove all items in the current truck group from the scene
    foreach(QGraphicsItem * item, this->truckGroup->childItems()) {
      this->truckBridgeVisual->scene()->removeItem(item);
      delete item;
    }
    //Set the truck group to be the newly created group
    this->truckGroup = group;
  }
  else if (sceneType == "Bridge") {
    //If we are updating the bridge scene, remove all items in the current bridge group from the scene
    foreach(QGraphicsItem * item, this->bridgeGroup->childItems()) {
      this->truckBridgeVisual->scene()->removeItem(item);
      delete item;
    }
    //Remove the discretization length text and concerned section line from the scene
    this->truckBridgeVisual->scene()->removeItem(this->discretizationLengthText);
    delete this->discretizationLengthText;
    this->discretizationLengthText = NULL;
    this->concernedSectionLine = NULL;
    //Set the bridge group to be the newly created group
    this->bridgeGroup = group;
  }
  else {
    //If we are updating neither the truck nor the bridge scene then inputs are invalid
    return;
  }

  //Get all items in the inputted scene
  QList<QGraphicsItem*> items = scene->items();
  if (items.size() != 0) {
    //This will be used to keep track of the number of spans, which is used to enable (if spans > 1) or disable the negative moment force response option
    int spanCount = 0;

    //For all items in the inputted scene
    foreach(QGraphicsItem* item, items) {
      //This will copy each item from the inputted scene into our scene and add it to the newly created item group
      //Inspiration from https://forum.qt.io/topic/85648/how-can-i-copy-paste-qgraphicsitems/6

      //For rectangle items
      QGraphicsRectItem* rect = qgraphicsitem_cast<QGraphicsRectItem*>(item);
      if (rect != NULL) {
        //Create a new rect in our scene with the same properties as the rect we are copying
        QGraphicsRectItem* newRect = this->truckBridgeVisual->scene()->addRect(rect->mapRectToScene(rect->rect()), rect->pen(), rect->brush());
        //Set this new rect's z value to be the same as the one we are copying
        newRect->setZValue(rect->zValue());
        //Add the new rectangle to our group
        group->addToGroup(newRect);

        //If this rectangle is the support for a span, increment the number of spans
        if (sceneType == "Bridge" && rect->brush().color() == Qt::gray) {
          spanCount++;
        }
      }

      //For ellipses items, idea same as rectangle items
      QGraphicsEllipseItem* ellipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
      if (ellipse != NULL) {
        QGraphicsEllipseItem* newEllipse = this->truckBridgeVisual->scene()->addEllipse(ellipse->mapRectToScene(ellipse->rect()), ellipse->pen(), ellipse->brush());
        newEllipse->setZValue(ellipse->zValue());
        group->addToGroup(newEllipse);
      }

      //For line items, idea same as rectangle items
      QGraphicsLineItem* line = qgraphicsitem_cast<QGraphicsLineItem*>(item);
      if (line != NULL) {
        QPointF p1 = line->mapToScene(line->line().p1());
        QPointF p2 = line->mapToScene(line->line().p2());
        QGraphicsLineItem* newLine = this->truckBridgeVisual->scene()->addLine(p1.x(), p1.y(), p2.x(), p2.y(), line->pen());
        newLine->setZValue(line->zValue());
        group->addToGroup(newLine);

        //If this line is the concerned section line on the bridge, mark it as such
        if (sceneType == "Bridge" && line->pen().color() == Qt::red) {
          this->concernedSectionLine = newLine;
          newLine->hide();
        }
      }

      //For text items, idea same as rectangle items
      QGraphicsTextItem* text = qgraphicsitem_cast<QGraphicsTextItem*>(item);
      if (text != NULL) {
        QGraphicsTextItem* newText = this->truckBridgeVisual->scene()->addText(text->toPlainText());
        newText->setZValue(text->zValue());
        newText->hide();

        //Since the only text item possible is the discretization length text, mark it as such
        this->discretizationLengthText = newText;
      }
    }

    //Add all items from the new group to the scene (while we initialy added them to the scene when we created them, adding them to the group removed them from the scene)
    this->truckBridgeVisual->scene()->addItem(group);

    //Enable or disable the negative moment option based on the found span length
    //When there is 1 span there will be 2 supports (on each bank), 2 spans = 3 supports, etc.
    if (sceneType == "Bridge") {
      if (spanCount == 2) {
        //Disable negative moment, swap to positive moment if negative moment is currently selected
        this->negativeMomentButton->setEnabled(false);
        if (this->negativeMomentButton->isChecked()) {
          this->positiveMomentButton->click();
        }
      }
      else {
        //Enable negative moment
        this->negativeMomentButton->setEnabled(true);
      }
    }
  }

  //Set up the animation with the newly updated item group
  this->setUpAnimation();
}

//Internal slot for when the calculate button is clicked
void SolverVisual::calculateClicked() {
  //Disable certain UI elements while calculation is running
  this->calculateButton->setDisabled(true);
  this->calculateButton->setText("Analysing...");
  this->saveReportButton->setDisabled(true);
  this->saveChartButton->setDisabled(true);
  this->backFrameButton->setDisabled(true);
  this->firstFrameButton->setDisabled(true);
  this->nextFrameButton->setDisabled(true);
  this->lastFrameButton->setDisabled(true);
  this->animationButton->setDisabled(true);

  //Collect the current truck configuration
  MockCalculationInputT in;
  in.truckConfig.axleLoad = PlatoonConfiguration::getAxleLoads();
  in.truckConfig.axleSpacing = PlatoonConfiguration::getAxleSpacings();
  in.truckConfig.numberOfTrucks = PlatoonConfiguration::getNumTrucks();
  in.truckConfig.headway = PlatoonConfiguration::getHeadway();

  //Collect the current bridge configuration
  BridgeT bridgeConfig = BridgeConfiguration::getConfiguration();
  in.bridgeConfig.numberSpans = bridgeConfig.numberSpans;
  in.bridgeConfig.spanLength = bridgeConfig.spanLength;
  in.bridgeConfig.concernedSection = bridgeConfig.concernedSection;
  in.bridgeConfig.discretizationLength = bridgeConfig.discretizationLength;

  //Collect the current solver configuration
  if (Solver::getForceType() == "Positive Moment") {
    in.solverConfig.forceType = MockSolverT::POSITIVE_MOMENT;
  }
  else if (Solver::getForceType() == "Negative Moment") {
    in.solverConfig.forceType = MockSolverT::NEGATIVE_MOMENT;
  }
  else if (Solver::getForceType() == "Shear") {
    in.solverConfig.forceType = MockSolverT::SHEAR;
  }

  if (Solver::getSolverType() == "Concerned Section") {
    in.solverConfig.solverType = MockSolverT::CONCERNED;
  }
  else if (Solver::getSolverType() == "Critical Section") {
    in.solverConfig.solverType = MockSolverT::CRITICAL;
  }

  //Emit the runCommand signal, which will start the calculation in the engine class
  emit SolverVisual::runCommand(in);
}

//The slot called when a report is being loaded
void SolverVisual::loadedReport(Report report) {
  //Update the current force response type based on inputted report
  auto config = report.input.solverConfig;
  if (config.forceType == MockSolverT::POSITIVE_MOMENT) {
      Solver::updateForceType("Positive Moment");
  }
  else if (config.forceType == MockSolverT::NEGATIVE_MOMENT) {
      Solver::updateForceType("Negative Moment");
  }
  else if (config.forceType == MockSolverT::SHEAR) {
      Solver::updateForceType("Shear");
  }

  //Update the current solver type based on inputted report
  if (config.solverType == MockSolverT::CONCERNED) {
      Solver::updateSolverType("Concerned Section");
  }
  else if (config.solverType == MockSolverT::CRITICAL) {
      Solver::updateSolverType("Critical Section");
  }

  //Update the visualisation page to match new inputs
  updatePage();

  //Automatically start the calculation once all inputs match the loaded report
  calculateClicked();
}
};  // namespace mtobridge
