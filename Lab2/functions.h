#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;

struct worker;

string get_filename(); // ������� ��� �������� ���� �����
bool check_date(int, int, int, int, int); // ������� ��� �������� �� ������ ���� � ������� ������
void append_file(string); // ������� ��� ��������� ����� � ����
void read_data(string); // ������� ��� ������� ����� � �����
void split_workers_to_files(string); // ������� ��� ��������� �������� �� 2 ����� � ��������� �� ���
void choose_file_to_read(); // ������� ��� ������ ����� ��� ������� (���� � ���������� ��������� 40 ���� ��� ���� � ���������� �������� 40 ����)