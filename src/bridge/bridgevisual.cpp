#include "bridgevisual.hpp"

#include "../saver/loader.hpp"
#include "../saver/saver.hpp"
using namespace std;

namespace mtobridge {
void BridgeVisual::createPage() {
  this->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                  QSizePolicy::Policy::Expanding));
  auto* bridgePageLayout = new QVBoxLayout();
  this->setLayout(bridgePageLayout);

  // bridge input section
  {
    auto* bridgeInputLayout = new QGridLayout();
    QWidget* bridgeInputWidget = new QWidget(this);
    bridgeInputWidget->setSizePolicy(QSizePolicy(
        QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
    bridgeInputWidget->setLayout(bridgeInputLayout);
    mNumberSpans = new QComboBox(this);
    mNumberSpans->addItem("1");
    mNumberSpans->addItem("2");
    mNumberSpans->addItem("3");
    
    mNumberSpansLabel = new QLabel("Number of Spans", this);

    mSpanLength = new QLineEdit("20 20", this);
    mSpanLengthLabel = new QLabel("Span Length(m)", this);

    mConcernedSection = new QLineEdit("10", this);
    mConcernedSectionLabel = new QLabel("Concerned Section(m)", this);

    mDiscretizationLength = new QLineEdit("0.1", this);
    mDiscretizationLengthLabel = new QLabel("Discretization Length(m)", this);

    bridgeInputLayout->addWidget(mNumberSpansLabel, 1, 0);
    bridgeInputLayout->addWidget(mNumberSpans, 1, 1);
    bridgeInputLayout->addWidget(mSpanLengthLabel, 2, 0);
    bridgeInputLayout->addWidget(mSpanLength, 2, 1);
    bridgeInputLayout->addWidget(mConcernedSectionLabel, 3, 0);
    bridgeInputLayout->addWidget(mConcernedSection, 3, 1);
    bridgeInputLayout->addWidget(mDiscretizationLengthLabel, 4, 0);
    bridgeInputLayout->addWidget(mDiscretizationLength, 4, 1);
    bridgePageLayout->addWidget(bridgeInputWidget);
  }

  // bridge visualizer
  auto* visualizerLayout = new QGridLayout();
  mVisualizerWidget = new QWidget(this);
  mVisualizerWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                               QSizePolicy::Policy::Expanding));

  mVisualizerWidget->setLayout(visualizerLayout);

  mVisualizerView = new QGraphicsView(mVisualizerWidget);
  mScene = new QGraphicsScene(this);
  mVisualizerView->setScene(mScene);
  visualizerLayout->addWidget(mVisualizerView, 0, 0);

  previewButton = new QPushButton("Preview", this);
  visualizerLayout->addWidget(previewButton, 1, 0);

  bridgePageLayout->addWidget(mVisualizerWidget);

  // bridge IO section
  auto* bridgeIOLayout = new QGridLayout();
  bridgeIOWidget = new QWidget(this);
  bridgeIOWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                            QSizePolicy::Policy::Expanding));
  bridgeIOWidget->setLayout(bridgeIOLayout);

  saveButton = new QPushButton("Save Config", this);
  bridgePageLayout->addWidget(saveButton);

  loadButton = new QPushButton("Load Config", this);
  bridgePageLayout->addWidget(loadButton);

  // connect window to engine for running commands and drawing chart
  {
    QObject::connect(previewButton, &QPushButton::clicked, this, [&]() {
      // QMessageBox::about(this, "Title", "Button Clicked");
      mScene->clear();
      BridgeConfiguration::updateNumberOfSpans(mNumberSpans->currentText());
      BridgeConfiguration::updateConcernedSection(mConcernedSection->text());
      BridgeConfiguration::updateSpanLength(mSpanLength->text());
      BridgeConfiguration::updateDiscretizationLength(
          mDiscretizationLength->text());
      BridgeT configBridge = BridgeConfiguration::getConfiguration();

      QBrush grayBrush(Qt::gray);
      QBrush redBrush(Qt::red);
      QBrush blackBrush(Qt::blue);
      QPen blackpen(Qt::black);
      blackpen.setWidthF(1);
      QPen redpen(Qt::red);
      redpen.setWidthF(0.1);

      double bridgeLength = 0;
      int scale = 5;
      int topLayerWidth = 5;
      mScene->addRect(0, topLayerWidth, 8 * topLayerWidth, 7 * topLayerWidth, blackpen, grayBrush);
      bridgeLength += 4 * topLayerWidth; //Sketching first abutment

      for (int i = 0; i < configBridge.numberSpans; i++) {
          bridgeLength += configBridge.spanLength[i] * scale;
          if (i != configBridge.numberSpans - 1) {
              mScene->addRect((bridgeLength - 2 * topLayerWidth), 3 * topLayerWidth, 4 * topLayerWidth, 5 * topLayerWidth, blackpen,
                  grayBrush);  // Sketching the columns
          }
          //string test = to_string(configBridge.spanLength[i]);
          //wstring stemp = wstring(test.begin(), test.end());
          //LPCWSTR sw = stemp.c_str();
          //MessageBox(NULL, sw, NULL, MB_OK);
       }
      
      mScene->addRect((bridgeLength - 4 * topLayerWidth), topLayerWidth, 8 * topLayerWidth, 7 * topLayerWidth, blackpen, grayBrush);
      bridgeLength += 4 * topLayerWidth; //Sketching second abutment

      mScene->addRect(0, 0, bridgeLength , topLayerWidth, blackpen, blackBrush);
      mScene->addRect(4 * topLayerWidth, topLayerWidth, (bridgeLength - 8 * topLayerWidth), 2 * topLayerWidth, blackpen, redBrush);

      //for (double i = configBridge.discretizationLength * scale;
      //     i < bridgeLength * scale;
      //     i = i + configBridge.discretizationLength * scale) {
      //  mScene->addLine(i, 0, i, 20, redpen);
      //}
    });

    QObject::connect(saveButton, &QPushButton::clicked, this, [&]() {
      BridgeConfiguration::updateNumberOfSpans(mNumberSpans->currentText());
      BridgeConfiguration::updateConcernedSection(mConcernedSection->text());
      BridgeConfiguration::updateSpanLength(mSpanLength->text());
      BridgeConfiguration::updateDiscretizationLength(
          mDiscretizationLength->text());
      saver::saveBridgeConfiguration(BridgeConfiguration::getConfiguration());
    });

    QObject::connect(loadButton, &QPushButton::clicked, this, [&]() {
      BridgeT config = loader::loadBridgeConfiguration();
      mNumberSpans->setCurrentText(QString::number(config.numberSpans));
      QString temp = "";
      for (double i : config.spanLength) {
        temp += QString::number(i) + " ";
      }
      mSpanLength->setText(temp);
      mDiscretizationLength->setText(
          QString::number(config.discretizationLength));
      mConcernedSection->setText(QString::number(config.concernedSection));
    });
  }
}
}  // namespace mtobridge
