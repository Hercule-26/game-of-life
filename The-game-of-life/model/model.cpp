#include "model.h"

Model::Model(int rows, int cols, QObject *parent) : table(rows, cols) {
}

int Model::get_table_rows() {
    return table.rows();
}

int Model::get_table_cols() {
    return table.cols();
}

void Model::reset() {
    table.reset();
}

void Model::set(int row, int col, bool value) {
    table.set(row, col, value);
}

bool Model::get_at(int row, int col) {
    return table.get(row, col);
}

void Model::run_life() {
    qDebug() << "run life en cours d'execution";
    Table tmp_table(table.rows(), table.cols());

    for (int i = 0; i < table.rows(); ++i) {
        for (int j = 0; j < table.cols(); ++j) {
            int alive_neighbors = count_alive_neighbors(i, j);

            if (table.get(i, j) == true) {
                if (alive_neighbors < 2 || alive_neighbors > 3) {
                    tmp_table.set(i, j, false);
                } else {
                    tmp_table.set(i, j, true);
                }
            } else {
                if (alive_neighbors == 3) {
                    tmp_table.set(i, j, true);
                } else {
                    tmp_table.set(i, j, false);
                }
            }
        }
    }
    table = tmp_table;

    emit tableUpdated();
    qDebug() << "run life à fini d'etre executer";
}

int Model::count_alive_neighbors(int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;

            int neighbor_row = row + i;
            int neighbor_col = col + j;

            if (neighbor_row >= 0 && neighbor_row < table.rows() &&
                neighbor_col >= 0 && neighbor_col < table.cols()) {
                count += table.get(neighbor_row, neighbor_col);
            }
        }
    }

    return count;
}

