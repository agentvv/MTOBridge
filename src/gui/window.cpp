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

    mNumberSpans = new QLineEdit("2", this);
    mNumberSpansLabel = new QLabel("Number of Spans", this);

    mSpanLength = new QLineEdit("20 20", this);
    mSpanLengthLabel = new QLabel("Span Length(m)", this);

    mConcernedSection = new QLineEdit("10", this);
    mConcernedSectionLabel = new QLabel("Concerned Section(m)", this);

    mDiscretizationLength = new QLineEdit("0.1", this);
    mDiscretizationLengthLabel =
        new QLabel("Discretization Length(m)", this);

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

    QObject::connect(&engine, &Engine::errorOccurred, this,
                     &Window::errorOccurred);
  }
}

QTabWidget *Window::getTabWidget() { return mTabWidget; }

void Window::errorOccurred(QString error){
    QMessageBox::critical(this, QString("Unknown Error!"), error);
}
};  // namespace mtobridge