#pragma once
#include "scenario_controls.h"
#include "scenario_service.h"
#include "search_service.h"
#include <QBoxLayout>
#include <QComboBox>
#include <QWidget>


class SearchTab : public QWidget {
    Q_OBJECT;

public:
    SearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls& i_scenario_controls);
private:
    virtual void performSearch(const int scenario_index) {}
    virtual QString buttonText() const { return "Perform X Search"; }

    const ScenarioService& scenario_service;
    SearchService& search_service;
    ScenarioControls& scenario_controls;
    
    int expanded=0,visited=0;
    double flimit=0.0;

};

class AstarTab : public SearchTab {
public:
    AstarTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls& i_scenario_controls);
private:
    void performSearch(const int scenario_index) override {
        qDebug() << "performing Astar search for scenario " << scenario_index;
    }
};

class FringeTab : public SearchTab {
public:
    FringeTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls& i_scenario_controls);
private:
    void performSearch(const int scenario_index) override {
        qDebug() << "performing Fringe search for scenario " << scenario_index;
    }
};

