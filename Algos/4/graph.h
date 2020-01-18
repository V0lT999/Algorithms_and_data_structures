#ifndef INC_4_GRAPH_H
#define INC_4_GRAPH_H
#include <iostream>
#include <time.h>
#include <fstream>
#endif //INC_4_GRAPH_H

using namespace std;

class Graph
{
    static int maxN;
    static int maxS;
    int N;
    int **gr;
public:
    bool generator();
    void show();
    int way();
    Graph(): gr(nullptr) {};
    ~Graph(){
        for(int i = 0; i < N; i++){
            delete(gr[i]);
        }
        delete(gr);
    }
};

int Graph:: maxN = 20;
int Graph:: maxS = 50;


bool Graph:: generator(){
    cout << "1: Generate from filee\n2: Random generation\nYour choose is: ";
    int choose;
    cin >> choose;
    switch(choose){
        case 1: {
            ifstream input;
            input.open("generator.txt", ios::in);
            if(input) {
                input >> N;
                gr = new int *[N];
                for (int i = 0; i < N; i++) {
                    gr[i] = new int[N];
                    for (int i1 = 0; i1 < N; i1++) {
                        input >> gr[i][i1];
                    }
                }
                input.close();
            } else {
                cout << "wrong file" << endl;
                return false;
            }
            break;
        }
        case 2:{
            srand(time(nullptr));
            N = rand() % maxN;
            while(N < 10){
                N = rand() % maxN;
            }
            gr = new int * [N];
            for(int i = 0; i < N; i++){
                gr[i] = new int [N];
            }
            for(int i = 0; i < N; i++){
                for(int i1 = 0; i1 <= i; i1++){
                    int a = rand() % 100;
                    if(i == i1) gr[i][i1] = maxS; else
                    if(a >= 30) {
                        gr[i][i1] = rand() % maxS;
                    } else gr[i][i1] = maxS;
                }
            }
            for(int i = 0; i < N - 1; i++){
                for(int i1 = i + 1; i1 < N; i1++){
                    gr[i][i1] = gr[i1][i];
                }
            }
            break;
        }
        default: {
            cout << "wrong input" << endl;
            return false;
        }
    }
    return true;
}

void Graph::show(){
    cout << "   ";
    for(int i = 0; i < N; i++) cout << i << "  ";
    cout << endl;
    cout << "---";
    for (int i = 0; i < N; i++) if(i < 10) cout << "---"; else cout << "----";
    cout << endl;
    for(int i = 0; i < N; i++){
        if (i / 10 == 0) cout << i << " |"; else cout << i << "|";
        for(int i1 = 0; i1 < N; i1++){
            if (gr[i][i1] / 10 == 0) cout << gr[i][i1] << "  ";
            else cout << gr[i][i1] << " ";
            if(i1 / 10 != 0) cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int Graph::way(){
    int first, second;
    cout << "Input first and second point: ";
    cin >> first >> second;
    cout << "Looking for the shortest path from vertex " << first << " to vertex " << second << endl;
    int point[N];
    bool pass[N];
    for(int i = 0; i < N; i++){
        point[i] = maxS;
        pass[i] = false;
    }
    int k = 0;
    int tp;
    int p[N];
    tp = first;
    point[first] = 0;
    p[first] = first;
    while (k < N){
        int min = maxS;
        for(int i = 0; i < N; i++){
            if(!pass[i] && point[i] <= min){
                min = point[i];
                tp = i;
            }
        }
        for(int i = 0; i < N; i++){
            if(point[i] > point[tp] + gr[tp][i]){
                point[i] = point[tp] + gr[tp][i];
                p[i] = tp;
            }
        }
        pass[tp] = true;
        k++;
    }

    cout << "minimal way is: " << point[second] << endl;
    cout << "way is: ";
    k = second;
    cout << second << " ";
    while(k != first){
        cout << p[k] << " ";
        k = p[k];
    }
    cout << endl;

    return N;
}