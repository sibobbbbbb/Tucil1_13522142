#include "solver.cpp"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std::chrono;
using namespace std;

int main()
{
    string choice,save;
    Tucil tucil;
    cout << "Selamat Datang di Program Cyberpunk 2077 Breach Protocol dengan Algoritma Brute Force" << endl;
    cout << "Pilih Inputan: " << endl;
    cout << "1. CLI" << endl;
    cout << "2. File.txt" << endl;
    cout << "Pilihan: ";

    cin >> choice;
    while (choice != "1" && choice != "2")
    {
        cout << "Pilihan tidak valid\n"
             << endl;
        cout << "Pilih Inputan: " << endl;
        cout << "1. CLI" << endl;
        cout << "2. File.txt" << endl;
        cout << "Pilihan: ";
        cin >> choice;
    }
    cout << endl;

    if (choice == "1")
    {
        tucil = CLI();
    }
    else
    {
        tucil = read_file();
    }
    checkData(tucil);
    
    vector<string> route;
    vector<Point> routePoints;
    vector<vector<bool>> visited(tucil.row, vector<bool>(tucil.col, false)); 

    auto start = high_resolution_clock::now();

    for (int j = 0; j < tucil.col; ++j)
    {
        searchRoute(tucil, tucil.matriks, 0, j, route, routePoints, visited, tucil.buffer, true);
    }
    cout << maxReward << endl;
    if (maxReward != 0)
    {
        for (int i = 0; i < maxRoute.size(); ++i)
        {
            cout << maxRoute[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < maxRoutePoints.size(); ++i)
        {
            cout << maxRoutePoints[i].col +1 << "," << maxRoutePoints[i].row + 1 << endl;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << endl <<duration.count() << " ms" << endl;
    cout << "\nApakah ingin menyimpan solusi? (y/n)" << endl;
    cin >> save;

    while (save != "y" && save != "n")
    {
        cout << "Pilihan tidak valid\n"<< endl;
        cout << "Apakah ingin menyimpan solusi? (y/n)" << endl;
        cin >> save;
    }

    if (save == "y")
    {
        string filename;
        string path = "../test/";
        cout << "Masukkan nama file tanpa (.txt): ";
        cin >> filename;
        filename += ".txt";
        ofstream file(path + filename);

        if (!file.is_open()) {
            cout << "Gagal membuka file untuk penulisan" << endl;
            return 1;
        }

        file << maxReward << endl;
        for (int i = 0; i < maxRoute.size(); ++i)
        {
            file << maxRoute[i] << " ";
        }
        file << endl;
        for (int i = 0; i < maxRoutePoints.size(); ++i)
        {
            file << maxRoutePoints[i].col +1 << ", " << maxRoutePoints[i].row + 1 << endl;
        }
        file << endl << duration.count() << " ms";
        file.close();
    }
    return 0;
}