#pragma once
#include "bucket_tab.h"
#include "scenario_controls.h"
#include "scenario_service.h"
#include <QTabWidget>
#include <qtmetamacros.h>



class TabWindow : public QTabWidget {
    Q_OBJECT;

public:
    TabWindow(ScenarioService& scenario_service);
private:
    ScenarioControls *scenario_controls_tab;
    BucketTab *bucket_tab;
};
