#ifndef MODEL_H
#define MODEL_H
#include "table.h"
#include <QObject>

class Model: public QObject {
    Q_OBJECT
private:
    Table table;
public:
    explicit Model(int rows, int cols, QObject *parent = nullptr);

    int get_table_rows();
    int get_table_cols();
    bool get_at(int row, int col);
    void reset();
    void set(int row, int col, bool value);

    void run_life();
    int count_alive_neighbors(int row, int col);

signals:
    void tableUpdated();
};

#endif // MODEL_H
