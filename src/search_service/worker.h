#pragma once
#include "search_service.h"
#include "models.h"
#include <QObject>


class WorkerRunner : QObject {
public:
    WorkerRunner();
    void run_astar(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap, SearchService* search_service);
    void run_fringe(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap, SearchService* search_service);
};




class Worker: public QObject {
    Q_OBJECT

signals:
    void visit_node(int x, int y);
    void expand_node(int x, int y);
    void found_goal(RetVal ret);
    void finished();

public: 
    Worker(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap);
    virtual void run() {};

    int startx, starty, goalx, goaly;
    const std::vector<std::string>& citymap;

};






class AstarWorker: public Worker {

    Q_OBJECT


public:
    AstarWorker(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap);
    void run() override;

private:
    void astar_with_signals();
};






class FringeWorker: public Worker {

    Q_OBJECT


public:
    FringeWorker(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap);
    void run() override;

private:
    void fringe_with_signals();
};
