#pragma once
#include "search_signals.h"

#include <QObject>
#include <QThread>

#include <vector>
#include <string>

class Worker : public QObject {
    Q_OBJECT

public:
  //Worker(const int startx, const int starty, const int goalx, const int goaly, const std::vector<std::string>& citymap, SearchSignals* search_signals);
  Worker(const int startx, const int starty, const int goalx, const int goaly, const std::vector<std::string>& citymap);
  const int startx, starty, goalx, goaly;
  const std::vector<std::string>& citymap;
  SearchSignals search_signals;

signals:
    void finished();

    void visit(int x, int y);
    void expand(int x, int y);
    void search_finished(int cost);
public slots:
    virtual void run() = 0; 
};


class AstarWorker : public Worker {
    Q_OBJECT

public:
  //AstarWorker(const int startx, const int starty, const int goalx, const int goaly, const std::vector<std::string>& citymap, SearchSignals* search_signals);
  AstarWorker(const int startx, const int starty, const int goalx, const int goaly, 
              const std::vector<std::string>& citymap);

public slots:
  void run() override; 
};


class FringeWorker : public Worker {
    Q_OBJECT

public:
  //FringeWorker(const int startx, const int starty, const int goalx, const int goaly, const std::vector<std::string>& citymap, SearchSignals* search_signals);
  FringeWorker(const int startx, const int starty, const int goalx, const int goaly, 
               const std::vector<std::string>& citymap);

public slots:
    void run() override;  
};
