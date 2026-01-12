#pragma once
#include <QThread>


class SearchThread : public QThread {

  Q_OBJECT

public:
  SearchThread(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap) 
  : startx(startx), starty(starty), goalx(goalx), goaly(goaly), citymap(citymap), QThread() {}
  //SearchSignals search_signals;
  virtual void run() {}

  int startx, starty, goalx, goaly;
  const std::vector<std::string>& citymap;

signals:
  void visit(int x, int y);
  void expand(int x, int y);
  void search_finished(int cost);


};
