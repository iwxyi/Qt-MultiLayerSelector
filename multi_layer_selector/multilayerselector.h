#ifndef MULTILAYERSELECTOR_H
#define MULTILAYERSELECTOR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include "interactivebuttonbase.h"
#include "layeriteminfo.h"

class MultiLayerSelector : public QWidget
{
    Q_OBJECT
public:
    explicit MultiLayerSelector(QWidget *parent = nullptr);

    void setData(LayerItemInfo *data);

signals:

public slots:

private:
    void initView();
    void setSubItem(int level, LayerItemInfo *parent);
    void clearView();
    void setLayerCurrentIndex(int level, int index);
    LayerItemInfo *getLayerItem(int current_level, LayerItemInfo* data, int level, int index);

private:
    LayerItemInfo *m_data_root = nullptr;

    QHBoxLayout *m_main_hlayout;
    QList<QListWidget *> m_list_widgets;
};

#endif // MULTILAYERSELECTOR_H
