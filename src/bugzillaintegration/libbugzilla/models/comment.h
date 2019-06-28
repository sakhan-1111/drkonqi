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

#ifndef COMMENT_H
#define COMMENT_H

#include <QObject>
#include <QPointer>

namespace Bugzilla {

class Comment : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int bug_id READ bug_id WRITE setBug_id)
    Q_PROPERTY(QString text READ text WRITE setText)
public:
    typedef QPointer<Comment> Ptr;

    explicit Comment(const QVariantHash &object, QObject *parent = nullptr);

    int bug_id() const;
    void setBug_id(int bug_id);

    QString text() const;
    void setText(const QString &text);

private:
    int m_bug_id;
    QString m_text;
};

} // namespace Bugzilla

#endif // COMMENT_H