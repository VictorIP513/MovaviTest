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
    QVector<QPair<double, QString> > imagesDiagonal(filenames.size());
    for (int i = 0; i < filenames.size(); ++i)
    {
        QImageReader reader(filenames.at(i));
        imagesDiagonal[i].first = Utils::getDiagonalFromSize(reader.size());
        imagesDiagonal[i].second = filenames.at(i);
    }
    std::sort(imagesDiagonal.begin(), imagesDiagonal.end());
    for (int i = filenames.size() - 1; i >= 0; --i)
    {
        images.insert(filenames.size() - i - 1, imagesDiagonal.at(i).second);
    }
}

void Pyramid::drawImage()
{
    int selectedLayer = ui->layerComboBox->currentIndex();
    pyramidImage = new PyramidImage(currentImage, qPow(layerCoefficient, selectedLayer));
    pyramidImage->enableSmoothTransformation(enableSmoothTransformation);
    ui->imageLabel->setPixmap(pyramidImage->getCompressedImage());
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

void Pyramid::fillSizeInformation()
{
    QSize imageSize = pyramidImage->getCompressedSize();
    QString size = "Size: " + QString::number(imageSize.rwidth()) + "x" + QString::number(imageSize.rheight());
    ui->sizeLabel->setText(size);
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
    fillSizeInformation();
}

void Pyramid::on_layerComboBox_currentIndexChanged(int)
{
    drawImage();
    fillSizeInformation();
}


void Pyramid::on_smoothTransformationCheckBox_stateChanged(int newState)
{
    enableSmoothTransformation = newState;
    drawImage();
}

void Pyramid::on_layerCoefficientDoubleSpinBox_valueChanged(double newCoefficientValue)
{
    layerCoefficient = newCoefficientValue;
    fillLayerCombobox();
    drawImage();
    fillSizeInformation();
}

void Pyramid::on_saveImageAction_triggered()
{
    QString filename = QFileDialog::getSaveFileName(
                this,
                "Save As",
                "untitled.png",
                "Images (*.png *.jpg)");
    if (!filename.isEmpty())
    {
        QFile file(filename);
        file.open(QIODevice::WriteOnly);
        bool saveResult = currentImage.save(&file, "png");
        if (!saveResult)
        {
            QMessageBox::critical(
                        this,
                        "Error",
                        "Cannot create file " + filename,
                        QMessageBox::Ok);
        }
    }
}

void Pyramid::on_exitAction_triggered()
{
    QApplication::quit();
}

void Pyramid::on_aboutProgramAction_triggered()
{
    QMessageBox::information(
                this,
                "Information",
                "Данное приложение было сделано в качестве тестового задания на позицию Junior C++ Developer в Movavi",
                QMessageBox::Ok);
}
