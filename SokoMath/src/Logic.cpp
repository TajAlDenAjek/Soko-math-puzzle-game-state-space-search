#include "Logic.h"
#include "Structure.h"
#include "windows.h"

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

void Logic::UserPlay()
{
    Structure root=this->root;
    vector<Structure> path;
    Structure next;
    while(true)
    {
        system("cls");
        root.printStateInfo();
        if(root.isFinal())
        {
            cout << "Good Game , Well Done" << endl;
            break;
        }
        vector<action> Actions=root.printPossibleActions();
        system("pause>nul");
        int choice=0;
        cin >> choice;
        if(choice>=0&&choice<(int)Actions.size())
        {
            next=root;
            root=next.applyMove(Actions[choice],&next);
            system("pause>nul");
        }
    }
}

void Logic::bfs()
{
    map<vector<vector<cell>>,bool,customGridKeyforMap> visited;
    int visitedNodes=0,depth=0,maxDepth=0;
    vector<Structure> path;
    queue<Structure> q;
    Structure root=this->root;
    q.push(root);
    visited[root.grid]=true;
    while(!q.empty())
    {
        Structure cur=q.front().DeepCopy();
        q.pop();
        maxDepth=max(maxDepth,cur.depth);
        visitedNodes++;
        if(cur.isFinal())
        {
            depth=cur.depth;
//            while(cur.parent!=NULL)
//            {
//                path.push_back(cur);
//                cur=*cur.parent;
//            }
//            path.push_back(cur);
//            reverse(path.begin(),path.end());
            break;
        }
        vector<action> Actions=cur.getPossibleActions();
        for(auto a:Actions)
        {
            Structure next=cur.applyMove(a,NULL);
            next.setParent(new Structure(cur));
            if(!visited[next.grid])
            {
                visited[next.grid]=true;
                q.push(next);
            }
        }
    }
    cout << "Visited Nodes : " << visitedNodes << " Solution Depth : " << depth << " Max Depth : " << maxDepth << endl;
//    cout << "Solution path with : " << path.size() << " Nodes" << endl;
//    for(auto i:path)
//        i.printGrid();
}
void Logic::dfs()
{
    map<vector<vector<cell>>,bool,customGridKeyforMap> visited;
    int visitedNodes=0,depth=0,maxDepth=0;
    vector<Structure> path;
    stack<Structure> s;
    Structure root=this->root;
    s.push(root);
    visited[root.grid]=true;
    while(!s.empty())
    {
        Structure cur=s.top().DeepCopy();
        s.pop();
        maxDepth=max(maxDepth,cur.depth);
        visitedNodes++;
        if(cur.isFinal())
        {
            depth=cur.depth;
//            while(cur.parent!=NULL)
//            {
//                path.push_back(cur);
//                cur=*cur.parent;
//            }
//            path.push_back(cur);
//            reverse(path.begin(),path.end());
            break;
        }
        vector<action> Actions=cur.getPossibleActions();
        for(auto a:Actions)
        {
            Structure next=cur.applyMove(a,NULL);
            next.setParent(new Structure(cur));
            if(!visited[next.grid])
            {
                visited[next.grid]=true;
                s.push(next);
            }
        }
    }
    cout << "Visited Nodes : " << visitedNodes << " Solution Depth : " << depth << " Max Depth : " << maxDepth << endl;
//    cout << "Solution path with : " << path.size() << " Nodes" << endl;
//    for(auto i:path)
//        i.printGrid();
}


void Logic::dijkstra()
{
    map<vector<vector<cell>>,int,customGridKeyforMap> cost;
    int visitedNodes=0,depth=1e9,maxDepth=0;
    vector<Structure> path;
    priority_queue<Structure> pq;
    Structure root=this->root;
    pq.push(root);
    cost[root.grid]=0;
    while(!pq.empty())
    {
        Structure temp=pq.top();
        Structure cur=temp.DeepCopy();
        pq.pop();
        maxDepth=max(maxDepth,cur.depth);
        visitedNodes++;
        if(cur.isFinal())
        {
            if(depth>cur.depth)
            {
                depth=cur.depth;
                root=cur;
            }
        }
        if(cost[cur.grid]<cur.cost)
            continue;
        vector<action> Actions=cur.getPossibleActions();
        for(auto a:Actions)
        {
            Structure next=cur.applyMove(a,new Structure(cur));
            if(!cost.count(next.grid))
                cost[next.grid]=1e9;
            if(cost[cur.grid]+1<cost[next.grid])
            {
                cost[next.grid]=cost[cur.grid]+1;
                pq.push(next);
            }
        }
    }
    cout << "Visited Nodes : " << visitedNodes << " Solution Depth : " << depth << " Max Depth : " << maxDepth << endl;
//    while(root.parent!=NULL)
//    {
//        path.push_back(root);
//        root=*root.parent;
//    }
//    path.push_back(root);
//    reverse(path.begin(),path.end());
//    cout << "Solution path with : " << path.size() << " Nodes" << endl;
//    for(auto i:path)
//        i.printGrid();
}

