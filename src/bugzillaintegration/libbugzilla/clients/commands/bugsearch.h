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

#ifndef BUGSEARCH_H
#define BUGSEARCH_H

#include "querycommand.h"

namespace Bugzilla {

class BugSearch : public QueryCommand
{
    Q_OBJECT
    BUGZILLA_MEMBER_PROPERTY(QStringList, products);
    BUGZILLA_MEMBER_PROPERTY(QString, severity);
    BUGZILLA_MEMBER_PROPERTY(QString, creationTime);
    BUGZILLA_MEMBER_PROPERTY(qint64, id) = -1;
    BUGZILLA_MEMBER_PROPERTY(qint64, limit) = -1;
    BUGZILLA_MEMBER_PROPERTY(qint64, offset) = -1;
    BUGZILLA_MEMBER_PROPERTY(QString, longdesc);
    BUGZILLA_MEMBER_PROPERTY(QStringList, order);
public:
    virtual QUrlQuery toQuery() const override;
};

} // namespace Bugzilla

#endif // BUGSEARCH_H