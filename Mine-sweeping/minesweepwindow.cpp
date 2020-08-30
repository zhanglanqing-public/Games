#include"minesweepwindow.h"
#include"ui_minesweepwindow.h"
#include<QLabel>
#include<vector>
#include<QPushButton>
#include<strstream>
#include<QString>
#include<iostream>
#include<QObject>
#include<QMessageBox>
#include<set>
#include<algorithm>
#include"time.h"
using namespace std;
MIneSweepWindow::MIneSweepWindow(QWidget *parent):QWidget(parent),ui(new Ui::MIneSweepWindow){
    qsrand(time(NULL));
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            array[j][i]=new QPushButton(this);
            array[j][i]->resize(50,50);
            array[j][i]->move(50*i,50*j);
            array[j][i]->show();
            array[j][i]->setStyleSheet("background-color: rgb(125, 116, 116);");
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            state[j][i]=0;
        }
    }
    random();
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            connect(array[j][i],SIGNAL(clicked()),this,SLOT( response() ) );
            visit[j][i]=0;
        }
    }
}

void MIneSweepWindow::response(){
   for(int i=0;i<10;i++){
       for(int j=0;j<10;j++){
           if(QObject::sender()==array[j][i]){
               if(state[j][i]==-1){
                   QMessageBox::warning(this, "啊！","踩到地雷被炸死咯(>_<)",QMessageBox::Yes);
                   init();
               }else{
                   recursion(j,i);
               }
           }
       }
   }
}

int MIneSweepWindow::get_num_mines(int m, int n){
    int cnt=0;
    if(state[m][n]==-1) return -1;
    for(int xx=-1;xx<=1;xx++){
        for(int yy=-1;yy<=1;yy++){
            if(!(xx==0&&yy==0)){
                if(m+xx<=9 && m+xx>=0 && n+yy>=0 && n+yy<=9){
                    if(state[m+xx][n+yy]==-1)cnt++;
                }
            }
        }
    }
    return cnt;
}

QString MIneSweepWindow::int_to_string(int x){
    string line;
    strstream strm;
    strm << x;
    strm >> line;
    return QString::fromStdString(line);
}

void MIneSweepWindow::recursion(int j, int i)
{
   if(!(j>=0&&j<=9&&i>=0&&i<=9))return;
   if(state[j][i]==-1)return;
   if(state[j][i]!=0){
       if(visit[j][i]==0){
           array[j][i]->setStyleSheet("background-color: rgb(255, 255, 255);");
           array[j][i]->setText(int_to_string(state[j][i]));
           visit[j][i]=1;
           current_cnt+=1;
           if(current_cnt==90){
               QMessageBox::warning(this, "啊！","成功了(^o^)",QMessageBox::Yes);
               init();
           }
       }
       else return;
   }
   else{
       if(visit[j][i]==0){
           array[j][i]->setStyleSheet("background-color: rgb(255, 255, 255);");
           visit[j][i]=1;
           current_cnt+=1;
           if(current_cnt==90){
               QMessageBox::warning(this, "啊！","成功了(^o^)",QMessageBox::Yes);
               init();
           }
           for(int xx=-1;xx<=1;xx++){
               for(int yy=-1;yy<=1;yy++){
                   if(!(xx==0&&yy==0)){
                       recursion(j+xx,i+yy);
                   }
               }
           }
       }
   }
}

void MIneSweepWindow::init(){
    current_cnt=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            array[j][i]->setStyleSheet("background-color: rgb(125, 116, 116);");
            array[j][i]->setText("");
            state[j][i]=0;
            visit[j][i]=0;
        }
    }
    random();
}

void MIneSweepWindow::random(){
    set<pair<int,int> > random_num;
    for(int i=0;i<100;i++){
        int random = qrand()%100;
        int row=random/10;
        int col=random%10;
        cout<<"first"<<col<<" second"<<row<<endl;
        random_num.insert(make_pair(col,row));
        if(random_num.size()==10)break;
    }
    for(auto p=random_num.begin();p!=random_num.end();p++){
        state[p->first][p->second]=-1;
        //array[p->first][p->second]->setText("!");
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            state[j][i]=get_num_mines(j,i);
        }
    }
}

MIneSweepWindow::~MIneSweepWindow(){
    delete ui;
}
