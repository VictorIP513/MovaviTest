#include "pyramidimage.h"

PyramidImage::PyramidImage(QPixmap image, double layerCoefficient) :
    image(image),
    layerCoefficient(layerCoefficient),
    originalImageSize(image.size())
{}

PyramidImage::~PyramidImage() {}

QPixmap PyramidImage::getCompressedImage()
{
    QSize newImageSize = getCompressedSize();
    if (enabledSmoothTransformation)
    {
        QPixmap scaledImage = image.scaled(newImageSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        return scaledImage.scaled(originalImageSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    else
    {
        QPixmap scaledImage = image.scaled(newImageSize, Qt::IgnoreAspectRatio);
        return scaledImage.scaled(originalImageSize, Qt::IgnoreAspectRatio);
    }
}

QSize PyramidImage::getCompressedSize()
{
    int newWidth = static_cast<int>(image.size().rwidth() / layerCoefficient);
    int newHeight = static_cast<int>(image.size().rheight() / layerCoefficient);
    return QSize(newWidth, newHeight);
}

void PyramidImage::enableSmoothTransformation(bool value)
{
    this->enabledSmoothTransformation = value;
}

int PyramidImage::getMaxLayersForSize(QSize imageSize, double layerCoefficient)
{
    int maxLayers = 0;
    while (imageSize.rheight() < 1 || imageSize.rwidth() < 1)
    {
        int newWidth = static_cast<int>(imageSize.rwidth() / layerCoefficient);
        int newHeight = static_cast<int>(imageSize.rheight() / layerCoefficient);
        imageSize.scale(newWidth, newHeight, Qt::IgnoreAspectRatio);
        ++maxLayers;
    }
    return maxLayers;
}
