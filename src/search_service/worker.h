#pragma once
#include "search_service.h"
#include <QObject>

class WorkerRunner : QObject {
public:
    WorkerRunner(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap, SearchService* search_service);
};


class AstarWorker: public QObject {

    Q_OBJECT

signals:
    void visit_node(int x, int y);
    void expand_node(int x, int y);
    void finished();

public:
    AstarWorker(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap);
    void run();

    int startx, starty, goalx, goaly;
    const std::vector<std::string>& citymap;
};
