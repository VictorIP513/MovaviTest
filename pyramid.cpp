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

void Pyramid::on_openImagesAction_triggered()
{
    QStringList openedImages = QFileDialog::getOpenFileNames(
                this,
                "Select one or more files to open",
                "",
                "Images (*.png *.jpg)");
    if (!openedImages.isEmpty())
    {
        images = openedImages;
        fillFilenamesToCombobox();
    }

}

void Pyramid::fillFilenamesToCombobox()
{
    ui->fileComboBox->clear();
    foreach (QString image, images)
    {
        QString imageName = Utils::getFilenameFromPath(image);
        ui->fileComboBox->addItem(imageName);
    }
    drawImage();
}

void Pyramid::drawImage()
{

}
