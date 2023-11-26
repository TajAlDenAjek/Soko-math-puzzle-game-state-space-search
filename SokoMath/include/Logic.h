#ifndef LOGIC_H
#define LOGIC_H

#include<bits/stdc++.h>
#include"Structure.h"
class Logic
{
    public:
    Structure root;
    public:
        Logic();
        Logic(Structure s);
        void LoadRootNode(Structure s);
        void UserPlay();
        void bfs();
        void dfs();
        void dijkstra();
        void A_StarSearch(int level);
        int heuristic(Structure s,map<vector<vector<cell>>,int,customGridKeyforMap> &cost,int level);
        virtual ~Logic();
    protected:

    private:
};

#endif // LOGIC_H
