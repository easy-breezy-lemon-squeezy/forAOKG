#pragma once
#include <vector>
#include <memory>
#include <random>
#include <iostream>

using namespace std;

class MazeGenerator
{
public:
    static shared_ptr<vector<vector<char>>> generate(unsigned width, unsigned height)
    {
        // �������� ����������� ���������� �� 0
        if ((width < 1) || (height < 1))
            return nullptr;

        // �������������� ������ �������� ������� maze
        // ������ ����� ������������ �� ���� ��������� 2x2 + 1 ���� �������� ������ � ����� ��� ����
        unsigned output_height = height * 2 + 1;
        unsigned output_width = width * 2 + 1;
        // �������������� ��������� �� ��������
        auto maze = make_shared<vector<vector<char>>>();
        // ������������� ������ ��������� �� ������
        maze.get()->reserve(output_height);
        // �������������� ��������� ������ �������� �� ������� �� ��������� � "�������" (�������) � ������ ������ ���� ����� 2x2

        for (unsigned i = 0; i < output_height; ++i)
        {
            vector<char> row;
            row.reserve(output_width);
            for (unsigned j = 0; j < output_width; ++j)
                // ���� ���� ������� � ������ �������� ������� � ����� ������� ���� ������� 2x2 - �� ��� ������ ������ � ���������
                if ((i % 2 == 1) && (j % 2 == 1))
                    row.push_back('0');
                else
                    // ���� ��� ������� ��� ����� ������ ��� ������� ��� ����� ����� - �� �������������� ���� ������� ������ ������� � ���������
                    if (((i % 2 == 1) && (j % 2 == 0) && (j != 0) && (j != output_width - 1)) ||
                        ((j % 2 == 1) && (i % 2 == 0) && (i != 0) && (i != output_height - 1)))
                        row.push_back('0');
                    else
                        // �� ���� ��������� ������� ������������� �����
                        row.push_back('3');
            maze.get()->push_back(move(row));
        }
        //1. �������� ������ ������ ���������. �� ���� ������ �� ����� ������������ ������ - ���� ���������.
        // �������������� ��������������� ������, ������� ����� ��������� � ���� �������������� �� ��������� ��� ������ �� ���������
        vector<unsigned> row_set;
        row_set.reserve(width);
        // 0 - ����� ��������, ��� ������ �� ����������� �������� ���������
        for (unsigned i = 0; i < width; ++i)
            row_set.push_back(0);
        // � �������������� ������� ��� ��������
        unsigned set = 1;
        // �������������� ��������� ��������� �����
        random_device rd;
        mt19937 mt(rd());
        // �� 0 �� 2 (2 �� ������) � ����� ���������� � int ����� ���� 0 - ��� ����� ���, ���� 1 - ����� ������ ����������
        uniform_int_distribution<int> dist(0, 2);
        // ���������� ���� ��������� ������
        for (unsigned i = 0; i < height; ++i)
        {
            //2. ��������� ������ ������, ������� �� ������ �� � ���� ���������, ��� ���������� ���������.
            //3. �������� ������ ����� ��� �����, �������� ����� �������, ��������� ������� :
            //	* ��������� ������� ������, ��������� ����� ��� ���
            //		* ���� ������� ������ � ������ ������ �������� ������� ������ � ���� �� ���������, ������ ���������� ����� ���� �����(��� ������������ �����)
            //		* ���� �� ������ �� ��������� �����, �� ���������� ���������, � ������� ��������� ������� ������ � ������ ������
            //4. �������� ������ �����, �������� ����� ������� :
            //	* ��������� ������� ������, ��������� ������ ����� ��� ���. *����� : *���������, ��� ������ ������� ����� �� ������� ���� ���� ������ ��� ������ �����(��� ������������ �������� ������������� ��������)
            //		* ���� ������ �������� ������������ ������ ������ ���������, �� �� ���������� ������ �����
            //		* ���� ������ �������� ������������ ������ ������ ���������, ������� �� ����� ������ �����, �� �� ���������� ������ �����
            //5. ������, ���������� ��������� ������ ��� ������������ � ��������� ��������
            //	* ���� �� ������ �������� ��� ���� ������ :
            //		* ���������� ������� ������
            //		* ������� � ����� ������ ��� ������ �����
            //		* ������� ������ � ������ ������ �� �� ���������
            //		* ������� ��� ������ �����
            //		* ���������� � ���� 2.
        }

        //	* ���� �� ������ ��������� �������� :
        //		*�������� ������ ����� ������ ������
        //		* ������������� ����� ������� :
        //			*���� ������� ������ � ������ ������ �������� ������� ������ ��������, �� :
        //			*������� ������ �����
        //			* ���������� ���������, � ������� ����������� ������� ������ � ������ ������
        //			* ����� �������� ������
        // ���������� ���� ��������� ������
        for (unsigned i = 0; i < height; ++i)
        {
            //2. ��������� ������ ������, ������� �� ������ �� � ���� ���������, ��� ���������� ���������.
            for (unsigned j = 0; j < width; ++j)
                if (row_set[j] == 0)
                    row_set[j] = set++;

            //3. �������� ������ ����� ��� �����, �������� ����� �������, ��������� �������:
            for (unsigned j = 0; j < width - 1; ++j)
            {
                //  * ��������� ������� ������, ��������� ����� ��� ���
                const auto right_wall = dist(mt);
                //      * ���� ������� ������ � ������ ������ �������� ������� ������ � ���� �� ���������, ������ ���������� ����� ���� �����(��� ������������ �����)
                if ((right_wall == 1) || (row_set[j] == row_set[j + 1]))
                    maze.get()->at(i * 2 + 1/*������� ��� � i-�� ���� ����� 2x2*/).at(j * 2 + 2/*������ ������� � (i;j) ������ 2x2*/) = '2';/*������� �����*/
                else
                {
                    //      * ���� �� ������ �� ��������� �����, �� ���������� ���������, � ������� ��������� ������� ������ � ������ ������
                    const auto changing_set = row_set[j + 1];
                    for (unsigned l = 0; l < width; ++l)
                        if (row_set[l] == changing_set)
                            row_set[l] = row_set[j];
                }
            }


            //4. �������� ������ �����, �������� ����� �������:
            for (unsigned j = 0; j < width; ++j)
            {
                //  * ��������� ������� ������, ��������� ������ ����� ��� ���. 
                const auto bottom_wall = dist(mt);
                //      * ���� ������ �������� ������������ ������ ������ ���������, �� �� ���������� ������ �����
                unsigned int count_current_set = 0;
                for (unsigned l = 0; l < width; ++l)
                    // ������� ���������� ����� �������� ���������
                    if (row_set[j] == row_set[l])
                        count_current_set++;
                //      * ���� ������ �������� ������������ ������ ������ ���������, ������� �� ����� ������ �����, �� �� ���������� ������ �����
                if ((bottom_wall == 1) && (count_current_set != 1)) {
                    maze.get()->at(i * 2 + 2).at(j * 2 + 1) = '2';
                    maze.get()->at(i * 2).at(j * 2) = '1';
                }

            }
            //*�����: *���������, ��� ������ ������� ����� �� ������� ���� ���� ������ ��� ������ �����(��� ������������ �������� ������������� ��������)
            // ������ ���� ��� �� ��������� ������
            if (i != height - 1)
            {
                for (unsigned j = 0; j < width; ++j) {
                    unsigned count_hole = 0;
                    for (unsigned l = 0; l < width; ++l)
                        if ((row_set[l] == row_set[j]) && (maze.get()->at(i * 2 + 2).at(l * 2 + 1) == '0'))
                            count_hole++;
                    if (count_hole == 0)
                        maze.get()->at(i * 2 + 2).at(j * 2 + 1) = '0';
                }
            }


            //5. ������, ���������� ��������� ������ ��� ������������ � ��������� ��������
            //  * ���� �� ������ �������� ��� ���� ������ :
            if (i != height - 1)
            {
                //      * ���������� ������� ������
                //      * ������� � ����� ������ ��� ������ �����
                /// ������ ������ � ������������������ ������� � ��� ��� ����������� � ������ ����� ������
                //      * ������� ������ � ������ ������ �� �� ���������
                for (unsigned j = 0; j < width; ++j)
                    if (maze.get()->at(i * 2 + 2/* �������� ������� ������ ����� � �������� ����*/).at(j * 2 + 1) == '2')
                        // ���� ������ ����, �� ������� ������ �� ���������
                        row_set[j] = 0;
                //      * ������� ��� ������ �����
                /// ������ ����� � ������ ����� ���� ����� ����������� (�������� ��� �������������)
            }
            //      * ���������� � ���� 2.

        }

        //	5.� ���� �� ������ ��������� ��������:
        //		*�������� ������ ����� ������ ������
        /// ������ ����� ��������� ��� ������������� ���������
        //		* ������������� ����� �������:
        for (unsigned int j = 0; j < width - 1; ++j)
        {
            //			*���� ������� ������ � ������ ������ �������� ������� ������ ��������, �� :
            if (row_set[j] != row_set[j + 1])
                //			*������� ������ �����
                maze.get()->at(output_height - 2).at(j * 2 + 2) = '0';
            //			* ���������� ���������, � ������� ����������� ������� ������ � ������ ������
                /// ��� ������ �� �����������, ��� ��� row_set �� ������ �� ����� ������������,
                /// � ��� ��������� � �������� ����� ������ �����, ����� �������� ����
            //			* ����� �������� ������
        }
        for (unsigned i = 0; i < maze.get()->size(); ++i)
        {
            for (unsigned j = 0; j < maze.get()->at(0).size(); ++j)
            {
                if (maze.get()->at(i).at(j) == '3') {
                    maze.get()->at(i).at(j) = '2';
                }
                
            }
        }
        for (unsigned i = 0; i < maze.get()->size(); ++i)
        {
            for (unsigned j = 0; j < maze.get()->at(0).size(); ++j)
            {
                if (i == 0) {
                    maze.get()->at(i).at(j) = '3';
                }
                else if (i == (maze.get()->size()-1)) {
                    maze.get()->at(i).at(j) = '3';
                }
                else if (j == 0) {
                    maze.get()->at(i).at(j) = '3';
                }
                else if (j == (maze.get()->size() - 1)) {
                    maze.get()->at(i).at(j) = '3';
                }
            }
        }
        // ������ ��������� �� ���������� ��������
        return maze;
    }

    static void print(const shared_ptr<vector<vector<char>>>& maze)
    {
        // ��������� ��������� �� nullptr
        if (maze == nullptr)
            return;


        // ��������� ��������� � ������� � �������
        for (unsigned i = 0; i < maze.get()->size(); ++i)
        {
            for (unsigned j = 0; j < maze.get()->at(0).size(); ++j)
                cout << maze.get()->at(i).at(j);
            cout << endl;
        }

    }


private:
    MazeGenerator() = default;
};