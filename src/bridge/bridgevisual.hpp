#pragma once
#include <QtWidgets>

#include "bridgeconfig.hpp"

namespace mtobridge {
class bridgevisual : public QWidget {
  Q_OBJECT

 public:
  bridgevisual(QWidget* parent = nullptr) : QWidget(parent) {}
  ~bridgevisual() {}
};
}  // namespace mtobridge