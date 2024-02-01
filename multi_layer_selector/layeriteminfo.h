#ifndef LAYERITEMINFO_H
#define LAYERITEMINFO_H

#include <QString>
#include <QVariant>
#include <QList>

struct LayerItemInfo
{
public:
    LayerItemInfo(const QString& title, const QVariant& data = QVariant())
        : m_title(title), m_data(data)
    {}

    void setTitle(const QString& title)
    {
        m_title = title;
    }

    void setData(const QVariant& data)
    {
        m_data = data;
    }

    void setSubItems(QList<LayerItemInfo*> items)
    {
        m_sub_items = items;
    }

    void addSubItem(LayerItemInfo* item)
    {
        m_sub_items.append(item);
    }

    void clearSubItem()
    {
        m_sub_items.clear();
    }

    void setCurrentIndex(int index)
    {
        m_current_index = index;
    }

    QString title() const
    {
        return m_title;
    }

    QVariant data() const
    {
        return m_data;
    }

    int currentIndex() const
    {
        return m_current_index;
    }
    
    QList<LayerItemInfo*> subItems() const
    {
        return m_sub_items;
    }

    LayerItemInfo* itemAt(int index) const
    {
        return m_sub_items.at(index);
    }
    
    LayerItemInfo* currentSubItem() const
    {
        if (m_current_index < 0 || m_current_index >= m_sub_items.size())
            return nullptr;
        return m_sub_items.at(m_current_index);
    }
    
    bool isLeaf() const
    {
        return m_sub_items.size() == 0;
    }

private:
    QString m_title;
    QVariant m_data;
    QList<LayerItemInfo*> m_sub_items;
    int m_current_index = -1;
};

#endif // LAYERITEMINFO_H