void Logic::A_StarSearch(int level)
{
    int visitedNodes=0,depth=1e9,maxDepth=0;

    Structure root=this->root;
    vector<Structure> path;

    map<vector<vector<cell>>,int,customGridKeyforMap> cost;
    priority_queue< pair<pair<int,int>,Structure>, vector<pair<pair<int,int>,Structure> >, compForHeuristic> pq;


    cost[root.grid]=0;
    pq.push({{0,0},root});
    while(!pq.empty())
    {
        Structure temp=pq.top().second;
        Structure cur=temp.DeepCopy();
        pq.pop();
        maxDepth=max(maxDepth,cur.depth);
        if(cur.isFinal())
        {
            if(depth>cur.depth)
            {
                depth=cur.depth;
                root=cur;
            }
            visitedNodes++;
            break;
        }
        if(cost[cur.grid]<cur.cost)
            continue;

        visitedNodes++;
        vector<action> Actions=cur.getPossibleActions();
        for(auto a:Actions)
        {
            Structure next=cur.applyMove(a,new Structure(cur));
            int h=heuristic(next,cost,level);
            int priority=h;
            if(!cost.count(next.grid))
                cost[next.grid]=1e9;
            if(cost[cur.grid]+1<cost[next.grid])
            {
                cost[next.grid]=cost[cur.grid]+1;
                //      f(n)=  g(n)  +  h(n)
                //      g(n): cost from start to the current , h(n):estimated cost from the current to the goal
                priority+=cost[next.grid];
                pq.push({{priority,h},next});
            }
        }
    }
    cout << "Visited Nodes : " << visitedNodes << " Solution Depth : " << depth << " Max Depth : " << maxDepth << endl;
//    while(root.parent!=NULL)
//    {
//        path.push_back(root);
//        root=*root.parent;
//    }
//    path.push_back(root);
//    reverse(path.begin(),path.end());
//    cout << "Solution path with : " << path.size() << " Nodes" << endl;
//    for(auto i:path)
//        i.printGrid();
}

int Logic::heuristic(Structure s,map<vector<vector<cell>>,int,customGridKeyforMap> &cost,int level)
{
    if(s.isFinal())
        return 0;
    int estimatedValue=0;
    vector<vector<int>> validDir={{0,1},{2,3}};
    for(int i=0;i<(int)s.grid.size();i++)
    {
        for(int j=0;j<(int)s.grid[i].size();j++)
        {
            // Misplaced
            if(s.grid[i][j].isAns&&!(s.grid[i][j].isNumber||s.grid[i][j].isOperation))
                estimatedValue++;
            // handle operation
            if(s.grid[i][j].isAns&&s.grid[i][j].isOperation)
            {
                int cnt=0;
                int operationAdjacent=0;
                for(auto d:validDir)
                {
                    bool ok=true;
                    for(auto dir:d)
                    {
                        int newX=i+s.dirX[dir];
                        int newY=j+s.dirY[dir];
                        operationAdjacent+=(newX>=0&&newY>=0&&newX<(int)s.grid.size()&&newY<(int)s.grid[0].size()&&s.grid[newX][newY].view=='$'&&s.grid[newX][newY].isOperation);
                        ok&=(newX>=0&&newY>=0&&newX<(int)s.grid.size()&&newY<(int)s.grid[0].size()&&s.grid[newX][newY].view=='$');
                    }
                    cnt+=ok;
                }
                if(cnt==0)
                {
                    // at least I need one moves
                    estimatedValue+=1;
                }
            }
            // heuristic by level
            if(level==8)
                continue;
            // handle number
            if(s.grid[i][j].isAns&&s.grid[i][j].isNumber)
            {
                int cnt=0;
                for(auto d:validDir)
                {
                    bool ok=false;
                    for(auto dir:d)
                    {
                        int newX=i+s.dirX[dir];
                        int newY=j+s.dirY[dir];
                        ok|=(newX>=0&&newY>=0&&newX<(int)s.grid.size()&&newY<(int)s.grid[0].size()&&s.grid[newX][newY].view=='$'&&s.grid[newX][newY].isOperation);
                    }
                    cnt+=ok;
                }
                if(cnt==0)
                {
                    estimatedValue++;
                }
            }
        }
    }
    return estimatedValue;
}
Logic::~Logic()
{
    //dtor
}
