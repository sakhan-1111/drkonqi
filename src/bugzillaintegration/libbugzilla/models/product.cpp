/*
    Copyright 2019 Harald Sitter <sitter@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "product.h"

#include <QDebug>

#include <QMetaObject>
#include <QMetaMethod>
#include <QMetaType>

namespace Bugzilla {

Product::Product(const QVariantHash &object, const Connection &connection, QObject *parent)
    : QObject(parent)
    , m_connection(connection)
{
    registerVariantConverters();

    for (auto it = object.constBegin(); it != object.constEnd(); ++it) {
        setProperty(qPrintable(it.key()), it.value());
    }
}

QList<ProductVersion *> Product::versions() const
{
    return m_versions;
}

void Product::setVersions(const QList<ProductVersion *> &versions)
{
    m_versions = versions;
}

QList<ProductComponent *> Product::components() const
{
    return m_components;
}

void Product::setComponents(const QList<ProductComponent *> &components)
{
    m_components = components;
}

Product::~Product()
{
    qDeleteAll(m_components);
    qDeleteAll(m_versions);
}

bool Product::isActive() const
{
    return m_active;
}

QStringList Product::componentNames() const
{
    QStringList ret;
    for (const auto *component : m_components) {
        ret << component->name();
    }
    return ret;
}

QStringList Product::allVersions() const
{
    QStringList ret;
    for (const auto *version : m_versions) {
        ret << version->name();
    }
    return ret;
}

QStringList Product::inactiveVersions() const
{
    QStringList ret;
    for (const auto *version : m_versions) {
        if (!version->isActive()) {
            ret << version->name();
        }
    }
    return ret;
}

void Product::registerVariantConverters()
{
    // The way List QVariant get converted to QList<T> is a bit meh.
    // A List variant by default only can convert to a QStringList, regardless
    // of the T itself being a metatype known to QVariant. i.e. the QVariant
    // may know how to iterate a QList, and it may know how to convert T, but
    // it doesn't know how to put the two together into a list conversion.
    // This is true for all Ts. You can have a QList<int>, QVariant::fromValue
    // that into a QVariant{QVariantList} but that variant will no longer
    // convert<QList<int>>.
    // To bridge the conversion gap we need to register custom converters which
    // iterate the variant list and turn it into the relevant type.

    static bool convertersRegistered = false;
    if (convertersRegistered) {
        return;
    }
    convertersRegistered = true;

    QMetaType::registerConverter<QVariantList, QList<ProductComponent *>>(
                [](QVariantList v) -> QList<ProductComponent *>
    {
        QList<ProductComponent *> list;
        list.reserve(v.size());
        for (const QVariant &variant : qAsConst(v)) {
            list.append(new ProductComponent(variant.toHash()));
        }
        return list;
    });

    QMetaType::registerConverter<QVariantList, QList<ProductVersion *>>(
                [](QVariantList v) -> QList<ProductVersion *>
    {
        QList<ProductVersion *> list;
        list.reserve(v.size());
        for (const QVariant &variant : qAsConst(v)) {
            list.append(new ProductVersion(variant.toHash()));
        }
        return list;
    });
}

void Product::setActive(bool active)
{
    m_active = active;
}

ProductVersion::ProductVersion(const QVariantHash &object, QObject *parent)
    : QObject(parent)
{
    for (auto it = object.constBegin(); it != object.constEnd(); ++it) {
        setProperty(qPrintable(it.key()), it.value());
    }
}

ProductComponent::ProductComponent(const QVariantHash &object, QObject *parent)
    : QObject(parent)
{
    for (auto it = object.constBegin(); it != object.constEnd(); ++it) {
        setProperty(qPrintable(it.key()), it.value());
    }
}

} // namespace Bugzilla