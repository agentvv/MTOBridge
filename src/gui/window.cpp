#include "window.hpp"

#include <sstream>

#include "../engine/engine.hpp"

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

    mNumberOfTrucks = new QLineEdit("3", mInputWidget);
    mNumberOfTrucksLabel = new QLabel("Number of Trucks", mInputWidget);

    mTruckPositionIncrement = new QLineEdit("0.1", mInputWidget);
    mTruckPositionIncrementLabel =
        new QLabel("Truck Position Increment", mTruckPositionIncrement);

    mHeadway = new QLineEdit("5", mInputWidget);
    mHeadwayLabel = new QLabel("Truck Headway", mInputWidget);

    mAxleLoad = new QLineEdit("53.4 75.6 75.6 75.6 75.6", mInputWidget);
    mAxleLoadLabel = new QLabel("Axle Load", mInputWidget);

    mAxleSpacing = new QLineEdit("3.6576 1.2192 9.4488 1.2192", mInputWidget);
    mAxleSpacingLabel = new QLabel("Axle Spacing", mInputWidget);

    mSpanLength = new QLineEdit("20", mInputWidget);
    mSpanLengthLabel = new QLabel("Span Length", mInputWidget);

    mConcernedSection = new QLineEdit("10", mInputWidget);
    mConcernedSectionLabel = new QLabel("Concerned Section", mInputWidget);

    inputLayout->addWidget(mNumberOfTrucksLabel, 0, 0);
    inputLayout->addWidget(mNumberOfTrucks, 0, 1);
    inputLayout->addWidget(mTruckPositionIncrementLabel, 1, 0);
    inputLayout->addWidget(mTruckPositionIncrement, 1, 1);
    inputLayout->addWidget(mHeadwayLabel, 2, 0);
    inputLayout->addWidget(mHeadway, 2, 1);
    inputLayout->addWidget(mAxleLoadLabel, 3, 0);
    inputLayout->addWidget(mAxleLoad, 3, 1);
    inputLayout->addWidget(mAxleSpacingLabel, 4, 0);
    inputLayout->addWidget(mAxleSpacing, 4, 1);
    inputLayout->addWidget(mSpanLengthLabel, 5, 0);
    inputLayout->addWidget(mSpanLength, 5, 1);
    inputLayout->addWidget(mConcernedSectionLabel, 6, 0);
    inputLayout->addWidget(mConcernedSection, 6, 1);
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

  // connect window to engine for running commands and drawing chart
  {
    auto &engine = Engine::getInstance();

    // add command for engine to run
    QObject::connect(this, &Window::runCommand, &engine, &Engine::addCommand);

    // collect inputs to run matlab
    QObject::connect(mButton, &QPushButton::clicked, this, [&]() {
      Engine::concernedOneMomentInput in;

      in.number_of_trucks = mNumberOfTrucks->text().toInt();
      in.truck_position_increment = mTruckPositionIncrement->text().toDouble();
      in.headway = mHeadway->text().toInt();

      double temp;
      std::vector<double> tempVec;
      std::stringstream tempStream(mAxleLoad->text().toStdString());
      while (tempStream >> temp) {
        tempVec.push_back(temp);
      }
      in.axle_load = tempVec;

      tempVec.clear();
      tempStream = std::stringstream(mAxleSpacing->text().toStdString());
      while (tempStream >> temp) {
        tempVec.push_back(temp);
      }
      in.axle_spacing = tempVec;

      in.span_length = mSpanLength->text().toInt();
      in.concerned_section = mConcernedSection->text().toInt();

      emit runCommand(in);
    });

    // enable calculate button as soon as matlab is ready to go
    QObject::connect(&engine, &Engine::engineStarted, this,
                     [&]() { mButton->setDisabled(false); });

    // draw chart after command finished
    QObject::connect(
        &engine,
        qOverload<Engine::concernedOneMomentReturn>(&Engine::finishedCommand),
        this, [&](Engine::concernedOneMomentReturn ret) {
          std::vector<double> x_vals;
          for (int i = 0; i < ret.moment.size(); i++) {
            x_vals.push_back(i * ret.input.truck_position_increment);
          }
          std::vector<double> y_vals = ret.moment;
          mSeries = new QLineSeries(mChart);
          for (int i = 0; i < x_vals.size(); i++) {
            mSeries->append(x_vals[i], y_vals[i]);
          }
          mChart->removeAllSeries();
          mChart->addSeries(mSeries);
          mChart->setTitle(QString("Concerned section moment at %1 meters")
                               .arg(ret.input.concerned_section));
          mChart->createDefaultAxes();
          mChart->axes(Qt::Vertical).first()->setReverse(true);
          mChart->axes(Qt::Vertical)
              .first()
              ->setTitleText(QString("Moment at Concerned Section (kNm)"));
          mChart->axes(Qt::Horizontal)
              .first()
              ->setTitleText(QString("First Axle Position (m)"));
          update();
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