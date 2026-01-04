#pragma once
#include "retval.h"
#include <QObject>


class SearchSignals : public QObject {

    Q_OBJECT;

signals:
    void visit(int x, int y);
    void expand(int x, int y);
    void finished(RetVal ret);
};
