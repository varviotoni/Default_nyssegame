#ifndef SIMPLEMAINWINDOW_HH
#define SIMPLEMAINWINDOW_HH

#include "interfaces/iactor.hh"
#include "graphics/simpleactoritem.hh"
#include "city.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>

namespace Ui {
class SimpleMainWindow;
}

namespace StudentSide {

class SimpleMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimpleMainWindow(std::shared_ptr<StudentSide::City> city, QWidget *parent = 0);
    virtual ~SimpleMainWindow();

    void setSize(int w, int h);
    void setTick(int t);

    virtual void addActor(int locX, int locY, int type = 0);
    void updateCoords(int nX, int nY);
    void setPicture(QImage &img);

signals:
    void gameStarted();

private slots:
    void on_startButton_clicked();

private:
    Ui::SimpleMainWindow *ui;
    std::shared_ptr<StudentSide::City> city_;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<QGraphicsItem*> actors_;
    CourseSide::SimpleActorItem* last_;

    int width_ = 500; //pxls
    int height_ = 500;
    int tick_ = 500; //ms
};

} //namespace
#endif // SIMPLEMAINWINDOW_HH
