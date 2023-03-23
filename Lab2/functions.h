#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;

struct worker;

string get_filename(); // Функція для введення імені файлу
bool check_date(int, int, int, int, int); // Функція для перевірки чи лежить дата в заданих рамках
void append_file(string); // Функція для додавання даних в файл
void read_data(string); // Функція для читання даних з файлу
void split_workers_to_files(string); // Функція для розділення робітників на 2 файли в залежності від віку
void choose_file_to_read(); // Функція для вибору файла для читання (Файл з робітниками молодшими 40 років або файл з робітниками старшими 40 років)