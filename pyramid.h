#ifndef PYRAMID_H
#define PYRAMID_H

#include "utils.h"

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QMap>

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

    void on_fileComboBox_currentIndexChanged(int index);

private:
    Ui::Pyramid *ui;
    QMap<int, QString> images;
    void fillFilenamesToCombobox();
    void fillFilenamesToMap(QStringList filenames);
    void drawImage(int index);
};

#endif // PYRAMID_H
