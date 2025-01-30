#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void launchGame();
    void toggleOnlineInputs(bool checked);
    void toggleLocalInputs(bool checked);
    void setupLocalMode();
    void setupOnlineMode();
    void setupCommonComponents();
private:
    QVBoxLayout *layout;

    QRadioButton* radioLocal;
    QRadioButton* radioOnline;
    QPushButton* startButton;

    QLabel* ipLabel;
    QLineEdit* ipInput;
    QLabel* portLabel;
    QLineEdit* portInput;

    QLabel* widthLabel;
    QLineEdit* widthInput;
    QLabel* heightLabel;
    QLineEdit* heightInput;
};

#endif // MAINWINDOW_H
