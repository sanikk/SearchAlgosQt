#include "worker.h"

#include <QThread>


WorkerRunner::WorkerRunner(int startx, int starty, int goalx, int goaly, 
                           const std::vector<std::string>& citymap, 
                           SearchService* search_service) {

  QThread* thread = new QThread;
  AstarWorker* worker = new AstarWorker{startx, starty, goalx, goaly, citymap};

  worker->moveToThread(thread);

  connect(thread, &QThread::started, worker, &AstarWorker::run);
  connect(worker, &AstarWorker::finished, thread, &QThread::quit);
  connect(worker, &AstarWorker::finished, worker, &QObject::deleteLater);
  connect(thread, &QThread::finished, thread, &QObject::deleteLater);
  
  connect(worker, &AstarWorker::visit_node, search_service, &SearchService::astarVisit, Qt::QueuedConnection);
  connect(worker, &AstarWorker::expand_node, search_service, &SearchService::astarExpand, Qt::QueuedConnection);

  thread->start();
}





AstarWorker::AstarWorker(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap)
: startx(startx), starty(starty), goalx(goalx), goaly(goaly), citymap(citymap) {}
    


void AstarWorker::run() {
  for (int i=0; i < 100; i++) {
    emit visit_node(i, i);
    emit expand_node(i+1, i+1);
    QThread::msleep(20);
  }
  emit finished();

}
