#pragma once
#include "scenario_service.h"
#include <QComboBox>
#include <QtLogging>
#include <QWidget>



class SearchTab : public QWidget {
    Q_OBJECT;

public:
    SearchTab(const ScenarioService& i_scenario_service);
private:
    virtual void performSearch(const int scenario_index) {}
    virtual QString buttonText() const { return "Perform X Search"; }

    QWidget *common_area;
    QComboBox *bucket_box;
    QComboBox *scenario_box;
    void create_common_area();
    const ScenarioService& scenario_service;
    int expanded=0,visited=0;
    double flimit=0.0;

};

class AstarTab : public SearchTab {
public:
    AstarTab(const ScenarioService& i_scenario_service);
private:
    void performSearch(const int scenario_index) override {
        qDebug() << "performing Astar search for scenario " << scenario_index;
    }
};

class FringeTab : public SearchTab {
public:
    FringeTab(const ScenarioService& i_scenario_service);
private:
    void performSearch(const int scenario_index) override {
        qDebug() << "performing Fringe search for scenario " << scenario_index;
    }
};
