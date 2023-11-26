#ifndef STRUCTURE_H
#define STRUCTURE_H
#include<bits/stdc++.h>
using namespace std;

struct action
{
    int row,col,dir;
};
struct cell
{
    bool isAns;
    bool isNumber;
    bool isOperation;
    bool isStatic;
    int val;
    char op,view;
    cell():isAns(false),isNumber(false),isOperation(false),val(0),op('+'),view('.'){}
    cell(bool a=false,bool n=false,bool ob=false,int v=0,char op='+',char view='.',bool c=false)
    {
        isAns=a;
        isNumber=n;
        isOperation=ob;
        val=v;
        this->op=op;
        this->view=view;
        isStatic=c;
    }
};


class Structure
{

    public:
    vector<vector<cell>> grid;
    Structure *parent=NULL;
    int depth=0;
    int cost=0;

    int dirX[4]={0,0,-1,1};
    int dirY[4]={1,-1,0,0};
    string DIR[4]={"RIGHT","LEFT","UP","DOWN"};
    public:
        Structure();
        Structure(vector<vector<cell>> g,Structure *p);
        void initState(vector<vector<cell>> g,Structure *p);
        vector<action> printPossibleActions();
        void printGrid();

        void printStateInfo();

        Structure applyMove(action Move,Structure *p);

        vector<Structure> nextStates();

        void printNextStates();

        vector<action> getPossibleActions();

        string GetParentInfo();

        bool isValidPos(int x,int y);

        bool isEqual(Structure a,Structure b);

        void swapCells(int x1,int y1,int x2,int y2,vector<vector<cell>> &grid);

        Structure DeepCopy();

        bool isFinal();

        void setParent(Structure *a);
        virtual ~Structure();

        bool operator<(const Structure &a) const
        {
            return this->cost>a.cost;
        }
    protected:
    private:
};


struct compForHeuristic
{
    bool operator()(pair<pair<int,int>,Structure> a,pair<pair<int,int>,Structure> b)
    {
        // f==f (f=g+h)
        if(a.first.first==b.first.first)
            // return minimum f
            return a.first.second>b.first.second;
        // return minimum h
        return a.first.first>b.first.first;
    }
};

struct customGridKeyforMap
{
    bool operator()(const vector<vector<cell>> &v1, const vector<vector<cell>> &v2) const
    {
        if((int)v1.size()!=(int)v2.size())
        {
            return (int)v1.size()<(int)v2.size();
        }
        for(int i=0;i<(int)v1.size();i++)
        {
            if((int)v1[i].size()!=(int)v2[i].size())
            {
                return (int)v1[i].size()<(int)v2[i].size();
            }
            for(int j=0;j<(int)v1[i].size();j++)
            {
                const cell &cell1=v1[i][j];
                const cell &cell2=v2[i][j];

                if(cell1.isAns!=cell2.isAns)
                {
                    return cell1.isAns<cell2.isAns;
                }

                if(cell1.isNumber!=cell2.isNumber)
                {
                    return cell1.isNumber<cell2.isNumber;
                }
                if(cell1.isOperation!=cell2.isOperation)
                {
                    return cell1.isOperation<cell2.isOperation;
                }
                if(cell1.isStatic!=cell2.isStatic)
                {
                    return cell1.isStatic<cell2.isStatic;
                }

                if(cell1.val!=cell2.val)
                {
                    return cell1.val<cell2.val;
                }

                if(cell1.op!=cell2.op)
                {
                    return cell1.op<cell2.op;
                }
                if(cell1.view!=cell2.view)
                {
                    return cell1.view<cell2.view;
                }
            }
        }
        return false;
    }
};

#endif // STRUCTURE_H
