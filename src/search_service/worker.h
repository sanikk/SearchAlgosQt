#pragma once
#include "search_service.h"
#include "retval.h"
#include <QObject>


/// Thin runner for Worker objects, used with the visual searches. Sets up Worker signal connections to SearchService slots.
class WorkerRunner : QObject {
public:
    WorkerRunner() {}
    void run_astar(int startx, int starty, int goalx, int goaly, int width, int height, const std::vector<uint8_t>& citymap, SearchService* search_service);
    void run_fringe(int startx, int starty, int goalx, int goaly, int width, int height, const std::vector<uint8_t>& citymap, SearchService* search_service);
};



/// Abstact base class for AstarWorker and FringeWorker. Sets members, provides signals.
class Worker: public QObject {
    Q_OBJECT

signals:
    void visit_node(int x, int y);
    void expand_node(int x, int y);
    void found_goal(RetVal ret);
    void finished();

public: 
    Worker(int startx, int starty, int goalx, int goaly, int map_width, int map_height, const std::vector<uint8_t>& citymap);
    virtual void run() {};
protected:
    int startx, starty, goalx, goaly, map_width, map_height;
    const std::vector<uint8_t>& citymap;

};





/// Runs A* in another thread, sending signals.
class AstarWorker: public Worker {

    Q_OBJECT


public:
    AstarWorker(int startx, int starty, int goalx, int goaly, int map_width, int map_height, const std::vector<uint8_t>& citymap);
    void run() override;

private:
    void astar_with_signals();
};





/// Runs Fringe search in another thread, sending signals.
class FringeWorker: public Worker {

    Q_OBJECT


public:
    FringeWorker(int startx, int starty, int goalx, int goaly, int map_width, int map_height, const std::vector<uint8_t>& citymap);
    void run() override;

private:
    void fringe_with_signals();
};
