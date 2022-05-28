#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <memory>
#include <QApplication>

#include "../object/terrain/terrain.h"
#include "../object/light/light.h"
//#include "../invisible/zbuffer/zbuffer.hpp"
#include "../scene/scene_facade/scene_facade.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
        Q_OBJECT

    private:
        Ui::MainWindow *ui;
        QGraphicsScene *scene;
        QGraphicsView *view;
        QImage *image;
        QPixmap pixmap;

        Terrain terrain;
        PointLight light;
        std::shared_ptr<SceneFacade> _scene_facade;

     public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void init_terrain();
        void init_light();

     public slots:
        /*void rotate_landscape();
        void change_noise_parametrs();
        void change_size_noise();
        void change_light_position();
        void scale_landscape();*/
};

#endif
