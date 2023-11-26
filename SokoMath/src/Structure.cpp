#include "Structure.h"

Structure::Structure()
{
}

Structure::Structure(vector<vector<cell>> g,Structure *p)
{
    vector<vector<cell>> newGrid;
    for(auto i:g)
    {
        vector<cell> temp;
        for(auto j:i)
        {
            cell newCell(j.isAns,j.isNumber,j.isOperation,j.val,j.op,j.view,j.isStatic);
            temp.push_back(newCell);
        }
        newGrid.push_back(temp);
    }
    this->grid=newGrid;

    parent=p;
    depth=0;
    cost=0;
}
void Structure::initState(vector<vector<cell>> g,Structure *p)
{
    vector<vector<cell>> newGrid;
    for(auto i:g)
    {
        vector<cell> temp;
        for(auto j:i)
        {
            cell newCell(j.isAns,j.isNumber,j.isOperation,j.val,j.op,j.view,j.isStatic);
            temp.push_back(newCell);
        }
        newGrid.push_back(temp);
    }
    this->grid=newGrid;
    parent=p;
    depth=0;
    cost=0;
}

void Structure::printGrid()
{
    for(auto i:grid)
    {
        for(auto j:i)
        {
            if(j.isNumber)
                cout << j.val;
            else if(j.isOperation)
                cout << j.op;
            else
                cout << j.view;
            cout << " ";
        }
        cout << endl;
    }
    cout << "\n\n\n";
}

void Structure::printStateInfo()
{
    cout << "Current State Depth: " << depth << endl;
    cout << "Current State Cost: " << cost << endl;
    string p=GetParentInfo();
    cout << "Parent Grid: " << p << endl;
    if(p!="The Current State Does Not Have Parent State")
        parent->printGrid();
    cout << "Current Grid" << endl;
    printGrid();
}


vector<action> Structure::getPossibleActions()
{
    vector<action> actions;
    vector<pair<int,action>> order;
    for(int i=0;i<(int)grid.size();i++)
    {
        for(int j=0;j<(int)grid[i].size();j++)
        {
            if((grid[i][j].isNumber||grid[i][j].isOperation)&&!grid[i][j].isStatic)
            {
                for(int d=0;d<4;d++)
                {
                    int newX=i+dirX[d];
                    int newY=j+dirY[d];
                    if(isValidPos(newX,newY))
                    {
                        action a={i,j,d};
                        if(grid[i][j].isNumber)
                            order.push_back({grid[i][j].val,a});
                        else if(grid[i][j].isOperation)
                            order.push_back({(int)grid[i][j].op,a});
                    }
                }
            }
        }
    }
    sort(order.begin(),order.end(),[](pair<int,action> &a,pair<int,action> &b){
        return a.first<b.first;
    });
    for(auto i:order)
        actions.push_back(i.second);
    return actions;
}

bool Structure::isValidPos(int x,int y)
{
    return (x>=0&&y>=0&&x<(int)grid.size()&&y<(int)grid[0].size()&&grid[x][y].view!='#'&&!grid[x][y].isNumber&&!grid[x][y].isOperation);
}

string Structure::GetParentInfo()
{
    if(parent==NULL)
       return "The Current State Does Not Have Parent State";
    else
       return "There is a Parent State";
}


Structure Structure::applyMove(action Move,Structure *p=NULL)
{
    Structure newStructure=this->DeepCopy();
    int x=Move.row;
    int y=Move.col;
    int dir=Move.dir;

    while(true)
    {
        int newX=dirX[dir]+x;
        int newY=dirY[dir]+y;
        if(isValidPos(newX,newY))
        {
            x=newX;
            y=newY;
        }
        else
            break;
    }
    swapCells(Move.row,Move.col,x,y,newStructure.grid);
    newStructure.depth=depth+1;
    newStructure.cost=cost+1;
    newStructure.setParent(p);
    return newStructure;
}

void Structure::swapCells(int x1,int y1,int x2,int y2,vector<vector<cell>> &g)
{
    swap(g[x1][y1].isNumber,g[x2][y2].isNumber);
    swap(g[x1][y1].isOperation,g[x2][y2].isOperation);
    swap(g[x1][y1].val,g[x2][y2].val);
    swap(g[x1][y1].op,g[x2][y2].op);
    return;
}


vector<Structure> Structure::nextStates()
{
    vector<action> actions=this->getPossibleActions();
    vector<Structure> states;
    for(auto a:actions)
    {
        Structure temp=applyMove(a,this);
        states.push_back(temp);
    }
    return states;
}

bool Structure::isEqual(Structure a,Structure b)
{
    bool equalGrid=true;
    for(int i=0;i<(int)a.grid.size();i++)
    {
        for(int j=0;j<(int)a.grid[0].size();j++)
        {
            equalGrid&=(a.grid[i][j].isAns==b.grid[i][j].isAns);
            equalGrid&=(a.grid[i][j].isNumber==b.grid[i][j].isNumber);
            equalGrid&=(a.grid[i][j].isOperation==b.grid[i][j].isOperation);
            equalGrid&=(a.grid[i][j].val==b.grid[i][j].val);
            equalGrid&=(a.grid[i][j].op==b.grid[i][j].op);
            equalGrid&=(a.grid[i][j].view==b.grid[i][j].view);
            equalGrid&=(a.grid[i][j].isStatic==b.grid[i][j].isStatic);
        }
    }
    return (equalGrid);
}
Structure Structure::DeepCopy()
{
    Structure newCopy;
    vector<vector<cell>> newGrid;
    for(auto i:this->grid)
    {
        vector<cell> temp;
        for(auto j:i)
        {
            cell newCell(j.isAns,j.isNumber,j.isOperation,j.val,j.op,j.view,j.isStatic);
            temp.push_back(newCell);
        }
        newGrid.push_back(temp);
    }
    newCopy.grid=newGrid;
    newCopy.parent=this->parent;
    newCopy.depth=this->depth;
    newCopy.cost=this->cost;
    return newCopy;
}

