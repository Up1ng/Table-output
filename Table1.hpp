#ifndef TABLE_HPP
#define TABLE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

enum Alignment
{
    LEFT,
    RIGHT,
    CENTER
};
class Cell
{
private:
    string text;

public:
    Cell(string t = "");
    string format(int width, Alignment align); // Изменен тип параметра align
    string getText();
};

class Row
{
private:
    vector<Cell> cells;

public:
    Row(const vector<string> &cellTexts); // Добавлена константная ссылка
    int getCellCount();
    string getCellText(int index);
    Cell getCell(int index);
};

class Table
{
private:
    vector<Row> rows;
    string formatLine;
    vector<int> columnWidths;

public:
    void setFormatLine(const string &fmt); // Добавлена константная ссылка
    void addRow(const Row &r);             // Добавлена константная ссылка
    void calculateWidths();
    void print(ostream &out);
};

class FileManager
{
public:
    static vector<string> readLines(const string &filename);       // Константная ссылка
    static void write(const string &filename, const string &data); // Константные ссылки
};

vector<string> splitByTab(const string &line);

#endif