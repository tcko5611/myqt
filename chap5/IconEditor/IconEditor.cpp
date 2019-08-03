#include <QMouseEvent>
#include <QPainter>

#include "IconEditor.h"

IconEditor::IconEditor(QWidget *parent)
{
  setAttribute(Qt::WA_StaticContents);
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  color_ = Qt::black;
  zoom_ = 8;
  image_ = QImage(16, 16, QImage::Format_ARGB32);
  image_.fill(QColor(0, 0 , 0, 0));
}

IconEditor::~IconEditor()
{
}

void IconEditor::setIconImage(const QImage &image)
{
  if (image_ != image) {
    image_ = image;
    update();
    updateGeometry();
  }
}

void IconEditor::setZoomFactor(int zoom)
{
  if (zoom_ != zoom) {
    zoom_ = zoom;
    update();
  }
}

void IconEditor::mouseMoveEvent(QMouseEvent *event)
{
  if (event->buttons() & Qt::LeftButton) {
    setImagePixel(event->pos(), true);
  }
  else if (event->buttons() & Qt::RightButton) {
    setImagePixel(event->pos(), false);
  }
}

void IconEditor::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    setImagePixel(event->pos(), true);
  }
  else if (event->button() == Qt::RightButton) {
    setImagePixel(event->pos(), false);
  }
}

void IconEditor::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  QPen pen(palette().color(QPalette::Foreground));
  // draw grids
  if (zoom_ > 3) {
    for (int i = 0; i <= image_.width(); ++i) {
      painter.drawLine(i*zoom_, 0, i*zoom_, image_.height()* zoom_);
    }
    for (int j = 0; j <= image_.height(); ++j) {
      painter.drawLine(0, j *zoom_, image_.width() * zoom_, j*zoom_);
    }
  }
  // draw image
  for (int i = 0; i < image_.width(); ++i) {
    for (int j = 0; j < image_.height(); ++j) {
      QRect r = pixelRect(i, j);
      if (event->region().intersects(r)) {
	QColor c = image_.pixelColor(i,j);
	painter.fillRect(r, c);
      }
    }
  }
}

QRect IconEditor::pixelRect(int i, int j) const
{
  return QRect(i * zoom_, j * zoom_, zoom_, zoom_);
}

void IconEditor::setImagePixel(const QPoint &pos, bool opaque)
{
  int i = pos.x() / zoom_;
  int j = pos.y() / zoom_;
  if (image_.rect().contains(i, j)) {
    if (opaque) {
      image_.setPixelColor(i, j, color_);
    }
    else {
      image_.setPixelColor(i, j, QColor(255, 0, 0, 0));
    }
    update(pixelRect(i, j));
  }
}
