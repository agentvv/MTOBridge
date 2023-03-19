#include "solverVisual.hpp"

#include "../PlatoonConfiguration/PlatoonConfiguration.hpp"
#include "../engine/engine.hpp"
#include "../saver/loader.hpp"
#include "../saver/saver.hpp"
#include "solver.hpp"

namespace mtobridge {
void SolverVisual::visualize() {}

void SolverVisual::errorOccurred(QString error) {
  QMessageBox::critical(this, QString("Error!"), error);
}

void SolverVisual::createPage() {
  setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                            QSizePolicy::Policy::Expanding));
  QVBoxLayout* pageLayout = new QVBoxLayout();
  setLayout(pageLayout);

  QWidget* topHalf = new QWidget(this);
  QHBoxLayout* topHalfLayout = new QHBoxLayout();
  topHalf->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                     QSizePolicy::Policy::Expanding));
  topHalf->setLayout(topHalfLayout);

  // set up chart
  {
    auto* chartLayout = new QGridLayout();
    QWidget* mChartWidget = new QWidget(this);
    mChartWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                            QSizePolicy::Policy::Expanding));
    mChartWidget->setLayout(chartLayout);

    // QChart* mChart = new QChart();
    mChart = new QChart();
    mChart->legend()->hide();
    mChart->createDefaultAxes();

    mChartView = new QChartView(mChart, mChartWidget);
    mChartView->setRenderHint(QPainter::Antialiasing);
    mChartView->resize(300, 300);
    mChartView->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                          QSizePolicy::Policy::Expanding));

    mEnvelopeChart = new QChart();
    mEnvelopeChart->legend()->hide();
    mEnvelopeChart->createDefaultAxes();

    mEnvelopeChartView = new QChartView(mEnvelopeChart, nullptr);
    mEnvelopeChartView->setRenderHint(QPainter::Antialiasing);
    mEnvelopeChartView->resize(300, 300);
    mEnvelopeChartView->setSizePolicy(QSizePolicy(
        QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));

    chartLayout->addWidget(mChartView, 0, 0);
    topHalfLayout->addWidget(mChartWidget);
  }

  QVBoxLayout* inputLayout = new QVBoxLayout();
  QWidget* mInputWidget = new QWidget(this);
  mInputWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                          QSizePolicy::Policy::Expanding));
  mInputWidget->setLayout(inputLayout);
  mInputWidget->setFixedWidth(200);

  this->saveLoadGroup = new QGroupBox("Save/Load From File", this);
  inputLayout->addWidget(this->saveLoadGroup);
  QVBoxLayout* saveLoadBox = new QVBoxLayout;
  this->saveLoadGroup->setLayout(saveLoadBox);
  QPushButton* saveButton = new QPushButton("Save Solver Configuration", this);
  QObject::connect(saveButton, &QPushButton::clicked, this, [&]() {
    MockSolverT config;
    if (Solver::getForceType() == "Positive Moment") {
      config.forceType = MockSolverT::POSITIVE_MOMENT;
    } else if (Solver::getForceType() == "Negative Moment") {
      config.forceType = MockSolverT::NEGATIVE_MOMENT;
    } else if (Solver::getForceType() == "Shear") {
      config.forceType = MockSolverT::SHEAR;
    }

    if (Solver::getSolverType() == "Concerned Section") {
      config.solverType = MockSolverT::CONCERNED;
    } else if (Solver::getSolverType() == "Critical Section") {
      config.solverType = MockSolverT::CRITICAL;
    }

    saver::saveSolverConfiguration(config);
  });

  saveLoadBox->addWidget(saveButton);
  QPushButton* loadButton = new QPushButton("Load Solver Configuration", this);

  QObject::connect(loadButton, &QPushButton::clicked, this, [&]() {
    MockSolverT config = loader::loadSolverConfiguration();
    if (config.forceType == MockSolverT::POSITIVE_MOMENT) {
      Solver::updateForceType("Positive Moment");
    } else if (config.forceType == MockSolverT::NEGATIVE_MOMENT) {
      Solver::updateForceType("Negative Moment");
    } else if (config.forceType == MockSolverT::SHEAR) {
      Solver::updateForceType("Shear");
    }

    if (config.solverType == MockSolverT::CONCERNED) {
      Solver::updateSolverType("Concerned Section");
    } else if (config.solverType == MockSolverT::CRITICAL) {
      Solver::updateSolverType("Critical Section");
    }
    updatePage();
  });

  saveLoadBox->addWidget(loadButton);
  saveLoadBox->addStretch(1);
  this->saveLoadGroup->setFixedHeight(100);

  this->forceSettingGroup = new QGroupBox("Force Type", this);
  inputLayout->addWidget(this->forceSettingGroup);
  QVBoxLayout* forceBox = new QVBoxLayout;
  this->forceSettingGroup->setLayout(forceBox);
  positiveMomentButton = new QRadioButton("Positive Moment");
  positiveMomentButton->setChecked(true);
  QObject::connect(positiveMomentButton, &QPushButton::clicked, this,
                   [&]() { Solver::updateForceType("Positive Moment"); });
  forceBox->addWidget(positiveMomentButton);
  negativeMomentButton = new QRadioButton("Negative Moment");
  QObject::connect(negativeMomentButton, &QPushButton::clicked, this,
                   [&]() { Solver::updateForceType("Negative Moment"); });
  forceBox->addWidget(negativeMomentButton);
  shearButton = new QRadioButton("Shear");
  QObject::connect(shearButton, &QPushButton::clicked, this,
                   [&]() { Solver::updateForceType("Shear"); });
  forceBox->addWidget(shearButton);
  forceBox->addStretch(1);
  this->forceSettingGroup->setFixedHeight(100);

  this->solverSettingGroup = new QGroupBox("Solver Type", this);
  inputLayout->addWidget(this->solverSettingGroup);
  QVBoxLayout* solverBox = new QVBoxLayout;
  this->solverSettingGroup->setLayout(solverBox);
  concernedButton = new QRadioButton("Concerned Section");
  concernedButton->setChecked(true);
  QObject::connect(concernedButton, &QPushButton::clicked, this,
                   [&]() { Solver::updateSolverType("Concerned Section"); });
  solverBox->addWidget(concernedButton);
  criticalButton = new QRadioButton("Critical Section");
  QObject::connect(criticalButton, &QPushButton::clicked, this,
                   [&]() { Solver::updateSolverType("Critical Section"); });
  solverBox->addWidget(criticalButton);
  solverBox->addStretch(1);
  this->solverSettingGroup->setFixedHeight(75);

  this->calculateButton = new QPushButton("Initialising...", this);
  this->calculateButton->setDisabled(true);
  QObject::connect(this->calculateButton, &QPushButton::clicked, this, [&]() {
    this->calculateButton->setDisabled(true);
    this->calculateButton->setText("Analysing...");
    MockCalculationInputT in;

    std::list<double> tempList = PlatoonConfiguration::getAxleLoads();
    in.truckConfig.axleLoad = {std::begin(tempList), std::end(tempList)};
    tempList = PlatoonConfiguration::getAxleSpacings();
    in.truckConfig.axleSpacing = {std::begin(tempList), std::end(tempList)};
    in.truckConfig.numberOfTrucks = PlatoonConfiguration::getNumTrucks();
    in.truckConfig.headway = PlatoonConfiguration::getHeadway();

    BridgeT bridgeConfig = BridgeConfiguration::getConfiguration();
    in.bridgeConfig.numberSpans = bridgeConfig.numberSpans;
    in.bridgeConfig.spanLength = bridgeConfig.spanLength;
    in.bridgeConfig.concernedSection = bridgeConfig.concernedSection;
    in.bridgeConfig.discretizationLength = bridgeConfig.discretizationLength;

    if (Solver::getForceType() == "Positive Moment") {
      in.solverConfig.forceType = MockSolverT::POSITIVE_MOMENT;
    } else if (Solver::getForceType() == "Negative Moment") {
      in.solverConfig.forceType = MockSolverT::NEGATIVE_MOMENT;
    } else if (Solver::getForceType() == "Shear") {
      in.solverConfig.forceType = MockSolverT::SHEAR;
    }

    if (Solver::getSolverType() == "Concerned Section") {
      in.solverConfig.solverType = MockSolverT::CONCERNED;
    } else if (Solver::getSolverType() == "Critical Section") {
      in.solverConfig.solverType = MockSolverT::CRITICAL;
    }
    emit SolverVisual::runCommand(in);
  });
  inputLayout->addWidget(this->calculateButton);
  topHalfLayout->addWidget(mInputWidget);
  pageLayout->addWidget(topHalf);

  this->saveButton = new QPushButton("Generate Report", this);
  this->saveButton->setDisabled(true);
  QObject::connect(this->saveButton, &QPushButton::clicked, this, [&]() {
    this->saveButton->setDisabled(true);
    mtobridge::saver::saveReport(mReport);
    this->saveButton->setDisabled(false);
  });
  inputLayout->addWidget(this->saveButton);

  QWidget* bottomHalf = new QWidget(this);
  QVBoxLayout* truckBridgeLayout = new QVBoxLayout;
  bottomHalf->setLayout(truckBridgeLayout);
  bottomHalf->setFixedHeight(160);
  truckVisual = new QGraphicsView(this);
  truckVisual->setFixedHeight(80);
  bridgeVisual = new QGraphicsView(this);
  bridgeVisual->setFixedHeight(65);
  truckBridgeLayout->addWidget(truckVisual);
  truckBridgeLayout->addWidget(bridgeVisual);
  pageLayout->addWidget(bottomHalf);

  auto& engine = Engine::getInstance();

  // add command for engine to run
  QObject::connect(this, &SolverVisual::runCommand, &engine,
                   &Engine::runCommand);

  // enable buttons as soon as matlab is ready to go
  QObject::connect(&engine, &Engine::engineStarted, this, [&]() {
    this->calculateButton->setText("Run Analysis");
    this->calculateButton->setDisabled(false);
    this->saveButton->setDisabled(false);
  });

  // draw chart after command finished
  QObject::connect(&engine, &Engine::finishedCommand, this,
                   &SolverVisual::updateChart);
}

