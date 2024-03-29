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
    void reload();

    void setTextPadding(int p);
    void setTextColor(QColor c);
    void setHoverColor(QColor c);
    void setPressColor(QColor c);

signals:
    void signalItemClicked(QVariant data); // 所有item点击
    void signalGroupClicked(QVariant data); // 仅分组
    void signalChildClicked(QVariant data); // 仅子项
    void signalPathDataClicked(QList<QVariant> data); // 所有item的路径（不包括root）的data
    void signalPathIndexClicked(QList<int> data); // 所有item的路径的index

public slots:

private:
    void initView();
    void setSubItem(int level, LayerItemInfo *parent);
    void clearView();
    void setLayerCurrentIndex(int level, int index);
    LayerItemInfo *getLayerItem(int current_level, LayerItemInfo* data, int level, int index);
    void emitItemClicked(LayerItemInfo *sub_item, int level, int i);

private:
    LayerItemInfo *m_data_root = nullptr;
    QHBoxLayout *m_main_hlayout;
    QList<QListWidget *> m_list_widgets;

    int text_padding = 6;
    QColor text_color = Qt::black;
    QColor hover_color = Qt::lightGray;
    QColor press_color = Qt::gray;
};

#endif // MULTILAYERSELECTOR_H
