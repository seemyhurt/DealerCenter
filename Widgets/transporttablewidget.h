#ifndef TRANSPORTTABLEWIDGET_H
#define TRANSPORTTABLEWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class TransportsModel;

class TransportTableWidget : public QWidget
{
    Q_OBJECT
public:
    TransportTableWidget(QSharedPointer<TransportsModel> model,
                         QWidget * parent = nullptr);

private:
    QSharedPointer<TransportsModel> _transportModel;
};


#endif // TRANSPORTTABLEWIDGET_H
