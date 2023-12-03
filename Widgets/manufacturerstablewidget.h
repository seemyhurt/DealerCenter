#ifndef MANUFACTURERSTABLEWIDGET_H
#define MANUFACTURERSTABLEWIDGET_H

#include <QWidget>
#include <QSharedPointer>

class ManufacturersModel;
class ManufacturerDBService;
struct ManufacturerData;

class ManufacturersTableWidget : public QWidget
{
    Q_OBJECT
public:
    ManufacturersTableWidget(bool enableControl, QWidget * parent = nullptr);

private slots:
    void handleNeedAddManufacturer();

private:
    QSharedPointer<ManufacturersModel> _manufacturersModel;
};

#endif // MANUFACTURERSTABLEWIDGET_H
