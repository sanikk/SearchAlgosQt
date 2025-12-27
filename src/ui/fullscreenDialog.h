#include <QDialog>
#include <QWidget>
#include <QGraphicsView>
#include <QPushButton>
#include <qnamespace.h>
#include <QBoxLayout>
#include <QScrollArea>
#include <qscrollarea.h>

class FullscreenDialog : public QDialog {
public:
    FullscreenDialog(QScrollArea *scroll);
    FullscreenDialog(QGraphicsView *view);
    QPushButton *runAstarButton;
    QPushButton *runFringeButton;
    QPushButton *showHideAstarButton;
    QPushButton *showHideFringeButton;
    QPushButton *exitFullscreenButton;
private:
    QGraphicsView *view;
    QScrollArea *scroll;
};
