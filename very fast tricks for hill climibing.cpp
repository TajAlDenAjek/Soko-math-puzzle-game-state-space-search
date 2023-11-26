#include "Logic.h"
#include "Structure.h"
#include "windows.h"

// ( not tested a lot)


Logic::Logic()
{

}
Logic::Logic(Structure s)
{
    root=s.DeepCopy();
}
void Logic::LoadRootNode(Structure s)
{
    root=s.DeepCopy();
}


int Logic::heuristic(Structure s,map<vector<vector<cell>>,int,customGridKeyforMap> &cost)
{
    if(s.isFinal())
        return 0;
    if(cost.count(s.grid))
    {
        return s.depth*10;
    }
    int estimatedValue=0;
    vector<vector<int>> validDir={{0,1},{2,3}};
    for(int i=0;i<(int)s.grid.size();i++)
    {
        for(int j=0;j<(int)s.grid[i].size();j++)
        {
            if(s.grid[i][j].isAns)
                estimatedValue+=20;
            if(s.grid[i][j].isStatic)
            {
                estimatedValue-=20;
                continue;
            }
//            if(s.grid[i][j].isAns&&(s.grid[i][j].isNumber||s.grid[i][j].isOperation))
//            {
//                if(s.grid[i][j].isNumber)
//                    estimatedValue-=5;
//                else
//                    estimatedValue-=10;
//            }
//            for(int d=0;d<4;d++)
//            {
//                int newX=i+s.dirX[d];
//                int newY=j+s.dirY[d];
//                if(s.isValidPos(newX,newY))
//                    estimatedValue+=(d+1);
//            }
//            if(s.grid[i][j].isAns&&s.grid[i][j].isOperation)
//            {
//                for(auto d:validDir)
//                {
//                    bool ok=true;
//                    for(auto dir:d)
//                    {
//                        int newX=i+s.dirX[dir];
//                        int newY=j+s.dirY[dir];
//                        ok&=(newX>=0&&newY>=0&&newX<(int)s.grid.size()&&newY<(int)s.grid[0].size()&&s.grid[newX][newY].view=='$');
//                    }
////                    if(ok)
////                    {
////                        cout << "Yea" << endl;
////                        exit(0);
////                    }
//                    estimatedValue-=(ok?1:-1);
//                }
//            }
        }
    }
    return estimatedValue;
}
Logic::~Logic()
{
    //dtor
}
