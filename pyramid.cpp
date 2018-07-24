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

void Pyramid::drawImage(int index)
{
    QString currentImageFilename = images.value(index);
    QPixmap currentImage(currentImageFilename);
    ui->imageLabel->setPixmap(currentImage);
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
    drawImage(index);
}
