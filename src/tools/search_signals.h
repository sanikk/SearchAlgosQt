#pragma once

#include "retval.h"

#include <QObject>

#include <iostream>

class SearchSignals : public QObject {

    Q_OBJECT

public:
    SearchSignals(QObject* parent = nullptr) : QObject(parent) {}
    inline void node_visited(int x, int y) { emit visit(x, y); std::cout << "SearchSignals::visit " << QObject::thread() << std::endl; }
    inline void node_expanded(int x, int y) { emit expand(x, y); }
    inline void search_finished(RetVal ret) { emit finished(ret); }

signals:
    void visit(int x, int y);
    void expand(int x, int y);
    void finished(RetVal ret);
};
