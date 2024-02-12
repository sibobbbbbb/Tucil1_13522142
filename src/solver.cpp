#include <iostream>
#include <vector>
#include <utility>
#include "input.cpp"

using namespace std;

struct Point
{
    int row;
    int col;
    Point(int r, int c) : row(r), col(c) {}
};

struct RouteInfo
{
    vector<string> route;
    int reward;
    RouteInfo(vector<string> &r, int rw) : route(r), reward(rw) {}
};

int countSeqLength(Tucil tucil, int idx)
{
    int count = 0;
    for (int i = 0; i < tucil.sequence_length; i++)
    {
        if (tucil.sequence[idx][i] != "")
        {
            count++;
        }
    }
    return count;
}

int countScore(Tucil tucil, vector<string> temp)
{
    int score = 0;
    int size = temp.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < tucil.jumlah_sequence; j++)
        {
            int length = countSeqLength(tucil, j);
            if (size - i >= length)
            {
                int count = 0;
                for (int k = 0; k < length; k++)
                {
                    if (temp[i + k] == tucil.sequence[j][k])
                    {
                        count++;
                    }
                }
                if (count == length)
                {
                    score += tucil.reward_sequence[j];
                }
            }
        }
    }

    if (score == 0)
    {
        score = -1;
    }

    return score;
}

int maxReward = 0;
vector<string> maxRoute;
vector<Point> maxRoutePoints;

void searchRoute(Tucil tucil, vector<vector<string>> &matrix, int row, int col, vector<string> &route, vector<Point> &routePoints, vector<vector<bool>> &visited, int buffer, bool isVertical)
{
    route.push_back(matrix[row][col]);
    routePoints.push_back(Point(row, col));
    visited[row][col] = true;
    int tempReward = countScore(tucil, route);
    if (tempReward > maxReward)
    {
        maxReward = tempReward;
        maxRoute = route;
        maxRoutePoints = routePoints;
    }

    if (route.size() == buffer)
    {
        route.pop_back();
        routePoints.pop_back();
        visited[row][col] = false;
        return;
    }

    if (isVertical)
    {
        for (int i = 0; i < tucil.row; ++i)
        {
            if (!visited[i][col])
            {
                searchRoute(tucil, matrix, i, col, route, routePoints, visited, buffer, !isVertical);
            }
        }
    }

    else
    {
        for (int j = 0; j < tucil.col; ++j)
        {
            if (!visited[row][j])
            {
                searchRoute(tucil, matrix, row, j, route, routePoints, visited, buffer, !isVertical);
            }
        }
    }

    route.pop_back();
    routePoints.pop_back();
    visited[row][col] = false;
}