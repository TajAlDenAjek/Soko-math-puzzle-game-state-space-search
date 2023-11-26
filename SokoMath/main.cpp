#include<bits/stdc++.h>
#include<Structure.h>
#include<Logic.h>
#include<chrono>
#include "windows.h"

using namespace std;

// levels
vector<vector<cell>> levelOne({ { { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' } }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,true,0,'=','.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { true,true,false,1,0,'$' }, { true,false,false,0,0,'$' }, { true,true,false,1,0,'$' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } } });
vector<vector<cell>> levelTwo({ { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,true,false,4,0,'.' }, { true,false,false,0,0,'$' }, { true,false,false,0,0,'$' }, { true,false,false,0,0,'$' }, { false,true,false,4,0,'.' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,true,0,'=','.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, }, { { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' } } });
vector<vector<cell>> levelThree({ { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { true,false,false,0,0,'$' }, { true,false,false,0,0,'$' }, { true,true,false,1,0,'$',true }, { true,false,false,0,0,'$' }, { true,false,false,0,0,'$' }, { false,true,false,3,0,'.' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,true,false,2,0,'.' }, { false,false,true,0,'+','.' }, { false,false,false,0,0,'#' }, { false,false,true,0,'=','.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' } } });
vector<vector<cell>> levelFour({ { { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' } }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { true,true,false,1,0,'$' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { true,true,false,2,0,'$' }, { true,true,false,2,0,'$' }, { true,true,false,1,0,'$' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { true,false,true,0,'=','$' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, }, });
vector<vector<cell>> levelFive({ { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, }, { { false,false,false,0,0,'#' }, { true,false,true,0,'+','$' }, { true,false,false,0,0,'$' }, { true,false,false,0,0,'$' }, { true,false,false,0,0,'$' }, { true,false,true,0,'=','$' }, { false,true,false,2,0,'.' }, { false,true,false,1,0,'.' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,true,false,3,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, }, });
vector<vector<cell>> levelSix({ { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' } }, { { false,false,false,0,0,'#' }, { false,false,true,0,'=','.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,true,false,3,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,true,false,3,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { true,false,false,0,0,'$' }, { true,false,false,0,0,'$' }, { true,false,false,0,0,'$' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } } });
vector<vector<cell>> levelSeven({ { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, }, { { false,false,false,0,0,'#' }, { true,true,false,2,0,'$' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { true,false,false,0,0,'$' }, { true,false,false,0,0,'$' }, { true,true,false,2,0,'$',true }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { true,true,false,1,0,'$' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,true,0,'=','.' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { true,false,true,0,'=','$' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { false,true,false,1,0,'.' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } } });
vector<vector<cell>> levelEight({ { { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { true,false,true,0,'-','$' }, { true,true,false,1,0,'$' }, { true,false,false,0,0,'$' }, { true,false,false,0,0,'$' }, { true,true,false,3,0,'$',true }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,true,false,4,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,true,0,'=','.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' } }, { { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' } } });
vector<vector<cell>> levelNine({ { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, }, { { false,false,false,0,0,'#' }, { true,true,false,8,0,'$',true }, { true,true,false,3,0,'$' }, { true,false,true,0,'+','$' }, { true,false,true,0,'=','$' }, { true,true,false,5,0,'$' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,true,0,'=','.' }, { true,false,false,0,0,'$' }, { true,true,false,3,0,'$' }, { true,true,false,3,0,'$',true }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, } });
vector<vector<cell>> levelTen({ { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,true,false,1,0,'.' }, { false,false,true,0,'>','.' }, { true,true,false,2,0,'$' }, { true,false,true,0,'>','$' }, { true,true,false,3,0,'$' }, { true,false,false,0,0,'$' }, { true,false,false,0,0,'$' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' } }, { { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'#' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' }, { false,false,false,0,0,'.' } } });

vector<vector<vector<cell>>> levels={
    levelOne,
    levelTwo,
    levelThree,
    levelFour,
    levelFive,
    levelSix,
    levelSeven,
    levelEight,
    levelNine,
    levelTen
};


int main()
{
    while(true)
    {
        system("cls");
        cout << "Welcome to sokomath game (state space search), developed by Taj Al Den " << endl;
        cout << "Enter 0 to exit" << endl;
        cout << "Enter 1 to start playing as user" << endl;
        cout << "Enter 2 to start Bfs on all levels " << endl;
        cout << "Enter 3 to start Dfs on all levels " << endl;
        cout << "Enter 4 to start Dijkstra (UCS) all levels " << endl;
        cout << "Enter 5 to start A Star search on all levels " << endl;
        system("pause>nul");
        int choice; cin >> choice;
        if(choice<0||choice>=6)
            continue;
        if(choice==0)
        {
            break;
        }
        else if(choice==1)
        {
            Structure s;
            Logic L;
            for(int i=0;i<10;i++)
            {
                s.initState(levels[i],NULL);
                L.LoadRootNode(s);
                L.UserPlay();
                cout << "Level " << i+1 << " Completed" << endl;
                system("pause>nul");
            }
        }
        else if(choice==2)
        {
            for(int i=0;i<10;i++)
            {
                cout << "Breadth First Search on level " << i+1 << endl;
                cout << endl << "***************************************" << endl;
                auto start = chrono::high_resolution_clock::now();
                Structure S(levels[i],NULL);
                Logic L(S);
                L.bfs();
                auto end = chrono::high_resolution_clock::now();
                double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                time_taken *= 1e-9;
                cout << "Time taken by level " << i+1 << " is : " << fixed<< time_taken << setprecision(9) << "sec" << endl;
                cout << endl << "***************************************" << endl;
                system("pause>nul");
            }
        }
        else if(choice==3)
        {
            for(int i=0;i<10;i++)
            {
                cout << "Depth First Search on level : " << i+1 << endl;
                cout << endl << "***************************************" << endl;
                auto start = chrono::high_resolution_clock::now();
                Structure S(levels[i],NULL);
                Logic L(S);
                L.dfs();
                auto end = chrono::high_resolution_clock::now();
                double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                time_taken *= 1e-9;
                cout << "Time taken by level " << i+1 << " is : " << fixed<< time_taken << setprecision(9) << "sec" << endl;
                cout << endl << "***************************************" << endl;
                system("pause>nul");
            }
        }
        else if(choice==4)
        {
            for(int i=0;i<10;i++)
            {
                cout << "Dijkstra (UCS) on level : " << i+1 << endl;
                cout << endl << "***************************************" << endl;
                auto start = chrono::high_resolution_clock::now();
                Structure S(levels[i],NULL);
                Logic L(S);
                L.dijkstra();
                auto end = chrono::high_resolution_clock::now();
                double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                time_taken *= 1e-9;
                cout << "Time taken by level " << i+1 << " is : " << fixed<< time_taken << setprecision(9) << "sec" << endl;
                cout << endl << "***************************************" << endl;
                system("pause>nul");
            }
        }
        else if(choice==5)
        {
            for(int i=0;i<10;i++)
            {
                cout << "A Star search on level : " << i+1 << endl;
                cout << endl << "***************************************" << endl;
                auto start = chrono::high_resolution_clock::now();
                Structure S(levels[i],NULL);
                Logic L(S);
                L.A_StarSearch(i+1);
                auto end = chrono::high_resolution_clock::now();
                double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                time_taken *= 1e-9;
                cout << "Time taken by level " << i+1 << " is : " << fixed<< time_taken << setprecision(9) << "sec" << endl;
                cout << endl << "***************************************" << endl;
                system("pause>nul");
            }
        }
    }
    return 0;
}

