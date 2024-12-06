#pragma once
#include "scenario_controls.h"
#include "scenario_service.h"
#include <QtLogging>
#include <QWidget>


class SearchTab : public QWidget {
    Q_OBJECT;

public:
    SearchTab(ScenarioService& i_scenario_service);
private:
    virtual void performSearch(const int scenario_index) {}
    virtual QString buttonText() const { return "Perform X Search"; }

    // QWidget *common_area;
    ScenarioControls *scenario_controls;
    // d create_common_area();

    const ScenarioService& scenario_service;
    
    int expanded=0,visited=0;
    double flimit=0.0;

};

class AstarTab : public SearchTab {
public:
    AstarTab(ScenarioService& i_scenario_service);
private:
    void performSearch(const int scenario_index) override {
        qDebug() << "performing Astar search for scenario " << scenario_index;
    }
};

class FringeTab : public SearchTab {
public:
    FringeTab(ScenarioService& i_scenario_service);
private:
    void performSearch(const int scenario_index) override {
        qDebug() << "performing Fringe search for scenario " << scenario_index;
    }
};

