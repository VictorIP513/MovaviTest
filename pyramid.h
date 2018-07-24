#ifndef PYRAMID_H
#define PYRAMID_H

#include "utils.h"

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class Pyramid;
}

class Pyramid : public QMainWindow
{
    Q_OBJECT

public:
    explicit Pyramid(QWidget *parent = nullptr);
    ~Pyramid();

private slots:
    void on_openImagesAction_triggered();

private:
    Ui::Pyramid *ui;
    QStringList images;
    void fillFilenamesToCombobox();
    void drawImage();
};

#endif // PYRAMID_H
