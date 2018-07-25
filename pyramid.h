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
#include <QSize>
#include <QPixmap>
#include <QtMath>

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
    void on_layerCoefficientDoubleSpinBox_valueChanged(double newCoefficientValue);
    void on_exitAction_triggered();
    void on_layerComboBox_currentIndexChanged(int index);

private:
    Ui::Pyramid *ui;
    QMap<int, QString> images;
    QPixmap currentImage;
    PyramidImage *pyramidImage;
    double layerCoefficient = 2.0;
    bool enableSmoothTransformation = false;
    void fillFilenamesToCombobox();
    void fillFilenamesToMap(QStringList filenames);
    void fillLayerCombobox();
    void fillSizeInformation();
    void drawImage();
    int getMaxLayers();
};

#endif // PYRAMID_H
