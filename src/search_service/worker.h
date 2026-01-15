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
    //void found_cost(double cost);
    void found_goal(RetVal ret);
    void finished();

public:
    AstarWorker(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap);
    void run();

private:
    int startx, starty, goalx, goaly;
    const std::vector<std::string>& citymap;

    void astar_with_signals();
};
