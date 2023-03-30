#include "bridgevisual.hpp"
#include "bridgevisual.hpp"

#include "../saver/loader.hpp"
#include "../saver/saver.hpp"
using namespace std;

namespace mtobridge {
    bool isNumber(string str) {
        bool isNumber = true;
        for (char c : str)
        {
            if (!std::isdigit(c) && c != '.')
            {
                isNumber = false;
                break;
            }
        }
        return isNumber;
    }

void BridgeVisual::spanLengthChanged() {
    if (!isNumber(mSpanLength->text().toStdString())){
        mSpanLengthErrorLabel->setVisible(true);
    }
    else
    {
        mSpanLengthErrorLabel->setVisible(false);
        BridgeVisual::bridgeConfigEdited();
    }
}

void BridgeVisual::concernedSectionChanged() {
    if (!isNumber(mConcernedSection->text().toStdString())) {
        mConcernedSectionErrorLabel->setText("Concerned section is a single positive real number.");
        mConcernedSectionErrorLabel->setVisible(true);
        return;
    }

    else {
        mConcernedSectionErrorLabel->setVisible(false);
        BridgeVisual::bridgeConfigEdited();
    }
}

void BridgeVisual::discretizationLengthChanged() {
    if (!isNumber(mDiscretizationLength->text().toStdString())) {
        mDiscretizationLengthErrorLabel->setText("Discretization Length is a single positive real number.");
        mDiscretizationLengthErrorLabel->setVisible(true);
        return;
    }
    else {
        mDiscretizationLengthErrorLabel->setVisible(false);
        BridgeVisual::bridgeConfigEdited();
    }
}

void BridgeVisual::bridgeConfigEdited() {

    bool spanLengthsGiven = true;
    for (int i = 0; i < spanLengthLineBoxes.size(); i++) {
        if (spanLengthLineBoxes[i]->text() == "") {
            spanLengthsGiven = false;
        }
    }
    if (!spanLengthsGiven || mConcernedSection->text() == "" ||
        mDiscretizationLength->text() == "") {
        return;
    }

    bool spanLenghtsAreNumbers = true;
    for (int i = 0; i < spanLengthLineBoxes.size(); i++) {
        if (!isNumber(spanLengthLineBoxes[i]->text().toStdString())) {
            spanLenghtsAreNumbers = false;
        }
    }
    if (!spanLenghtsAreNumbers || !isNumber(mConcernedSection->text().toStdString())
        || !isNumber(mDiscretizationLength->text().toStdString())) {
        return;
    }

    double spanSum = 0;
    for (int i = 0; i < spanLengthLineBoxes.size(); i++) {
        spanSum += std::stod(spanLengthLineBoxes[i]->text().toStdString());
    }
    double concernedSectionValue = std::stod(mConcernedSection->text().toStdString());
    if (concernedSectionValue > spanSum) {
        mConcernedSectionErrorLabel->setText("Concerned section should be less than sum of span lengths.");
        mConcernedSectionErrorLabel->setVisible(true);
        return;
    }

    mScene->clear();

    QString spanLengthsConcatenated = "";
    for (int i = 0; i < spanLengthLineBoxes.size(); i++) {
        if (i == spanLengthLineBoxes.size() - 1) {
            spanLengthsConcatenated += spanLengthLineBoxes[i]->text();
        }
        else {
            spanLengthsConcatenated = spanLengthsConcatenated + spanLengthLineBoxes[i]->text() + " ";
        }
    }

    BridgeConfiguration::updateNumberOfSpans(mNumberSpans->currentText());
    BridgeConfiguration::updateConcernedSection(mConcernedSection->text());
    BridgeConfiguration::updateSpanLength(spanLengthsConcatenated);
    BridgeConfiguration::updateDiscretizationLength(
        mDiscretizationLength->text());
    BridgeT configBridge = BridgeConfiguration::getConfiguration();

    QBrush grayBrush(Qt::gray);
    QBrush blackBrush(Qt::black);
    QBrush darkGrayBrush(Qt::darkGray);
    QBrush lightGrayBrush(Qt::lightGray);
    QPen blackpen(Qt::black);
    blackpen.setWidthF(1);
    QPen redpen(Qt::red);
    redpen.setWidthF(2);

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
    }

    mScene->addRect((bridgeLength - 4 * topLayerWidth), topLayerWidth, 8 * topLayerWidth, 7 * topLayerWidth, blackpen, grayBrush);
    bridgeLength += 4 * topLayerWidth; //Sketching second abutment

