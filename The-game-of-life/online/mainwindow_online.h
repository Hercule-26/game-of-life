#ifndef MAINWINDOW_ONLINE_H
#define MAINWINDOW_ONLINE_H

#include <QMainWindow>

class MainWindowOnline : public QMainWindow
{
    Q_OBJECT  // Assurez-vous que Q_OBJECT est présent

public:
    explicit MainWindowOnline(QWidget *parent = nullptr);
    ~MainWindowOnline();

private:
         // Les autres membres de ta classe (comme des widgets) vont aller ici
};

#endif // MAINWINDOW_ONLINE_H
