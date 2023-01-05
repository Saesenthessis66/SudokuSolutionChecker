#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Function that reads from given file and checks if input is correct.
std::pair<int,std::vector<std::vector<int>>> readFromFile(std::string fileName)
{
    std::vector<std::vector<int>> solution;

    std::fstream file;
    file.open(fileName);
    if (file.is_open())
    {
        std::vector<int> row;
        int rows = 0;
        std::string number;
        while (std::getline(file, number))
        {
            // Checking if there is more than 9 rows.
            rows++;
            if (rows > 9) { std::cout << "ERROR"; return { 1, solution }; }
            number.erase(std::remove_if(number.begin(), number.end(), ::isspace), number.end());
            // Checking i there is more than 9 columns.
            if (number.length() == 9)
            {
                for (int i = 0; i < number.length(); i++)
                {
                    // Checking if input is digit.
                    if (isdigit(number[i]))
                    {
                        row.push_back(number[i] - 48);
                    }
                    else { std::cout << "ERROR"; return { 1,solution }; }
                }
            }
            else { std::cout << "ERROR"; return {1, solution };
        }
            solution.push_back(row);
            row.clear();
        }
    }
    else { std::cout << "ERROR"; return { 1, solution }; }
    file.close();
    return {0,solution};
}

int rowCheck(std::vector<std::vector<int>> solution)
{
    for (int i = 0; i < solution.size(); i++)
    {
        for (int j = 0; j < solution[i].size(); j++)
        {
            int num = solution[i][j];
            {
                for (int k = j + 1; k + 2 < solution[i].size(); k++)
                {
                    if (num == solution[i][k])
                    {
                        std::cout << "WRONG"; return 2;
                    }
                }
            }
        }
    }
    return 0;
}

int columnCheck(std::vector<std::vector<int>> solution)
{
    for (int i = 0; i < solution.size(); i++)
    {
        for (int j = 0; j < solution[i].size(); j++)
        {
            int num = solution[j][i];
            {
                for (int k = j + 1; k + 2 < solution[i].size(); k++)
                {
                    if (num == solution[k][i])
                    {
                        std::cout << "WRONG"; return 2;
                    }
                }
            }
        }
    }
    return 0;
}

int boxCheck(std::vector<std::vector<int>> solution)
{
    for (int i = 0; i < solution.size(); i++)
    {
        if (i % 3 == 0)
        {
            for (int j = 0; j < solution[i].size(); j++)
                if (j % 3 == 0)
                {
                    std::vector<int> box;
                    box.push_back(solution[i + 2][j + 1]);
                    box.push_back(solution[i + 1][j + 2]);
                    for (int z = 0; z < 3; z++)
                    {
                        box.push_back(solution[i + z][j + z]);
                    }
                    for (int s = 0; s < box.size(); s++)
                    {
                        if (s + 1 < box.size())
                        {
                            for (int l = s + 1; l < box.size() - 1; l++)
                            {
                                if (box[s] == box[l])
                                {
                                    std::cout << "WRONG"; return 2;
                                }
                            }
                        }
                    }
                }
        }
    }
    return 0;
}

int run(std::string fileName)
{
    std::pair<int, std::vector<std::vector<int>>> pair = readFromFile(fileName);
    if (pair.first == 0)
    {
        if (rowCheck(pair.second) == 0 && columnCheck(pair.second) == 0 && boxCheck(pair.second) == 0)
        {
            std::cout << "CORRECT";
        }
    }
    else return 0;
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        run(argv[1]);
    }
    else std::cout << "ERROR";
    return 0;
}