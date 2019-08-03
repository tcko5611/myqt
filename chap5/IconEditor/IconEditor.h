#ifndef ICONEDITOR_H /* -*-c++-*- */
#define ICONEDITOR_H

#include <QWidget>
#include <QRect>
#include <QColor>
#include <QImage>

class IconEditor : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
  Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
  Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
  IconEditor(QWidget *parent = 0);
  ~IconEditor();
  QColor penColor() { return color_; }
  void setPenColor(const QColor& c) { color_ = c;}
  QImage iconImage() { return image_; }
  void setIconImage(const QImage &image);
  int zoomFactor() { return zoom_; }
  void setZoomFactor(int zoom);

protected:
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

private:
  QRect pixelRect(int i, int j) const;
  void setImagePixel(const QPoint &pos, bool opaque);
  QColor color_;
  QImage image_;
  int zoom_;
};

#endif /* ICONEDITOR_H */
