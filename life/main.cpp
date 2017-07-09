#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <thread>


using namespace std;
const int SIZE = 30;

void displayWorld(const bool world[][SIZE]) {
    cout << "\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (world[i][j])
                cout << "X ";
            else
                cout <<". ";
        }
        cout << "\n";
    }
}

vector<pair<int, int>> getRandomLiveCells(const int world_size) {
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, world_size-1);
    uniform_int_distribution<int> uni_amount(world_size, world_size*3);
    auto num_of_cells = uni_amount(rng);

    vector<pair<int, int>> cells(0);
    for (int i = 0; i < num_of_cells; i++) {
        int x = uni(rng);
        int y = uni(rng);
        cells.push_back(make_pair(x, y));
    }
    return cells;
}

void initCells(bool world[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            world[i][j] = false;
        }
    }
}

void setLiveCells(bool world[][SIZE], vector<pair<int, int>> cells) {
    for (int i = 0; i < cells.size(); i++) {
        world[cells[i].first][cells[i].second] = true;
    }
}

int neighborsCount(const bool world[][SIZE], int x, int y) {
    int count = 0;
    if (x > 0) {
        if (y > 0 && world[x-1][y-1])
            count++;
        if (y < SIZE-1 && world[x-1][y+1])
            count++;
        if (world[x-1][y])
            count++;
    }
    if (x < SIZE-1) {
        if (y > 0 && world[x+1][y-1])
            count++;
        if (y < SIZE-1 && world[x+1][y+1])
            count++;
        if (world[x+1][y])
            count++;
    }
    if (y > 0 && world[x][y-1])
        count++;
    if (y < SIZE-1 && world[x][y+1])
        count++;

    return count;
}

bool nextGeneration(bool world[][SIZE], bool temp_world[][SIZE]) {
    int neighbors = 0;
    bool any = false;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            neighbors = neighborsCount(world, i, j);
            if (neighbors == 2) {
                temp_world[i][j] = world[i][j];
                //temp_world[i][j] = true;
                if (temp_world[i][j]){
                    any = true;
                }
            } else if (neighbors == 3) {
                temp_world[i][j] = true;
                any = true;
            } else {
                temp_world[i][j] = false;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            world[i][j] = temp_world[i][j];
        }
    }
    return any;
}


void displayLiveCells(vector<pair<int, int>> live_cells) {
    cout<<"-------------------------------" <<"\n";
    for (int i = 0; i < live_cells.size(); i++) {
        cout<<live_cells[i].first<<" "<<live_cells[i].second<<"\n";
    }
    cout<<"-------------------------------" <<"\n";
}

void setGlider(bool world[][SIZE]) {
    vector<pair<int, int>> coordinates = {{1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2}};
    for (int i = 0; i < coordinates.size(); i++) {
        int x = coordinates[i].first;
        int y = coordinates[i].second;
        world[x][y] = true;
    }
}

int main() {
    bool World[SIZE][SIZE];
    cout<< "Size of the world is " << SIZE << " by "<< SIZE << "\n";
    vector<pair<int, int>> live_cells = getRandomLiveCells(SIZE);
    cout<<"Amount of live cells is " << live_cells.size() << "\n";
    //displayLiveCells(live_cells);

    initCells(World);
    //setLiveCells(World, live_cells);
    setGlider(World);
    displayWorld(World);

    bool TempWorld[SIZE][SIZE];
    bool is_any_alive = true;
    int cnt = 1;
    while (is_any_alive) {
        cout << "\033[2J\033[1;1H";
        is_any_alive = nextGeneration(World, TempWorld);
        cout<<"Generation " << cnt;
        displayWorld(World);
        this_thread::sleep_for(std::chrono::milliseconds(500));
        cnt++;
    }
    return 0;
}
