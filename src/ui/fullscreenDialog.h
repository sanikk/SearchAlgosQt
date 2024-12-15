// so fullscreen works straight on _windows_.
// QDialog and QMainwindow are windows.
// Make a QDialog with view and controls, pop that up and make it fullscreen.
#include <QDialog>
#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>
#include <qnamespace.h>
#include <QBoxLayout>

class FullscreenDialog : public QDialog {
public:
    FullscreenDialog(QGraphicsView *view);
    QPushButton *runAstarButton;
    QPushButton *runFringeButton;
    QPushButton *showHideAstarButton;
    QPushButton *showHideFringeButton;
    QPushButton *exitFullscreenButton;
private:
    QGraphicsView *view;

};