    mScene->addRect(0, 0, bridgeLength, topLayerWidth, blackpen, darkGrayBrush); //Sketching the top layer
    QGraphicsRectItem* bridge = mScene->addRect(4 * topLayerWidth, topLayerWidth, (bridgeLength - 8 * topLayerWidth), 2 * topLayerWidth, blackpen, lightGrayBrush);//Sketching the bridge
    bridge->setZValue(1);

    QGraphicsTextItem* text = mScene->addText("Discretization Length: " + mDiscretizationLength->text()); //Indicating Discretization Length
    text->setPos(( bridgeLength - text->boundingRect().width() ) / 2, 8 * topLayerWidth);

    QGraphicsLineItem* concernedLine = mScene->addLine(4 * topLayerWidth + configBridge.concernedSection * scale, topLayerWidth + 1, 4 * topLayerWidth + configBridge.concernedSection * scale, 3 * topLayerWidth - 1, redpen); // Indicating Concerned Section
    concernedLine->setZValue(2);

    this->saveButton->setDisabled(false);
}

void BridgeVisual::numberOfSpansDetermined(QGridLayout* bridgeInputLayout, QString numberOfSpans) {
    int spanLengthsize = spanLengthLineBoxes.size();

    if(spanLengthsize > numberOfSpans.toInt()){
        
        for (int i = numberOfSpans.toInt(); i < spanLengthsize; i++)
        {
            delete spanLengthLineBoxes[spanLengthLineBoxes.size() - 1];
            spanLengthLineBoxes.pop_back();
            delete spanLengthErrorLables[spanLengthErrorLables.size() - 1];
            spanLengthErrorLables.pop_back();
            bridgeConfigEdited();
        }
    }
    else if (spanLengthsize < numberOfSpans.toInt()) {
        for (int i = spanLengthsize; i < numberOfSpans.toInt(); i++) {
            QLineEdit* SpanLengthLineEdit = new QLineEdit(this);
            QLabel* SpanLengthErrorLabel = new QLabel("Span Length is a single positive real number", this);
            SpanLengthErrorLabel->setStyleSheet("QLabel { color : red; }");
            SpanLengthErrorLabel->setVisible(false);
            bridgeInputLayout->addWidget(SpanLengthLineEdit, i + 2, 1);
            bridgeInputLayout->addWidget(SpanLengthErrorLabel, i + 2, 2);
            string index = std::to_string(i);
            QObject::connect(SpanLengthLineEdit, &QLineEdit::editingFinished, this, [=]() {
                if (!isNumber(SpanLengthLineEdit->text().toStdString())) {
                    SpanLengthErrorLabel->setVisible(true);
                }
                else {
                    SpanLengthErrorLabel->setVisible(false);
                    BridgeVisual::bridgeConfigEdited();
                }
                });
            spanLengthLineBoxes.push_back(SpanLengthLineEdit);
            spanLengthErrorLables.push_back(SpanLengthErrorLabel);
            
        }
    }
}

