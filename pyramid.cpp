#include "pyramid.h"
#include "ui_pyramid.h"

Pyramid::Pyramid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Pyramid)
{
    ui->setupUi(this);
}

Pyramid::~Pyramid()
{
    delete ui;
}

void Pyramid::fillFilenamesToCombobox()
{
    ui->fileComboBox->clear();
    foreach (int imageNumber, images.keys())
    {
        QString imageName = Utils::getFilenameFromPath(images.value(imageNumber));
        ui->fileComboBox->addItem(imageName);
    }
}

void Pyramid::fillFilenamesToMap(QStringList filenames)
{
    images.clear();
    for (int i = 0; i < filenames.size(); ++i)
    {
        images.insert(i, filenames.at(i));
    }
}

void Pyramid::drawImage()
{
    int selectedLayer = ui->layerComboBox->currentIndex();
    PyramidImage pyramidImage(currentImage, qPow(layerCoefficient, selectedLayer));
    pyramidImage.enableSmoothTransformation(enabledSmoothTransformation);
    ui->imageLabel->setPixmap(pyramidImage.getCompressedImage());
}

void Pyramid::fillLayerCombobox()
{
    int countLayers = getMaxLayers();
    ui->layerComboBox->clear();
    for (int i = 0; i < countLayers; ++i)
    {
        ui->layerComboBox->addItem("Layer " + QString::number(i));
    }
}

int Pyramid::getMaxLayers()
{
    return PyramidImage::getMaxLayersForSize(currentImage.size(), layerCoefficient);
}

void Pyramid::on_openImagesAction_triggered()
{
    QStringList openedImages = QFileDialog::getOpenFileNames(
                this,
                "Select one or more files to open",
                "",
                "Images (*.png *.jpg)");
    if (!openedImages.isEmpty())
    {
        fillFilenamesToMap(openedImages);
        fillFilenamesToCombobox();
    }
}

void Pyramid::on_fileComboBox_currentIndexChanged(int index)
{
    currentImage = QPixmap(images.value(index));
    fillLayerCombobox();
}

void Pyramid::on_layerComboBox_currentIndexChanged(int index)
{
    drawImage();
}


void Pyramid::on_smoothTransformationCheckBox_stateChanged(int newState)
{
    enabledSmoothTransformation = newState;
    drawImage();
}

void Pyramid::on_layerCoefficientDoubleSpinBox_valueChanged(double newCoefficientValue)
{
    layerCoefficient = newCoefficientValue;
    fillLayerCombobox();
    drawImage();
}

void Pyramid::on_exitAction_triggered()
{
    QApplication::quit();
}
