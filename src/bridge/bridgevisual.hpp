#pragma once
#include <QtWidgets>

#include "bridgeconfig.hpp"

namespace mtobridge {
class BridgeVisual : public QWidget {
  Q_OBJECT

 public:
  BridgeVisual(QWidget* parent = nullptr) : QWidget(parent) { createPage(); }
  ~BridgeVisual() {}

  QGraphicsScene* getScene() { return mScene; }

 public slots:
  void bridgeConfigEdited();


 private:
  void createPage();
  
  QLabel* mSpanLengthLabel;
  QLineEdit* mSpanLength;
  QLabel* mConcernedSectionLabel;
  QLineEdit* mConcernedSection;
  QLabel* mNumberSpansLabel;
  QComboBox* mNumberSpans;
  QLabel* mDiscretizationLengthLabel;
  QLineEdit* mDiscretizationLength;

  // Bridge UI Elements
  QWidget* bridgeInputWidget;
  QWidget* mVisualizerWidget;
  QGraphicsView* mVisualizerView;
  QGraphicsScene* mScene;
  QGraphicsRectItem* bridgeRect;
  QGraphicsRectItem* topLayerRect;
  QPushButton* previewButton;
  QWidget* bridgeIOWidget;
  QPushButton* saveButton;
  QPushButton* loadButton;
  BridgeConfiguration* bridgeConfiguration;
  
};
}  // namespace mtobridge