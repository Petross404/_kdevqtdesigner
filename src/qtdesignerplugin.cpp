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

#include "qtdesignerplugin.h"

// plugin
#include "qtdesignerdocumentfactory.h"
#include <debug.h>
// KDev
#include <interfaces/idocumentcontroller.h>
// KF
#include <KPluginFactory>
// Qt
#include <QDesignerComponents>
#include <QDesignerIntegration>
#include <QDesignerFormEditorInterface>


K_PLUGIN_FACTORY_WITH_JSON(kdevqtdesignerFactory, "qtdesigner.json",
                           registerPlugin<QtDesignerPlugin>(); )


QtDesignerPlugin::QtDesignerPlugin(QObject *parent, const QVariantList& args)
    : KDevelop::IPlugin(QStringLiteral("kdevqtdesigner"), parent)
    , m_documentFactory(new QtDesignerDocumentFactory(this))
{
    Q_UNUSED(args);

    // Cmp. qt creator https://code.woboq.org/qt5/qt-creator/src/plugins/designer/formeditorw.cpp.html#_ZN8Designer8Internal14FormEditorData8fullInitEv
    auto formeditor = QDesignerComponents::createFormEditor(this);
    QDesignerComponents::initializePlugins(formeditor);
    QDesignerComponents::initializeResources();

    m_designerIntegration.reset(new QDesignerIntegration(formeditor, this));
    formeditor->setIntegration(m_designerIntegration.data());

    core()->documentController()->registerDocumentForMimetype(QStringLiteral("application/x-designer"), m_documentFactory.data());
}

QtDesignerPlugin::~QtDesignerPlugin() = default;

QDesignerFormEditorInterface* QtDesignerPlugin::designerFormEditor() const
{
    return m_designerIntegration->core();
}

// needed for QObject class created from K_PLUGIN_FACTORY_WITH_JSON
#include "qtdesignerplugin.moc"
