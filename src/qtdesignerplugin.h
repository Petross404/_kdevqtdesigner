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

#ifndef KDEVQTDESIGNER_H
#define KDEVQTDESIGNER_H

// KDev
#include <interfaces/iplugin.h>

class QDesignerFormEditorInterface;

class QtDesignerPlugin : public KDevelop::IPlugin
{
    Q_OBJECT

public:
    // KPluginFactory-based plugin wants constructor with this signature
    QtDesignerPlugin(QObject* parent, const QVariantList& args);
    ~QtDesignerPlugin() override;

public:
    QDesignerFormEditorInterface* designerFormEditor() const;

private:
    QScopedPointer<class QtDesignerDocumentFactory> const m_documentFactory;
    QScopedPointer<class QDesignerIntegrationInterface> m_designerIntegration;
};

#endif // KDEVQTDESIGNER_H
