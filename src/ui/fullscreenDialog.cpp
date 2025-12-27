#include "fullscreenDialog.h"
#include <qscrollarea.h>

FullscreenDialog::FullscreenDialog(QGraphicsView *view) : QDialog(), view(view)
{
  setAttribute(Qt::WA_DeleteOnClose);
  QVBoxLayout *mainLayout = new QVBoxLayout{};
  
  QWidget *controlsBox = new QWidget{};

  QHBoxLayout * boxLayout = new QHBoxLayout{};
  runAstarButton = new QPushButton{ "Run A*" };
  boxLayout->addWidget(runAstarButton);
  runFringeButton = new QPushButton{ "Run Fringe" };
  boxLayout->addWidget(runFringeButton);
  showHideAstarButton = new QPushButton{"Hide A*"};
  boxLayout->addWidget(showHideAstarButton);
  showHideFringeButton = new QPushButton{"Hide Fringe"};
  boxLayout->addWidget(showHideFringeButton);
  exitFullscreenButton = new QPushButton{"Exit fullscreen"};
  boxLayout->addWidget(exitFullscreenButton);
  controlsBox->setLayout(boxLayout);

  mainLayout->addWidget(controlsBox);
  mainLayout->addWidget(view);
  setLayout(mainLayout);
  connect(exitFullscreenButton, &QPushButton::clicked, this, &QDialog::close);
}

FullscreenDialog::FullscreenDialog(QScrollArea *scroll) : QDialog(), scroll(scroll)
{
  setAttribute(Qt::WA_DeleteOnClose);
  QVBoxLayout *mainLayout = new QVBoxLayout{};
  
  QWidget *controlsBox = new QWidget{};

  QHBoxLayout * boxLayout = new QHBoxLayout{};
  runAstarButton = new QPushButton{ "Run A*" };
  boxLayout->addWidget(runAstarButton);
  runFringeButton = new QPushButton{ "Run Fringe" };
  boxLayout->addWidget(runFringeButton);
  showHideAstarButton = new QPushButton{"Hide A*"};
  boxLayout->addWidget(showHideAstarButton);
  showHideFringeButton = new QPushButton{"Hide Fringe"};
  boxLayout->addWidget(showHideFringeButton);
  exitFullscreenButton = new QPushButton{"Exit fullscreen"};
  boxLayout->addWidget(exitFullscreenButton);
  controlsBox->setLayout(boxLayout);

  mainLayout->addWidget(controlsBox);
  mainLayout->addWidget(scroll);
  setLayout(mainLayout);
  connect(exitFullscreenButton, &QPushButton::clicked, this, &QDialog::close);
}
