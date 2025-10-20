#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    m_detected_segments.clear();
    update();
}

void DrawingCanvas::paintLines(){
    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection(){
    m_detected_segments.clear();
    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    cout << "Starting segment detection on image of size: " << image.width() << "x" << image.height() << endl;


    for(int i = 1; i < image.width() - 1; i++){
        for(int j = 1; j < image.height() - 1; j++){




            if (image.pixel(i, j) == 0xffffffff) {
                continue;
            }


            int active_neighbors = 0;
            for(int m = -1; m <= 1; m++){
                for(int n = -1; n <= 1; n++){
                    if (m == 0 && n == 0) continue;

                    if (image.pixel(i + m, j + n) != 0xffffffff) {
                        active_neighbors++;
                    }
                }
            }



            if (active_neighbors >= 1 && active_neighbors <= 2) {
                m_detected_segments.append(QPoint(i, j));
            }
        }
    }
    cout << "Detection finished. Found " << m_detected_segments.size() << " candidate segments." << endl;
    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if(isPaintLinesClicked){
        painter.setRenderHint(QPainter::Antialiasing, false);
        pen.setColor(Qt::red);
        pen.setWidth(1);
        painter.setPen(pen);

        for(int i = 0; i < m_points.size() - 1; i += 2){
            painter.drawLine(m_points[i], m_points[i + 1]);
        }
        isPaintLinesClicked = false;
    }

    if(!m_detected_segments.isEmpty()){
        pen.setColor(QColor(160, 32, 240));
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        for(const QPoint& center : std::as_const(m_detected_segments)){

            painter.drawRect(center.x(), center.y(), 1, 1);
        }
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    m_points.append(event->pos());
    update();
}
