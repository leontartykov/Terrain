#include "main_window.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    view = ui->graphicsView;
    scene = new QGraphicsScene(ui->graphicsView);
    view->setScene(scene);
    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::init_terrain()
{
    terrain.set_meta_config(ui->spinbox_octaves->value(), ui->spinbox_gain->value(), ui->spinbox_lacunarity->value(),
                                                ui->spinbox_seed->value(), ui->spinbox_frequency->value());
    terrain.set_rotate_angles(ui->spinbox_rotate_x->value(), ui->spinbox_rotate_y->value(), ui->spinbox_rotate_z->value());

    //qDebug() << "form_landscape.";
    terrain.form_terrain();

    //qDebug() << "find_all_landscapes.";
    terrain.find_all_normals();

    //qDebug() << "find_average_normals_of_each_node().";
    terrain.find_average_normals_of_each_node();

    rotate_t rotate_angles;
    rotate_angles.angle_x = ui->spinbox_rotate_x->value();
    rotate_angles.angle_y = ui->spinbox_rotate_y->value();
    rotate_angles.angle_z = ui->spinbox_rotate_z->value();

    //qDebug() << "rotate_landscape.";
    //landscape.rotate_landscape(rotate_angles);

    double scale = ui->spinbox_scale->value();
    //terrain.set_scale_landscape(scale);
    //landscape.scale_landscape();

    //qDebug() << "transform_points_to_screen.";
    //terrain.transform_points_to_screen();

    //qDebug() << "remove_invisible_lines.";
    //terrain.remove_invisible_lines(zbuffer, scene, light.get_position());

    //qDebug() << "draw_landscape.";
    //landscape.draw_landscape(zbuffer, scene, view);
}

void MainWindow::init_light()
{
    int light_x = ui->spinbox_light_position_x->value(),
         light_y = ui->spinbox_light_position_y->value(),
         light_z = ui->spinbox_light_position_z->value();

    light.set_position(light_x, light_y, light_z);
}
