#include "Table1.hpp"

Alignment charToAlignment(char c)
{
    switch (c)
    {
    case '>':
        return RIGHT;
    case '=':
        return CENTER;
    default:
        return LEFT;
    }
}

Cell::Cell(string t)
{
    text = t;
}

string Cell::format(int width, Alignment align)
{
    int spaces = width - text.size();
    if (spaces < 0)
        spaces = 0;

    string result;
    switch (align)
    {
    case LEFT:
        result = text;
        for (int i = 0; i < spaces; i++)
            result += ' ';
        break;
    case RIGHT:
        for (int i = 0; i < spaces; i++)
            result += ' ';
        result += text;
        break;
    case CENTER:
        int left = spaces / 2;
        int right = spaces - left;
        for (int i = 0; i < left; i++)
            result += ' ';
        result += text;
        for (int i = 0; i < right; i++)
            result += ' ';
        break;
    }
    return result;
}

string Cell::getText()
{
    return text;
}

Row::Row(const vector<string> &cellTexts)
{
    for (int i = 0; i < cellTexts.size(); i++)
    {
        cells.push_back(Cell(cellTexts[i]));
    }
}

int Row::getCellCount()
{
    return cells.size();
}

string Row::getCellText(int index)
{
    if (index < cells.size())
        return cells[index].getText();
    else
        return "";
}

Cell Row::getCell(int index)
{
    if (index < cells.size())
        return cells[index];
    else
        return Cell("");
}

void Table::setFormatLine(const string &fmt)
{
    formatLine = fmt;
}

void Table::addRow(const Row &r)
{
    rows.push_back(r);
}

void Table::calculateWidths()
{
    int cols = formatLine.size();
    columnWidths.resize(cols, 0);

    for (int i = 0; i < rows.size(); i++)
    {
        for (int j = 0; j < cols; j++)
        {
            string text = rows[i].getCellText(j);
            if (text.size() > columnWidths[j])
            {
                columnWidths[j] = text.size();
            }
        }
    }
}
void Table::print(ostream &out)
{
    int cols = formatLine.size();

    auto printBorder = [&]()
    {
        out << "+";
        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < columnWidths[i] + 2; j++)
                out << "-";
            out << "+";
        }
        out << "\n";
    };

    printBorder();
    for (int i = 0; i < rows.size(); i++)
    {
        out << "|";
        for (int j = 0; j < cols; j++)
        {
            Alignment align;
            switch (formatLine[j])
            {
            case '>':
                align = RIGHT;
                break;
            case '=':
                align = CENTER;
                break;
            default:
                align = LEFT;
                break;
            }
            string formatted = rows[i].getCell(j).format(columnWidths[j], align);
            out << " " << formatted << " |";
        }
        out << "\n";
        printBorder();
    }
}
vector<string> FileManager::readLines(const string &filename)
{
    vector<string> lines;
    ifstream in(filename);

    string line;
    while (getline(in, line))
    {
        lines.push_back(line);
    }
    in.close();
    return lines;
}

void FileManager::write(const string &filename, const string &data)
{
    ofstream out(filename);
    out << data;
    out.close();
}

vector<string> splitByTab(const string &line)
{
    vector<string> result;
    string current = "";

    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == '\t')
        {
            result.push_back(current);
            current = "";
        }
        else
        {
            current += line[i];
        }
    }

    result.push_back(current);
    return result;
}