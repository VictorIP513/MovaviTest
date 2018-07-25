#ifndef PYRAMID_H
#define PYRAMID_H

#include "utils.h"
#include "pyramidimage.h"

#include <QDebug>
#include <QMainWindow>
#include <QString>
#include <QStringList>
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
    void on_smoothTransformationCheckBox_stateChanged(int newState);

private:
    Ui::Pyramid *ui;
    QMap<int, QString> images;
    bool enabledSmoothTransformation = false;
    void fillFilenamesToCombobox();
    void fillFilenamesToMap(QStringList filenames);
    void drawImage(int index);
};

#endif // PYRAMID_H
