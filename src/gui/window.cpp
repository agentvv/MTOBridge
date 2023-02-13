#include "window.hpp"

#include <chrono>
#include <sstream>
#include <thread>

#include "../engine/engine.hpp"
#include "../bridge/bridgeconfig.hpp"
#include "../saver/saver.hpp"
#include "../saver/loader.hpp"

namespace mtobridge {
Window::Window(QWidget *parent) : QWidget(parent) {
  setWindowTitle("MTOBridge");
  resize(800, 600);
  createWindow();
}

/// SPAGHETTI INCOMING
/// should move this stuff to separate custom widgets, and also .ui files...
void Window::createWindow() {
  mTabWidget = new QTabWidget(this);
  mTabWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                        QSizePolicy::Policy::Expanding));

  auto *mainLayout = new QStackedLayout(this);
  mainLayout->addWidget(mTabWidget);
  setLayout(mainLayout);

  /// page 1
  mPage = new QWidget(mTabWidget);
  mPage->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                   QSizePolicy::Policy::Expanding));
  auto *pageLayout = new QHBoxLayout();
  mPage->setLayout(pageLayout);

  // set up all inputs and layout
  {
    auto *inputLayout = new QGridLayout();
    mInputWidget = new QWidget(mPage);
    mInputWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                            QSizePolicy::Policy::Expanding));
    mInputWidget->setLayout(inputLayout);

    mAxleLoad = new QLineEdit("53.4 75.6 75.6 75.6 75.6", mInputWidget);
    mAxleLoadLabel = new QLabel("Axle Load", mInputWidget);

    mAxleSpacing = new QLineEdit("3.6576 1.2192 9.4488 1.2192", mInputWidget);
    mAxleSpacingLabel = new QLabel("Axle Spacing", mInputWidget);

    mNumberOfTrucks = new QLineEdit("3", mInputWidget);
    mNumberOfTrucksLabel = new QLabel("Number of Trucks", mInputWidget);

    mHeadway = new QLineEdit("5", mInputWidget);
    mHeadwayLabel = new QLabel("Truck Headway", mInputWidget);

    mNumberSpans = new QLineEdit("2", mInputWidget);
    mNumberSpansLabel = new QLabel("Number of Spans", mInputWidget);

    mSpanLength = new QLineEdit("20 20", mInputWidget);
    mSpanLengthLabel = new QLabel("Span Length", mInputWidget);

    mConcernedSection = new QLineEdit("10", mInputWidget);
    mConcernedSectionLabel = new QLabel("Concerned Section", mInputWidget);

    mDiscretizationLength = new QLineEdit("0.1", mInputWidget);
    mDiscretizationLengthLabel =
        new QLabel("Discretization Length", mInputWidget);

    mForceType = new QLineEdit("positive", mInputWidget);
    mForceTypeLabel = new QLabel("Force Type", mInputWidget);

    mSolverType = new QLineEdit("concerned", mInputWidget);
    mSolverTypeLabel = new QLabel("Solver Type", mInputWidget);

    inputLayout->addWidget(mAxleLoadLabel, 0, 0);
    inputLayout->addWidget(mAxleLoad, 0, 1);
    inputLayout->addWidget(mAxleSpacingLabel, 1, 0);
    inputLayout->addWidget(mAxleSpacing, 1, 1);
    inputLayout->addWidget(mNumberOfTrucksLabel, 2, 0);
    inputLayout->addWidget(mNumberOfTrucks, 2, 1);
    inputLayout->addWidget(mHeadwayLabel, 3, 0);
    inputLayout->addWidget(mHeadway, 3, 1);

    inputLayout->addWidget(mNumberSpansLabel, 4, 0);
    inputLayout->addWidget(mNumberSpans, 4, 1);
    inputLayout->addWidget(mSpanLengthLabel, 5, 0);
    inputLayout->addWidget(mSpanLength, 5, 1);
    inputLayout->addWidget(mConcernedSectionLabel, 6, 0);
    inputLayout->addWidget(mConcernedSection, 6, 1);
    inputLayout->addWidget(mDiscretizationLengthLabel, 7, 0);
    inputLayout->addWidget(mDiscretizationLength, 7, 1);

    inputLayout->addWidget(mForceTypeLabel, 8, 0);
    inputLayout->addWidget(mForceType, 8, 1);
    inputLayout->addWidget(mSolverTypeLabel, 9, 0);
    inputLayout->addWidget(mSolverType, 9, 1);
  }
  pageLayout->addWidget(mInputWidget);
  
  // set up chart and calculate button
  {
    auto *chartLayout = new QGridLayout();
    mChartWidget = new QWidget(mPage);
    mChartWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                            QSizePolicy::Policy::Expanding));
    mChartWidget->setLayout(chartLayout);

    mChart = new QChart();
    mChart->legend()->hide();
    mChart->createDefaultAxes();

    mChartView = new QChartView(mChart, mChartWidget);
    mChartView->setRenderHint(QPainter::Antialiasing);
    mChartView->resize(300, 300);
    mChartView->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                          QSizePolicy::Policy::Expanding));
    chartLayout->addWidget(mChartView, 0, 0);

    mButton = new QPushButton("Run", mPage);
    mButton->setDisabled(true);
    chartLayout->addWidget(mButton, 1, 0);
  }
  pageLayout->addWidget(mChartWidget);
  mTabWidget->addTab(mPage, "Main");

  // Integration
  //// bridge tab
  bridgePage = new QWidget(mTabWidget);
  bridgePage->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                   QSizePolicy::Policy::Expanding));
  auto *bridgePageLayout = new QVBoxLayout();
  bridgePage->setLayout(bridgePageLayout);

  // bridge input section
  {
    auto *bridgeInputLayout = new QGridLayout();
    bridgeInputWidget = new QWidget(bridgePage);
    bridgeInputWidget->setSizePolicy(QSizePolicy(
        QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
    bridgeInputWidget->setLayout(bridgeInputLayout);

    bridgeInputLayout->addWidget(mNumberSpansLabel, 4, 0);
    bridgeInputLayout->addWidget(mNumberSpans, 4, 1);
    bridgeInputLayout->addWidget(mSpanLengthLabel, 5, 0);
    bridgeInputLayout->addWidget(mSpanLength, 5, 1);
    bridgeInputLayout->addWidget(mConcernedSectionLabel, 6, 0);
    bridgeInputLayout->addWidget(mConcernedSection, 6, 1);
    bridgeInputLayout->addWidget(mDiscretizationLengthLabel, 7, 0);
    bridgeInputLayout->addWidget(mDiscretizationLength, 7, 1);
  }
  bridgePageLayout->addWidget(bridgeInputWidget);

  // bridge visualizer
  auto *visualizerLayout = new QGridLayout();
  mVisualizerWidget = new QWidget(bridgePage);
  mVisualizerWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                               QSizePolicy::Policy::Expanding));

  mVisualizerWidget->setLayout(visualizerLayout);

  mVisualizerView = new QGraphicsView(mVisualizerWidget);
  scene = new QGraphicsScene(bridgePage);
  mVisualizerView->setScene(scene);
  visualizerLayout->addWidget(mVisualizerView, 0, 0);

  previewButton = new QPushButton("Preview", bridgePage);
  visualizerLayout->addWidget(previewButton, 1, 0);

  bridgePageLayout->addWidget(mVisualizerWidget);
  mTabWidget->addTab(bridgePage, "Bridge");

  //bridge IO section
  auto *bridgeIOLayout = new QGridLayout();
  bridgeIOWidget = new QWidget(bridgePage);
  bridgeIOWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                               QSizePolicy::Policy::Expanding));
  bridgeIOWidget->setLayout(bridgeIOLayout);

  saveButton = new QPushButton("Save Config", bridgePage);
  bridgePageLayout->addWidget(saveButton);

  loadButton = new QPushButton("Load Config", bridgePage);
  bridgePageLayout->addWidget(loadButton);


  // connect window to engine for running commands and drawing chart
  {
    auto &engine = Engine::getInstance();

    // add command for engine to run
    QObject::connect(this, &Window::runCommand, &engine, &Engine::runCommand);

    QObject::connect(previewButton, &QPushButton::clicked, this, [&]() {
      // QMessageBox::about(this, "Title", "Button Clicked");
      scene->clear();
      BridgeConfiguration::updateNumberOfSpans(mNumberSpans->text());
      BridgeConfiguration::updateConcernedSection(mConcernedSection->text());
      BridgeConfiguration::updateSpanLength(mSpanLength->text());
      BridgeConfiguration::updateDiscretizationLength(mDiscretizationLength->text());
      BridgeT configBridge = BridgeConfiguration::getConfiguration();

      QBrush grayBrush(Qt::gray);
      QPen blackpen(Qt::black);
      blackpen.setWidthF(1);
      QPen redpen(Qt::red);
      redpen.setWidthF(0.1);

      double bridgeLength = 0;
      int scale = 10;
      for (int i=0; i < configBridge.numberSpans; i++){
        if (bridgeLength != 0) {
          scene->addRect(bridgeLength * scale, 20, 5, 30, blackpen, grayBrush);  // Indicating the spans
        }
        bridgeLength += configBridge.spanLength[i];
      }
      bridgeRect = scene->addRect(0, 0, bridgeLength * scale, 20, blackpen, grayBrush);
      for (double i = configBridge.discretizationLength * scale;
           i < bridgeLength * scale;
           i = i + configBridge.discretizationLength * scale) {
        scene->addLine(i, 0, i, 20, redpen);
      }
    });

    QObject::connect(saveButton, &QPushButton::clicked, this,[&]() { 
        /*BridgeConfiguration configBridgeObject = BridgeConfiguration(mNumberSpans->text(), mConcernedSection->text(), 
                                                                     mSpanLength->text(), mDiscretizationLength->text());*/
        BridgeConfiguration::updateNumberOfSpans(mNumberSpans->text());
        BridgeConfiguration::updateConcernedSection(mConcernedSection->text());
        BridgeConfiguration::updateSpanLength(mSpanLength->text());
        BridgeConfiguration::updateDiscretizationLength(mDiscretizationLength->text());
        saver::saveBridgeConfiguration(BridgeConfiguration::getConfiguration());
    });

    QObject::connect(loadButton, &QPushButton::clicked, this, [&]() {
      BridgeT config = loader::loadBridgeConfiguration();
      mNumberSpans->setText(QString::number(config.numberSpans));
      QString temp = "";
      for (double i : config.spanLength) {
        temp += QString::number(i) + " ";
      }
      mSpanLength->setText(temp);
      mDiscretizationLength->setText(QString::number(config.discretizationLength));
      mConcernedSection->setText(QString::number(config.concernedSection));
    });

    // collect inputs to run matlab
    QObject::connect(mButton, &QPushButton::clicked, this, [&]() {
      MockCalculationInputT in;

      double temp;
      std::vector<double> tempVec;
      std::stringstream tempStream(mAxleLoad->text().toStdString());
      while (tempStream >> temp) {
        tempVec.push_back(temp);
      }
      in.truckConfig.axleLoad = tempVec;
      tempVec.clear();
      tempStream = std::stringstream(mAxleSpacing->text().toStdString());
      while (tempStream >> temp) {
        tempVec.push_back(temp);
      }
      in.truckConfig.axleSpacing = tempVec;
      in.truckConfig.numberOfTrucks = mNumberOfTrucks->text().toInt();
      in.truckConfig.headway = mHeadway->text().toDouble();

      in.bridgeConfig.numberSpans = mNumberSpans->text().toInt();
      tempVec.clear();
      tempStream = std::stringstream(mSpanLength->text().toStdString());
      while (tempStream >> temp) {
        tempVec.push_back(temp);
      }
      in.bridgeConfig.spanLength = tempVec;
      in.bridgeConfig.concernedSection = mConcernedSection->text().toDouble();
      in.bridgeConfig.discretizationLength =
          mDiscretizationLength->text().toDouble();

      if (mForceType->text() == "positive") {
        in.solverConfig.forceType = MockSolverT::POSITIVE_MOMENT;
      } else if (mForceType->text() == "negative") {
        in.solverConfig.forceType = MockSolverT::NEGATIVE_MOMENT;
      } else if (mForceType->text() == "shear") {
        in.solverConfig.forceType = MockSolverT::SHEAR;
      }

      if (mSolverType->text() == "concerned") {
        in.solverConfig.solverType = MockSolverT::CONCERNED;
      } else if (mSolverType->text() == "critical") {
        in.solverConfig.solverType = MockSolverT::CRITICAL;
      }

      mButton->setDisabled(true);
      emit Window::runCommand(in);
    });

    // enable calculate button as soon as matlab is ready to go
    QObject::connect(&engine, &Engine::engineStarted, this,
                     [&]() { mButton->setDisabled(false); });

    // draw chart after command finished
    QObject::connect(
        &engine, &Engine::finishedCommand, this,
        [&](MockCalculationInputT in, MockCalculationOutputT out) {
          std::vector<double> x_vals = std::move(out.firstAxlePosition);
          std::vector<double> y_vals;
          if (in.solverConfig.solverType == MockSolverT::CONCERNED) {
            y_vals = std::move(out.forceConcernedSection);
          } else {
            y_vals = std::move(out.forceCriticalSection);
          }

          mSeries = new QLineSeries(mChart);
          for (int i = 0; i < x_vals.size(); i++)
          {
            mSeries->append(QPointF(x_vals[i], y_vals[i]));
          }

          mChart->removeAllSeries();
          for (auto &axis : mChart->axes()) {
            mChart->removeAxis(axis);
          }
          mChart->addSeries(mSeries);
          QString force;
          if (in.solverConfig.forceType == MockSolverT::POSITIVE_MOMENT) {
            force = "Positive Moment";
          } else if (in.solverConfig.forceType ==
                     MockSolverT::NEGATIVE_MOMENT) {
            force = "Negative Moment";
          } else {
            force = "Shear";
          }

          double position;
          if (in.solverConfig.solverType == MockSolverT::CONCERNED) {
            position = in.bridgeConfig.concernedSection;
          } else {
            position = out.criticalSection;
          }

          mChart->setTitle(QString("%1 at %2 meters").arg(force).arg(position));
          mChart->createDefaultAxes();
          mChart->axes(Qt::Vertical)
              .first()
              ->setTitleText(
                  QString("%1 at %2 Section (kNm)")
                      .arg(force)
                      .arg(in.solverConfig.solverType == MockSolverT::CONCERNED
                               ? "Concerned"
                               : "Critical"));
          mChart->axes(Qt::Horizontal)
              .first()
              ->setTitleText(QString("First Axle Position (m)"));

          mChart->axes(Qt::Horizontal).first()->setMin(x_vals.front());
          mChart->axes(Qt::Horizontal).first()->setMax(x_vals.back());

          mChart->axes(Qt::Vertical)
              .first()
              ->setMin(*std::min_element(y_vals.begin(), y_vals.end()));
          mChart->axes(Qt::Vertical)
              .first()
              ->setMax(*std::max_element(y_vals.begin(), y_vals.end()));

          mChartView->setChart(mChart);

          mButton->setDisabled(false);
        });

    QObject::connect(&engine, &Engine::errorOccurred, this,
                     &Window::errorOccurred);
  }
}

QTabWidget *Window::getTabWidget() { return mTabWidget; }

void Window::errorOccurred(QString error){
    QMessageBox::critical(this, QString("Unknown Error!"), error);
}
};  // namespace mtobridge