void BridgeVisual::createPage() {
  this->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                  QSizePolicy::Policy::Expanding));
  auto* bridgePageLayout = new QVBoxLayout();
  this->setLayout(bridgePageLayout);

  // bridge input section
  {
    bridgeInputLayout = new QGridLayout();
    QWidget* bridgeInputWidget = new QWidget(this);
    bridgeInputWidget->setSizePolicy(QSizePolicy(
        QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
    bridgeInputWidget->setLayout(bridgeInputLayout);
    mNumberSpans = new QComboBox(this);
    mNumberSpans->addItem("1");
    mNumberSpans->addItem("2");
    mNumberSpans->addItem("3");
    
    mNumberSpansLabel = new QLabel("Number of Spans", this);
    mSpanLength = new QLineEdit(this);
    mSpanLengthLabel = new QLabel("Span Length(m)", this);
    mSpanLengthErrorLabel = new QLabel("Span Length is a single positive real number", this);
    mSpanLengthErrorLabel->setStyleSheet("QLabel { color : red; }");
    mSpanLengthErrorLabel->setVisible(false);

    mConcernedSectionLabel = new QLabel("Concerned Section(m)", this);
    mConcernedSection = new QLineEdit(this);
    mConcernedSectionErrorLabel = new QLabel(this);
    mConcernedSectionErrorLabel->setStyleSheet("QLabel { color : red; }");
    mSpanLengthErrorLabel->setVisible(false);

    mDiscretizationLengthLabel = new QLabel("Discretization Length(m)", this);
    mDiscretizationLength = new QLineEdit(this);
    mDiscretizationLengthErrorLabel = new QLabel(this);
    mDiscretizationLengthErrorLabel->setStyleSheet("QLabel { color : red; }");
    mSpanLengthErrorLabel->setVisible(false);
    

    bridgeInputLayout->addWidget(mNumberSpansLabel, 1, 0);
    bridgeInputLayout->addWidget(mNumberSpans, 1, 1);

    bridgeInputLayout->addWidget(mSpanLengthLabel, 2, 0);
    bridgeInputLayout->addWidget(mSpanLength, 2, 1);
    bridgeInputLayout->addWidget(mSpanLengthErrorLabel, 2, 2);
    spanLengthLineBoxes.push_back(mSpanLength);
    spanLengthErrorLables.push_back(mSpanLengthErrorLabel);
    bridgeInputLayout->addWidget(mConcernedSectionLabel, 5, 0);
    bridgeInputLayout->addWidget(mConcernedSection, 5, 1);
    bridgeInputLayout->addWidget(mConcernedSectionErrorLabel, 5, 2);

    bridgeInputLayout->addWidget(mDiscretizationLengthLabel, 6, 0);
    bridgeInputLayout->addWidget(mDiscretizationLength, 6, 1);
    bridgeInputLayout->addWidget(mDiscretizationLengthErrorLabel, 6, 2);

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

  bridgePageLayout->addWidget(mVisualizerWidget);

  // bridge save\load section
  auto* bridgeIOLayout = new QGridLayout();
  bridgeIOWidget = new QWidget(this);
  bridgeIOWidget->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding,
                                            QSizePolicy::Policy::Expanding));
  bridgeIOWidget->setLayout(bridgeIOLayout);

  saveButton = new QPushButton("Save Config", this);
  bridgePageLayout->addWidget(saveButton);
  saveButton->setDisabled(true);

  loadButton = new QPushButton("Load Config", this);
  bridgePageLayout->addWidget(loadButton);

  //signal handlers
  QObject::connect(mNumberSpans, &QComboBox::currentTextChanged, this, [&]() {
      numberOfSpansDetermined(bridgeInputLayout, mNumberSpans->currentText());
    });
  QObject::connect(mSpanLength, &QLineEdit::editingFinished, this, &BridgeVisual::spanLengthChanged);
  QObject::connect(mConcernedSection, &QLineEdit::editingFinished, this, &BridgeVisual::concernedSectionChanged);
  QObject::connect(mDiscretizationLength, &QLineEdit::editingFinished, this, &BridgeVisual::discretizationLengthChanged);

  QObject::connect(saveButton, &QPushButton::clicked, this, [&]() {
        BridgeConfiguration::updateNumberOfSpans(mNumberSpans->currentText());
        BridgeConfiguration::updateConcernedSection(mConcernedSection->text());
        QString spanLengthsConcatenated = "";
        for (int i = 0; i < spanLengthLineBoxes.size(); i++) {
            if (i == spanLengthLineBoxes.size() - 1) {
                spanLengthsConcatenated += spanLengthLineBoxes[i]->text();
            }
            else {
                spanLengthsConcatenated = spanLengthsConcatenated + spanLengthLineBoxes[i]->text() + " ";
            }
        }
        BridgeConfiguration::updateSpanLength(spanLengthsConcatenated);
        BridgeConfiguration::updateDiscretizationLength(
            mDiscretizationLength->text());

        BridgeT config = BridgeConfiguration::getConfiguration();
        saver::saveBridgeConfiguration(config);
    });
  QObject::connect(loadButton, &QPushButton::clicked, this, [&]() {
      BridgeT config = loader::loadBridgeConfiguration();
      mNumberSpans->setCurrentText(QString::number(config.numberSpans));
      int spanLengthCounter = 0;
      for (double i : config.spanLength) {
        spanLengthLineBoxes[spanLengthCounter]->setText(QString::number(i));
        spanLengthCounter += 1;
      }
      
      mDiscretizationLength->setText(
          QString::number(config.discretizationLength));
      mConcernedSection->setText(QString::number(config.concernedSection));
      bridgeConfigEdited();
    });

}
}  // namespace mtobridge
