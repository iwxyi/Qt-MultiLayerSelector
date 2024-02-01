#include "multilayerselector.h"
#include <QDebug>

MultiLayerSelector::MultiLayerSelector(QWidget *parent) : QWidget(parent)
{
    m_main_hlayout = new QHBoxLayout(this);
}

void MultiLayerSelector::setData(LayerItemInfo *data)
{
    m_data_root = data;
    initView();
}

void MultiLayerSelector::initView()
{
    if (m_data_root == nullptr)
        return;

    // 初始化最外面一层
    setSubItem(0, m_data_root);
}

void MultiLayerSelector::setSubItem(int level, LayerItemInfo* parent)
{
    if (level < 0 || parent == nullptr)
        return;
    
    // 如果数量不够，则生成一个新的widget
    if (m_list_widgets.size() <= level)
    {
        QListWidget* list_widget = new QListWidget(this);
        list_widget->setStyleSheet("QListWidget{border:1px solid #000000;}");
        m_list_widgets.append(list_widget);
        m_main_hlayout->addWidget(list_widget);
    }
    
    // 清空已有的item及其widget
    QListWidget* list_widget = m_list_widgets.at(level);
    if (list_widget->count() > 0)
    {
        for (int i = 0; i < list_widget->count(); i++)
        {
            QListWidgetItem* item = list_widget->item(i);
            QWidget* widget = list_widget->itemWidget(item);
            widget->deleteLater();
            // delete item;
        }
        list_widget->clear();
    }
    
    // 加载新的item
    for (int i = 0; i < parent->subItems().size(); i++)
    {
        LayerItemInfo* sub_item = parent->itemAt(i);
        QListWidgetItem* item = new QListWidgetItem(list_widget);
        InteractiveButtonBase* button = new InteractiveButtonBase(sub_item->title(), list_widget);
        list_widget->setItemWidget(item, button);
    }
    
    // 加载下一级
    if (parent->currentSubItem() != nullptr)
    {
        setSubItem(level + 1, parent->currentSubItem());
    }
    
}

void MultiLayerSelector::clearView()
{
    for (int i = 0; i < m_list_widgets.size(); i++)
    {
        m_list_widgets.at(i)->deleteLater();
    }
    m_list_widgets.clear();
}
