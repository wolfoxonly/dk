#include "Dealtokenunits.h"

#include <QStringList>

DealtokenUnits::DealtokenUnits(QObject *parent):
        QAbstractListModel(parent),
        unitlist(availableUnits())
{
}

QList<DealtokenUnits::Unit> DealtokenUnits::availableUnits()
{
    QList<DealtokenUnits::Unit> unitlist;
    unitlist.append(BTC);
    unitlist.append(mBTC);
    unitlist.append(uBTC);
    return unitlist;
}

bool DealtokenUnits::valid(int unit)
{
    switch(unit)
    {
    case BTC:
    case mBTC:
    case uBTC:
        return true;
    default:
        return false;
    }
}

QString DealtokenUnits::name(int unit)
{
    switch(unit)
    {
    case BTC: return QString("DK");//coingo.vip定义名字
    case mBTC: return QString("mDK");
    case uBTC: return QString::fromUtf8("μDK");
    default: return QString("???");
    }
}

QString DealtokenUnits::description(int unit)
{
    switch(unit)
    {
    case BTC: return QString("Dealtokens");
    case mBTC: return QString("Milli-Dealtokens (1 / 1,000)");
    case uBTC: return QString("Micro-Dealtokens (1 / 1,000,000)");
    default: return QString("???");
    }
}

qint64 DealtokenUnits::factor(int unit)
{
    switch(unit)
    {
    case BTC:  return 1000000;
    case mBTC: return 1000;
    case uBTC: return 1;
    default:   return 1000000;
    }
}

int DealtokenUnits::amountDigits(int unit)
{
    switch(unit)
    {
    case BTC: return 10; // 21,000,000 (# digits, without commas)
    case mBTC: return 13; // 21,000,000,000
    case uBTC: return 16; // 21,000,000,000,000
    default: return 0;
    }
}

int DealtokenUnits::decimals(int unit)
{
    switch(unit)
    {
    case BTC: return 6;
    case mBTC: return 3;
    case uBTC: return 0;
    default: return 0;
    }
}

QString DealtokenUnits::format(int unit, qint64 n, bool fPlus, bool trimzeros)
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    if(!valid(unit))
        return QString(); // Refuse to format invalid unit
    qint64 coin = factor(unit);
    int num_decimals = decimals(unit);
    qint64 n_abs = (n > 0 ? n : -n);
    qint64 quotient = n_abs / coin;
    qint64 remainder = n_abs % coin;
    QString quotient_str = QString::number(quotient);
    QString remainder_str = QString::number(remainder).rightJustified(num_decimals, '0');

    if (trimzeros)
    {
        // Right-trim excess zeros after the decimal point
        int nTrim = 0;
        for (int i = remainder_str.size()-1; i>=2 && (remainder_str.at(i) == '0'); --i)
            ++nTrim;
        remainder_str.chop(nTrim);
    }

    if (n < 0)
        quotient_str.insert(0, '-');
    else if (fPlus && n > 0)
        quotient_str.insert(0, '+');
    return quotient_str + QString(".") + remainder_str;
}

QString DealtokenUnits::formatWithUnit(int unit, qint64 amount, bool plussign, bool trimzeros)
{
    return format(unit, amount, plussign, trimzeros) + QString(" ") + name(unit);
}

bool DealtokenUnits::parse(int unit, const QString &value, qint64 *val_out)
{
    if(!valid(unit) || value.isEmpty())
        return false; // Refuse to parse invalid unit or empty string
    int num_decimals = decimals(unit);
    QStringList parts = value.split(".");

    if(parts.size() > 2)
    {
        return false; // More than one dot
    }
    QString whole = parts[0];
    QString decimals;

    if(parts.size() > 1)
    {
        decimals = parts[1];
    }
    if(decimals.size() > num_decimals)
    {
        return false; // Exceeds max precision
    }
    bool ok = false;
    QString str = whole + decimals.leftJustified(num_decimals, '0');

    if(str.size() > 18)
    {
        return false; // Longer numbers will exceed 63 bits
    }
    qint64 retvalue = str.toLongLong(&ok);
    if(val_out)
    {
        *val_out = retvalue;
    }
    return ok;
}

int DealtokenUnits::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return unitlist.size();
}

QVariant DealtokenUnits::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row >= 0 && row < unitlist.size())
    {
        Unit unit = unitlist.at(row);
        switch(role)
        {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return QVariant(name(unit));
        case Qt::ToolTipRole:
            return QVariant(description(unit));
        case UnitRole:
            return QVariant(static_cast<int>(unit));
        }
    }
    return QVariant();
}
