#pragma once
#include "search_thread.h"
#include "search_service.h"
#include "models.h"
#include "tools.h"

#include <vector>
#include <string>

// #include QObject

class AstarThread : public SearchThread {

// Q_OBJECT

public:
    AstarThread(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap, SearchService* search_service);
    void run() override;
    void astar_with_signals(
        int startx, 
        int starty, 
        int goalx, 
        int goaly, 
        const std::vector<std::string>& citymap
    );


    void astar_search_thread(int startx, int starty, int goalx, int goaly, const std::vector<std::string> &citymap);

};


