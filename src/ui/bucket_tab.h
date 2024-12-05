#include "scenario_service.h"
#include <QWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QComboBox>
#include <QTableWidget>

class BucketTab : public QWidget {
    Q_OBJECT

public:
    BucketTab(const ScenarioService& scenario_service);
private slots:


private:
    const ScenarioService& scenario_service;
    QGroupBox *scenario_box;
    void create_scenario_box();
    QComboBox *bucket_box;
    QTableWidget *result_table;
    QTableWidget* get_result_table();

};
