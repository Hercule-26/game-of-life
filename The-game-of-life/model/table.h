#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <QDebug>

class Table {
private:
    std::vector<std::vector<bool>> table;
public:
    inline Table(int rows, int cols): table(rows, std::vector<bool>(cols, false)) {};
    inline Table(std::vector<std::vector<bool>> table) : table(table) {};

    inline int rows() const { return table.size(); }
    inline int cols() const { return table.empty() ? 0 : table[0].size(); }
    inline bool get(int row, int col);
    inline void reset();
    inline void set(int row, int col, bool value);
};

bool Table::get(int row, int col) {
    return table[row][col];
}

void Table::reset() {
    for (int i = 0; i < rows(); ++i) {
        for (int j = 0; j < cols(); ++j) {
            table[i][j] = false;
        }
    }
}

void Table::set(int row, int col, bool value) {
    table[row][col] = value;
}

#endif // TABLE_H
