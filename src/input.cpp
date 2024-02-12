#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Tucil
{
    int buffer;
    int row;
    int col;
    int jumlah_sequence;
    int sequence_length;
    vector<vector<string>> matriks;
    vector<vector<string>> sequence;
    vector<int> reward_sequence;
};

int countWords(const string &str)
{
    stringstream ss(str);
    string word;
    int count = 0;

    while (ss >> word)
    {
        count++;
    }
    return count;
}


vector<vector<string>> generateMatriks(Tucil tucil, vector<string> token, int jumlah_token_unik)
{
    srand(time(0));
    vector<vector<string>> matriks(tucil.row, vector<string>(tucil.col));

    for (int i = 0; i < tucil.row; i++)
    {
        for (int j = 0; j < tucil.col; j++)
        {
            matriks[i][j] = token[rand() % jumlah_token_unik];
        }
    }
    return matriks;
}

vector<vector<string>> generateSequence(Tucil tucil , vector<string> token, int jumlah_token_unik)
{
    srand(time(0));
    vector<vector<string>> sequence(tucil.jumlah_sequence, vector<string>(tucil.sequence_length));
    for (int i = 0; i < tucil.jumlah_sequence; i++)
    {
        int seq_random = rand() % (tucil.sequence_length - 2 + 1) + 2;
        for (int j = 0; j < seq_random; j++)
        {
            sequence[i][j] = token[rand() % jumlah_token_unik];
        }
    }
    return sequence;
}

vector<int> generateRewardSequence(Tucil tucil)
{
    srand(time(0));
    vector<int> reward_sequence(tucil.jumlah_sequence);
    for (int i = 0; i < tucil.jumlah_sequence; i++)
    {
        reward_sequence[i] = rand() % 100;
    }
    return reward_sequence;
}

void checkData(Tucil tucil)
{
    cout << "\nBerikut adalah data yang dihasilkan: \n\n";
    cout << "Buffer size: " << tucil.buffer << endl;
    cout << "Row matriks: " << tucil.row << endl;
    cout << "Col matriks: " << tucil.col << endl;
    cout << "\nMatriks: " << endl;
    for (int i = 0; i < tucil.row; i++)
    {
        for (int j = 0; j < tucil.col; j++)
        {
            cout << tucil.matriks[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nJumlah sequence: " << tucil.jumlah_sequence << endl;
    cout << "Sequence length: " << tucil.sequence_length << endl;
    cout << "\nSequences: " << endl;
    for (int i = 0; i < tucil.jumlah_sequence; i++)
    {
        cout << "Sequence " << i + 1 << ": ";
        for (int j = 0; j < tucil.sequence[i].size(); j++)
        {
            cout << tucil.sequence[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nReward sequences: " << endl;
    for (int i = 0; i < tucil.jumlah_sequence; i++)
    {
        cout << "Sequence " << i + 1 << ": " << tucil.reward_sequence[i] << endl;
    }
    cout << endl;
}

Tucil read_file()
{
    Tucil tucil;
    string filename, line;
    int temp;
    string path = "../test/";
    cout << "Masukkan nama file tanpa (.txt): ";
    cin >> filename;
    filename += ".txt";
    ifstream file(path + filename);

    while (!file.is_open())
    {
        cout << "File tidak ditemukan" << endl;
        cout << "Masukkan nama file tanpa (.txt): ";
        cin >> filename;
        filename += ".txt";
        file.open(filename);
    }

    file >> tucil.buffer >> tucil.col >> tucil.row;

    tucil.matriks.resize(tucil.row, vector<string>(tucil.col));
    for (int i = 0; i < tucil.row; i++)
    {
        for (int j = 0; j < tucil.col; ++j)
        {
            file >> tucil.matriks[i][j];
        }
    }

    file >> tucil.jumlah_sequence;
    getline(file, line);
    tucil.sequence_length = 0;

    tucil.sequence.resize(tucil.jumlah_sequence, vector<string>(tucil.sequence_length));
    for (int i = 0; i < tucil.jumlah_sequence; i++)
    {
        getline(file, line);
        temp = countWords(line);
        if (temp > tucil.sequence_length)
        {
            tucil.sequence_length = temp;
            for (int i = 0; i < tucil.jumlah_sequence; i++)
            {
                tucil.sequence[i].resize(tucil.sequence_length);
            }
        }
        stringstream ss(line);
        string word;
        vector<string> words;
        int j = 0;
        while (ss >> word)
        {
            tucil.sequence[i][j] = word;
            j++;
        }
        getline(file, line);
        tucil.reward_sequence.push_back(stoi(line));
    }

    file.close();
    return tucil;
}

Tucil CLI()
{
    Tucil tucil;
    string temp;
    int jumlah_token_unik;
    vector<string> token;

    cout << "Masukkan jumlah token unik: " << endl;
    cin >> jumlah_token_unik;
    token.resize(jumlah_token_unik);
    cout << "Masukkan token unik sekaligus (contoh: 7A 55 E9): " << endl;
    for (int i = 0; i < jumlah_token_unik; ++i)
    {
        cin >> temp; 
        token[i] = temp;
    }
    
    cout << "Masukkan buffer size: " << endl;
    cin >> tucil.buffer; 
    cout << "Masukkan row x col matriks (contoh: 6 6): " << endl;
    cin >> tucil.row ;
    cin >> tucil.col;
    cout << "Masukkan jumlah sequence: " << endl;
    cin >> tucil.jumlah_sequence; 
    cout << "Masukkan sequence length: " << endl;
    cin >> tucil.sequence_length;
    
    tucil.matriks = generateMatriks(tucil, token, jumlah_token_unik);
    tucil.sequence = generateSequence(tucil, token, jumlah_token_unik);
    tucil.reward_sequence = generateRewardSequence(tucil);
    
    return tucil;
}