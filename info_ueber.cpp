#include "info_ueber.h"

Info_Ueber::Info_Ueber(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant Info_Ueber::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex Info_Ueber::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex Info_Ueber::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int Info_Ueber::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int Info_Ueber::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant Info_Ueber::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
