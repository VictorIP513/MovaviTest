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
        QSize imageSize = reader.size();
        if (imageSize == QSize(-1, -1))
        {
            QMessageBox::critical(
                        this,
                        "Error",
                        "Cannot read file " + filenames.at(i) + ". " + reader.errorString(),
                        QMessageBox::Ok);
            imagesDiagonal.remove(i);
            continue;
        }
        imagesDiagonal[i].first = Utils::getDiagonalFromSize(reader.size());
        imagesDiagonal[i].second = filenames.at(i);
    }
    std::sort(imagesDiagonal.begin(), imagesDiagonal.end());
    for (int i = imagesDiagonal.size() - 1; i >= 0; --i)
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

void Pyramid::setMaxValueInLayerSpinBox()
{
    QSize imageSize = pyramidImage->getCompressedSize();
    double spinBoxMaxValue = defaultMaxValueInLayerSpinBox;
    spinBoxMaxValue = qMin(static_cast<int>(spinBoxMaxValue), imageSize.rheight());
    spinBoxMaxValue = qMin(static_cast<int>(spinBoxMaxValue), imageSize.rwidth());
    ui->layerCoefficientDoubleSpinBox->setMaximum(spinBoxMaxValue);
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
        if (!images.isEmpty())
        {
            ui->layerCoefficientDoubleSpinBox->setEnabled(true);
            ui->smoothTransformationCheckBox->setEnabled(true);
            ui->saveImageAction->setEnabled(true);
            ui->countImagesOpenedLabel->setText("Opened " + QString::number(images.count()) + " images");
        }
        else
        {
            ui->layerCoefficientDoubleSpinBox->setEnabled(false);
            ui->smoothTransformationCheckBox->setEnabled(false);
            ui->saveImageAction->setEnabled(false);
            ui->sizeLabel->setText("");
            ui->countImagesOpenedLabel->setText("");
        }
    }
}

void Pyramid::on_fileComboBox_currentIndexChanged(int index)
{
    bool loadResult = currentImage.load(images.value(index));
    if (!loadResult)
    {
        QMessageBox::critical(
                    this,
                    "Error",
                    "Cannot open file " + images.value(index),
                    QMessageBox::Ok);
        ui->layerCoefficientDoubleSpinBox->setEnabled(false);
        ui->smoothTransformationCheckBox->setEnabled(false);
        ui->saveImageAction->setEnabled(false);
    }
    else
    {
        ui->layerCoefficientDoubleSpinBox->setEnabled(true);
        ui->smoothTransformationCheckBox->setEnabled(true);
        ui->saveImageAction->setEnabled(true);
    }
    fillLayerCombobox();
    fillSizeInformation();
    setMaxValueInLayerSpinBox();
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
        bool saveResult = pyramidImage->getCompressedImage().save(&file, "png");
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
