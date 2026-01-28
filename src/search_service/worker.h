#pragma once
#include "search_service.h"
#include "retval.h"
#include <QObject>


class WorkerRunner : QObject {
public:
    WorkerRunner();
    void run_astar(int startx, int starty, int goalx, int goaly, int width, int height, const std::vector<uint8_t>& citymap, SearchService* search_service);
    void run_fringe(int startx, int starty, int goalx, int goaly, int width, int height, const std::vector<uint8_t>& citymap, SearchService* search_service);
};




class Worker: public QObject {
    Q_OBJECT

signals:
    void visit_node(int x, int y);
    void expand_node(int x, int y);
    void found_goal(RetVal ret);
    void finished();

public: 
    Worker(int startx, int starty, int goalx, int goaly, int width, int height, const std::vector<uint8_t>& citymap);
    virtual void run() {};
protected:
    int startx, starty, goalx, goaly, width, height;
    const std::vector<uint8_t>& citymap;

};






class AstarWorker: public Worker {

    Q_OBJECT


public:
    AstarWorker(int startx, int starty, int goalx, int goaly, int width, int height, const std::vector<uint8_t>& citymap);
    void run() override;

private:
    void astar_with_signals();
};






class FringeWorker: public Worker {

    Q_OBJECT


public:
    FringeWorker(int startx, int starty, int goalx, int goaly, int width, int height, const std::vector<uint8_t>& citymap);
    void run() override;

private:
    void fringe_with_signals();
};
