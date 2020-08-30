#ifndef MINESWEEPWINDOW_H
#define MINESWEEPWINDOW_H

#include <QWidget>
#include<QString>
using namespace std;
#include<QPushButton>
namespace Ui {
class MIneSweepWindow;
}

class MIneSweepWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MIneSweepWindow(QWidget *parent = 0);
    ~MIneSweepWindow();
public slots:
    void response();
private:
    Ui::MIneSweepWindow *ui;
    int state[10][10];
    int get_num_mines(int m,int n);
    QString int_to_string(int x);
    QPushButton* array[10][10];
    void recursion(int j,int i);
    int current_cnt=0;
    int visit[10][10];
    void init();
    void random();
};

#endif // MINESWEEPWINDOW_H
