#include "Table1.hpp"

int main()
{
    vector<string> lines = FileManager::readLines("input.txt");

    Table table;
    table.setFormatLine(lines[0]);

    for (int i = 1; i < lines.size(); i++)
    {
        if (lines[i].empty())
            continue;
        vector<string> cells = splitByTab(lines[i]);
        if (cells.size() == 0)
            continue;
        table.addRow(Row(cells));
    }

    table.calculateWidths();

    ofstream out("output.txt");
    table.print(out);
    out.close();
    return 0;
}
