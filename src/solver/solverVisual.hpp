#pragma once

#include <QtCharts>
#include <QtWidgets>

#include "../report/report.hpp"
#include "util/data_types.hpp"

#define ANIMATION_TIME 15000          //Total time the animation should take in miliseconds
#define PIXELS_PER_METER 5            //Pixels per meter in truck and bridge visualisations
#define TRUCK_POSITION_INCREMENT 0.1  //Amount the truck moves forward per data point (in meters)
#define BUTTON_HOLD_TIME 500          //Amount of time (in ms) the nextFrame or backFrame button needs to be held before manual animation is started

namespace mtobridge {
//enums for use in representing the current animation status
enum AnimationStatus { NotLoaded, AtBeginning, AtEnd, Paused, RunningForward, RunningBackward };

//ChartView class used in overwritting the mouseReleaseEvent function of QChartView
//This is the class used for the force response chart allowing the user to click on the chart to jump the animation to that point
class ChartView : public QChartView {
  Q_OBJECT

 public:
  ChartView(QChart* chart, QWidget* parent = 0) {}

 protected:
  void mouseReleaseEvent(QMouseEvent* event) override;
};

//The main class for the solver visualisation page
class SolverVisual : public QWidget {
  Q_OBJECT

 public:
  SolverVisual(QWidget* parent) : QWidget(parent) { createPage(); };
  ~SolverVisual(){};

  //Have to set the ChartView class as a friend so that it can access private variables (animationStatus) and methods (setTruckPosition)
  friend class ChartView;

 signals:
  //The signal used to start the matlab calculations
  void runCommand(MockCalculationInputT);

  //The signal used to signify loading a report to other modules
  void loadReport();

 public slots:
  //The slot triggered when an error is encountered
  void errorOccurred(QString);

  //The slot triggered when the calculation results are returned
  void updateChart(MockCalculationInputT, MockCalculationOutputT);

  //The slot called when a report is being loaded
  void loadedReport(Report);

  //The slot called when a scene (either truck or bridge visuals) is updated
  void updateScene(std::string, QGraphicsScene*);

 private slots:
  //Internal slot for when the calculate button is clicked
  void calculateClicked();

 private:
  //Variables for various UI widget groups
  QGroupBox* forceSettingGroup;                   //UI element group for force response type buttons     
  QGroupBox* solverSettingGroup;                  //UI element group for solver type buttons
  QGroupBox* saveLoadGroup;                       //UI element group for saving and loading reports and saving chart figures

  //Variables for various UI Buttons
  QRadioButton* positiveMomentButton;             //Button for setting the current force response to positive moment
  QRadioButton* negativeMomentButton;             //Button for setting the current force response to negative moment
  QRadioButton* shearButton;                      //Button for setting the current force response to shear
  QRadioButton* concernedButton;                  //Button for setting the current calculation type to concerned section
  QRadioButton* criticalButton;                   //Button for setting the current calculation type to critical section
  QPushButton* calculateButton;                   //Button to start calculations
  QPushButton* firstFrameButton;                  //Button to jump to first frame of animation
  QPushButton* backFrameButton;                   //Button to move animation back one frame
  QPushButton* animationButton;                   //Button to play or pause animation
  QPushButton* nextFrameButton;                   //Button to move animation forward one frame
  QPushButton* lastFrameButton;                   //Button to jump to last frame of animation
  QTimer* buttonHoldTimer;                        //Timer element used to determine when the backFrame or nextFrame buttons are being held down
  QPushButton* saveChartButton;                   //Button to save the force response chart as an image file
  QPushButton* saveReportButton;                  //Button to save the current report to a file
  QPushButton* loadReportButton;                  //Button to load all settings from a previously saved report file

  //Variables for the result charts
  QTabWidget* mChartTabWidget;                    //Parent tab widget that the two charts are added to
  QChart* mChart;                                 //Chart widget for the force response chart
  ChartView* mChartView;                          //Chart view for the force response chart
  QChart* mEnvelopeChart;                         //Chart widget for the force envelope chart (only displayed when calculating critical section)
  QChartView* mEnvelopeChartView;                 //Chart view for the force envelope chart (only displayed when calculating critical section)

  //Animation related variables
  QGraphicsView* truckBridgeVisual;               //Graphics scene where the truck and bridge visualisation are combined and displayed to the user
  QGraphicsItemGroup* truckGroup;                 //UI items group that contains all the bridge-related UI items being displayed in the truck and bridge scene
  QGraphicsItemGroup* bridgeGroup;                //UI items group that contains all the truck-related UI items being displayed in the truck and bridge scene
  QGraphicsLineItem* concernedSectionLine;        //Line UI item displayed in the truck and bridge scene to show user current concerned section
  QGraphicsLineItem* criticalSectionLine;         //Line UI item displayed in the truck and bridge scene to show user current critical section
  QGraphicsTextItem* discretizationLengthText;    //Text UI item displayed in the truck and bridge scene to inform user of current discretization length

  //Variable for the calculation results data
  Report mReport;                                 //Report variable that holds all calculation results

  //Variables to keep track of the animation settings
  int animationMin;                               //Minimum truck x position in animation
  int animationMax;                               //Maximum truck x position in animation
  int animationInc;                               //Truck x position increment per frame in animation
  int animationSpeed;                             //Time (in ms) between animation frames
  AnimationStatus animationStatus;                //Current status of the animation

  //Animation related methods
  void setTruckPosition(double);                  //Set the current truck position to a given x coordinate and update the chart to match truck position
  bool moveFrames(int);                           //Move the animation by a given number of frames
  void animateForward();                          //Start animation running forwards
  void animateBackward();                         //Start animation running backwards
  void setUpAnimation();                          //Used to set up animation, involves calculating animation settings and setting truck and brdige positions

  //Methods used for creating an updating various UI elements
  void createPage();                              //Initial creation of UI page
  void updatePage();                              //Updates UI elements when a new force response or solver type is selected
};
};  // namespace mtobridge
