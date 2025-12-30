#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QScrollArea>

class FullscreenDialog : public QDialog {
public:
    FullscreenDialog(QScrollArea *scroll);
    QPushButton *runAstarButton;
    QPushButton *runFringeButton;
    QPushButton *showHideAstarButton;
    QPushButton *showHideFringeButton;
    QPushButton *exitFullscreenButton;
private:
    QScrollArea *scroll;
};