void SolverVisual::updatePage() {
  positiveMomentButton->setChecked(false);
  negativeMomentButton->setChecked(false);
  shearButton->setChecked(false);
  concernedButton->setChecked(false);
  criticalButton->setChecked(false);

  if (Solver::getForceType() == "Positive Moment") {
    positiveMomentButton->setChecked(true);
  } else if (Solver::getForceType() == "Negative Moment") {
    negativeMomentButton->setChecked(true);
  } else if (Solver::getForceType() == "Shear") {
    shearButton->setChecked(true);
  }

  if (Solver::getSolverType() == "Concerned Section") {
    concernedButton->setChecked(true);
  } else if (Solver::getSolverType() == "Critical Section") {
    criticalButton->setChecked(true);
  }
}

void SolverVisual::updateChart(MockCalculationInputT in,
                               MockCalculationOutputT out) {
  this->mReport.input = in;
  this->mReport.results = out;
  std::vector<double> x_vals = std::move(out.firstAxlePosition);
  std::vector<double> y_vals;
  if (in.solverConfig.solverType == MockSolverT::CONCERNED) {
    y_vals = std::move(out.forceConcernedSection);
  } else {
    y_vals = std::move(out.forceCriticalSection);
  }

  QLineSeries* mSeries = new QLineSeries(mChart);
  for (int i = 0; i < x_vals.size(); i++) {
    mSeries->append(QPointF(x_vals[i], y_vals[i]));
  }

  mChart->removeAllSeries();
  for (auto& axis : mChart->axes()) {
    mChart->removeAxis(axis);
  }
  mChart->addSeries(mSeries);
  QString force;
  if (in.solverConfig.forceType == MockSolverT::POSITIVE_MOMENT) {
    force = "Positive Moment";
  } else if (in.solverConfig.forceType == MockSolverT::NEGATIVE_MOMENT) {
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

  if (in.solverConfig.solverType == CRITICAL) {
    x_vals = std::move(out.sections);
    y_vals = std::move(out.forceEnvelope);

    QLineSeries* series = new QLineSeries(mEnvelopeChart);
    for (int i = 0; i < x_vals.size(); i++) {
      series->append(QPointF(x_vals[i], y_vals[i]));
    }

    mEnvelopeChart->removeAllSeries();
    for (auto& axis : mEnvelopeChart->axes()) {
      mEnvelopeChart->removeAxis(axis);
    }
    mEnvelopeChart->addSeries(series);

    mEnvelopeChart->createDefaultAxes();
    mEnvelopeChart->axes(Qt::Horizontal).first()->setMin(x_vals.front());
    mEnvelopeChart->axes(Qt::Horizontal).first()->setMax(x_vals.back());

    mEnvelopeChart->axes(Qt::Vertical)
        .first()
        ->setMin(*std::min_element(y_vals.begin(), y_vals.end()));
    mEnvelopeChart->axes(Qt::Vertical)
        .first()
        ->setMax(*std::max_element(y_vals.begin(), y_vals.end()));

    mEnvelopeChartView->setChart(mEnvelopeChart);
  }

  this->calculateButton->setText("Run Analysis");
  this->calculateButton->setDisabled(false);
}

void SolverVisual::setPlatoon(QGraphicsScene* platoon) {
  truckVisual->setScene(platoon);
}

void SolverVisual::setBridge(QGraphicsScene* bridge) {
  bridgeVisual->setScene(bridge);
}
};  // namespace mtobridge