bool Structure::isFinal()
{
    bool ok=true;
    vector<pair<int,int>> equalSign;
    bool isComparison=false;
    int equalSigns=0;
    pair<int,int> FirstAnsBlock={-1,-1};
    for(int i=0;i<(int)grid.size();i++)
    {
        for(int j=0;j<(int)grid[0].size();j++)
        {
            if(grid[i][j].isOperation&&grid[i][j].op=='>')
                isComparison=true;
            if(grid[i][j].isOperation&&grid[i][j].op=='=')
                equalSigns++;
            if(grid[i][j].view=='$'&&FirstAnsBlock.first==-1)
                FirstAnsBlock={i,j};
            if(grid[i][j].view=='$'&&grid[i][j].isOperation&&grid[i][j].op=='=')
                equalSign.push_back({i,j});
        }
    }
    if(equalSign.empty())
    {
        if(!isComparison)
            return false;
        // solve for > operator
        int x=FirstAnsBlock.first;
        int y=FirstAnsBlock.second;
        int currentNumber=grid[x][y].val;
        if(!grid[x][y].isNumber)
            return false;
        int Xor=1;
        while(true)
        {
            int newX=x;
            int newY=y+1;
            if(newX>=0&&newY>=0&&newX<(int)grid.size()&&newY<(int)grid[0].size()&&grid[newX][newY].view=='$')
            {
                if(grid[newX][newY].isNumber&&Xor==0)
                {
                    ok&=(currentNumber>grid[newX][newY].val);
                    currentNumber=grid[newX][newY].val;
                    x=newX;
                    y=newY;
                    Xor^=1;
                }
                else if(grid[newX][newY].isOperation&&Xor==1)
                {
                    x=newX;
                    y=newY;
                    Xor^=1;
                }
                else
                {
                    ok=false;
                    break;
                }
            }
            else
                break;
        }
        return ok;
    }
    if((int)equalSign.size()!=equalSigns)
        return false;
    // solve for = && + -
    for(auto i:equalSign)
    {
        int X=i.first;
        int Y=i.second;
        int cnt=0;
        vector<vector<int>> validDir={{0,1},{2,3}};
        for(auto v:validDir)
        {
            map<int,int> freq;
            bool isValidDir=true;
            for(auto d:v)
            {
                int newX=X+dirX[d];
                int newY=Y+dirY[d];
                isValidDir&=(newX>=0&&newY>=0&&newX<(int)grid.size()&&newY<(int)grid[0].size()&&grid[newX][newY].view=='$');
            }
            cnt+=isValidDir;
            if(!isValidDir)
                continue;
            for(auto d:v)
            {
                int num=0;
                char c='.';
                int x=X;
                int y=Y;
                while(true)
                {
                    if(!ok)
                        break;
                    int newX=dirX[d]+x;
                    int newY=dirY[d]+y;
                    if(newX>=0&&newY>=0&&newX<(int)grid.size()&&newY<(int)grid[0].size()&&grid[newX][newY].view=='$')
                    {
                        if(grid[newX][newY].isNumber)
                        {
                            if(c!='.')
                            {
                                if(c=='+')
                                    num+=grid[newX][newY].val;
                                else
                                    num-=grid[newX][newY].val;
                                c='.';
                            }
                            else
                            {
                                if(num==0)
                                {
                                    num=grid[newX][newY].val;
                                }
                                else
                                {
                                    ok=false;
                                    break;
                                }
                            }
                            x=newX;
                            y=newY;
                        }
                        else if(grid[newX][newY].isOperation)
                        {

                            if(c=='.'&&grid[newX][newY].op!='=')
                            {
                                c=grid[newX][newY].op;
                            }
                            else
                            {
                                ok=false;
                                break;
                            }
                            x=newX;
                            y=newY;
                        }
                        else
                        {
                            if(num==0)
                            {
                                ok=false;
                            }
                            else
                            {
                                freq[abs(num)]++;
                            }
                            break;
                        }
                    }
                    else
                    {
                        if(num==0)
                        {
                            ok=false;
                        }
                        else
                        {
                            freq[abs(num)]++;
                        }
                        break;
                    }
                }
            }
            ok&=(freq.size()==1&&freq.begin()->second>=2);
        }
        ok&=(cnt>=1);
    }
    return ok;
}


void Structure::printNextStates()
{
    vector<Structure> nodes=this->nextStates();
    for(auto state:nodes)
        state.printStateInfo();
    return;
}

vector<action> Structure::printPossibleActions()
{
    vector<action> actions=getPossibleActions();
    for(int i=0;i<(int)(actions.size());i++)
    {
        int row=actions[i].row;
        int col=actions[i].col;
        int d=actions[i].dir;
        cout << i << " - The cell in row: " << row << " and col: " << col << " Can Move " << DIR[d] << endl;
    }
    return actions;
}

void Structure::setParent(Structure *a)
{
    this->parent=a;
}
Structure::~Structure()
{
    //dtor
}
