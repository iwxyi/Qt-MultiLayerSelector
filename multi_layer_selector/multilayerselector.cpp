#include "multilayerselector.h"
#include <QDebug>
#define MULTI_LAYER_SELECTOR_DEBUG \
    if (0)                         \
    qDebug()

MultiLayerSelector::MultiLayerSelector(QWidget *parent) : QWidget(parent)
{
    m_main_hlayout = new QHBoxLayout(this);
}

void MultiLayerSelector::setData(LayerItemInfo *data)
{
    m_data_root = data;
    initView();
}

void MultiLayerSelector::reload()
{
    setData(m_data_root);
}

void MultiLayerSelector::setTextPadding(int p)
{
    this->text_padding = p;
}

void MultiLayerSelector::setTextColor(QColor c)
{
    this->text_color = c;
}

void MultiLayerSelector::setHoverColor(QColor c)
{
    this->hover_color = c;
}

void MultiLayerSelector::setPressColor(QColor c)
{
    this->press_color = c;
}

void MultiLayerSelector::initView()
{
    if (m_data_root == nullptr)
    {
        qWarning() << "root data is null";
        return;
    }

    // 初始化最外面一层
    setSubItem(0, m_data_root);
}

/**
 * @brief MultiLayerSelector::setSubItem
 * @param level  层级，从0开始
 * @param parent 父节点，然后获取其子节点，并设置对应的列表
 */
void MultiLayerSelector::setSubItem(int level, LayerItemInfo *parent)
{
    MULTI_LAYER_SELECTOR_DEBUG << "setSubItem level:" << level << "title:" << parent->title();
    if (level < 0 || parent == nullptr)
    {
        qWarning() << "level out of range or parent is null";
        return;
    }

    if (!parent->hasSubItems())
    {
        return;
    }

    // 如果数量不够，则生成一个新的widget
    if (m_list_widgets.size() <= level)
    {
        QListWidget *list_widget = new QListWidget(this);
        list_widget->setStyleSheet("QListWidget{border:1px solid #000000;}");
        m_list_widgets.append(list_widget);
        m_main_hlayout->addWidget(list_widget);

        // list_widget->setStyleSheet("QListWidget::item:selected { background-color: transparent; }");
    }

    // 清空已有的item及其widget
    QListWidget *list_widget = m_list_widgets.at(level);
    if (list_widget->count() > 0)
    {
        for (int i = 0; i < list_widget->count(); i++)
        {
            QListWidgetItem *item = list_widget->item(i);
            QWidget *widget = list_widget->itemWidget(item);
            widget->deleteLater();
            // delete item;
        }
        list_widget->clear();
    }

    // 加载新的item
    for (int i = 0; i < parent->subItems().size(); i++)
    {
        LayerItemInfo *sub_item = parent->itemAt(i);
        QListWidgetItem *item = new QListWidgetItem(list_widget);
        InteractiveButtonBase *button = new InteractiveButtonBase(sub_item->title(), list_widget);
        button->setMouseTracking(true);
        
        // 设置样式
        button->setPaddings(text_padding);
        button->setTextColor(text_color);
        button->setHoverColor(hover_color);
        button->setPressColor(press_color);
        list_widget->setItemWidget(item, button);
        item->setSizeHint(button->size());

        // 控件的事件
        connect(button, &InteractiveButtonBase::signalMouseEnter, this, [=]()
                { setLayerCurrentIndex(level, i); });
        connect(button, &InteractiveButtonBase::clicked, this, [=]()
                {
                    // 切换到这个index，用来适配不支持鼠标移动的情况
                    setLayerCurrentIndex(level, i);

                    // 发送信号
                    emitItemClicked(sub_item, level, i); });
    }
    list_widget->setCurrentRow(parent->currentValidIndex());

    // 加载下一级
    if (parent->currentValidSubItem()->hasSubItems())
    {
        MULTI_LAYER_SELECTOR_DEBUG << "setSubItem next level:" << level + 1 << "title:" << parent->currentValidSubItem()->title();
        setSubItem(level + 1, parent->currentValidSubItem());
    }
}

void MultiLayerSelector::clearView()
{
    MULTI_LAYER_SELECTOR_DEBUG << "clearView";
    for (int i = 0; i < m_list_widgets.size(); i++)
    {
        m_list_widgets.at(i)->deleteLater();
    }
    m_list_widgets.clear();
}

/**
 * 设置当前指定层级的列表到第几个，然后影响下一层的内容
 * @param level 对应第 level 个 listwidget
 */
void MultiLayerSelector::setLayerCurrentIndex(int level, int index)
{
    MULTI_LAYER_SELECTOR_DEBUG << "setLayerCurrentIndex level:" << level << "index:" << index;
    if (level < 0 || level >= m_list_widgets.size())
    {
        qWarning() << "level out of range";
        return;
    }
    
    QListWidget *list_widget = m_list_widgets.at(level);
    if (index < 0 || index >= list_widget->count())
    {
        qWarning() << "index out of range";
        return;
    }

    // 修改 parent 的 index
    list_widget->setCurrentRow(index);

    LayerItemInfo *data = getLayerItem(0, m_data_root, level, -1);
    if (data->currentIndex() == index)
    {
        return;
    }
    data->setCurrentIndex(index);

    // 设置下一级的数据
    setSubItem(level + 1, data->currentSubItem());
}

/**
 * 递归获取指定的层级的数据
 */
LayerItemInfo *MultiLayerSelector::getLayerItem(int current_level, LayerItemInfo *data, int level, int index)
{
    // MULTI_LAYER_SELECTOR_DEBUG << "getLayerItem current_level:" << current_level << "title:" << data->title();
    if (level < 0 || level >= m_list_widgets.size())
    {
        qWarning() << "level out of range";
        return nullptr;
    }

    if (current_level == level)
    {
        if (index == -1)
        {
            return data;
        }
        if (index < 0 || index >= data->subItems().size())
        {
            qWarning() << "index out of range";
            return nullptr;
        }
        return data;
    }
    return getLayerItem(current_level + 1, data->currentSubItem(), level, index);
}

void MultiLayerSelector::emitItemClicked(LayerItemInfo *sub_item, int level, int i)
{
    MULTI_LAYER_SELECTOR_DEBUG << "emitItemClicked level:" << level << "index:" << i << "title:" << sub_item->title();
    emit signalItemClicked(sub_item->data());

    if (sub_item->hasSubItems())
    {
        emit signalGroupClicked(sub_item->data());
    }
    else
    {
        emit signalItemClicked(sub_item->data());
    }

    // 发送路径
    QList<QVariant> path_data;
    QList<int> path_index;
    LayerItemInfo *current_item = sub_item;
    while (current_item != nullptr)
    {
        path_data.prepend(current_item->data());
        path_index.prepend(current_item->currentIndex());
        current_item = current_item->parent();
    }
    if (path_data.size() > 0)
    {
        // 去掉root的data，因为这是固定的，不需要作为变量
        path_data.removeFirst();
        path_index.removeLast();
    }
    emit signalPathDataClicked(path_data);
    emit signalPathIndexClicked(path_index);
}
