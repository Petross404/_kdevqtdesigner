/*
    This file is part of KDevelop

    Copyright 2018 Friedrich W. H. Kossebau <kossebau@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef QTDESIGNERDOCUMENTFACTORY_H
#define QTDESIGNERDOCUMENTFACTORY_H

// plugin
#include "qtdesignerdocument.h"
// KDev
#include <interfaces/icore.h>
#include <interfaces/idocumentcontroller.h>

class QtDesignerPlugin;


class QtDesignerDocumentFactory : public KDevelop::IDocumentFactory
{
public:
    explicit QtDesignerDocumentFactory(QtDesignerPlugin* plugin);

public: // IDocumentFactory API
    KDevelop::IDocument* create(const QUrl& url, KDevelop::ICore* core) override;

private:
    QtDesignerPlugin* const m_plugin;
};


inline QtDesignerDocumentFactory::QtDesignerDocumentFactory(QtDesignerPlugin* plugin)
    : m_plugin(plugin)
{
}

inline KDevelop::IDocument* QtDesignerDocumentFactory::create(const QUrl& url, KDevelop::ICore* core)
{
    QtDesignerDocument* document = new QtDesignerDocument(url, core, m_plugin);
    return document;
}

#endif
