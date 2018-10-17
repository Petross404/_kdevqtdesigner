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

#include "qtdesignerdocument.h"

// plugin
#include "qtdesignerplugin.h"
#include "qtdesignerview.h"
#include <debug.h>
// KDevPlatform
#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>
#include <sublime/controller.h>
// KF
#include <KTextEditor/Cursor>
// Qt
#include <QDesignerFormEditorInterface>
#include <QDesignerFormWindowManagerInterface>
#include <QMimeDatabase>
#include <QFile>
#include <QBuffer>


QtDesignerDocument::QtDesignerDocument(const QUrl& url, KDevelop::ICore* core, QtDesignerPlugin* plugin)
    : Sublime::UrlDocument(core->uiController()->controller(), url)
    , KDevelop::IDocument(core)
    , m_plugin(plugin)
{
}

QtDesignerDocument::~QtDesignerDocument() = default;

QMimeType QtDesignerDocument::mimeType() const
{
    return QMimeDatabase().mimeTypeForName(QStringLiteral("application/x-designer"));
}

KParts::Part* QtDesignerDocument::partForView(QWidget*) const
{
    return nullptr;
}

KDevelop::IDocument::DocumentState QtDesignerDocument::state() const
{
    return IDocument::Clean;
}

KTextEditor::Document* QtDesignerDocument::textDocument() const
{
    return nullptr;
}

KTextEditor::Cursor QtDesignerDocument::cursorPosition() const
{
    return KTextEditor::Cursor();
}

bool QtDesignerDocument::isActive() const
{
    // TODO
    return false;
}

QUrl QtDesignerDocument::url() const
{
    return Sublime::UrlDocument::url();
}

void QtDesignerDocument::reload()
{
    // TODO

    notifyStateChanged();
}

void QtDesignerDocument::activate(Sublime::View* view, KParts::MainWindow* mainWindow)
{
    Q_UNUSED(mainWindow);
    Q_UNUSED(view);

    // TODO

    notifyActivated();
}


bool QtDesignerDocument::close(KDevelop::IDocument::DocumentSaveMode mode)
{
    Q_UNUSED(mode);

    // TODO

    // The document is deleted automatically when there are no views left

    return true;
}

bool QtDesignerDocument::save(KDevelop::IDocument::DocumentSaveMode mode)
{
    if (mode & Discard) {
        return true;
    }

    if (!m_buffer) {
        return false;
    }

    if (state() == IDocument::Clean) {
        return false;
    }

    // TODO: ensure buffer is up-to-date from view

    const auto filePath = url().toLocalFile();
    QFile uiFile(filePath);
    if (!uiFile.open(QIODevice::WriteOnly)) {
        qCDebug(KDEVQTDESIGNER) << "Couldn't open file:" << uiFile.error();
        return false;
    }
    uiFile.write(m_buffer->data());
    uiFile.close();

    notifySaved();
    notifyStateChanged();

    return true;
}



void QtDesignerDocument::setCursorPosition(const KTextEditor::Cursor&)
{
}

void QtDesignerDocument::setTextSelection(const KTextEditor::Range&)
{
}

Sublime::View* QtDesignerDocument::newView(Sublime::Document* document)
{
    auto designerDocument = qobject_cast<QtDesignerDocument*>(document);
    if (!designerDocument) {
        return nullptr;
    }

    if (!m_buffer) {
        const auto filePath = url().toLocalFile();
        QFile uiFile(filePath);
        uiFile.open(QIODevice::ReadOnly);

        m_buffer = new QBuffer(this);
        m_buffer->setData(uiFile.readAll());
    }    

    return new QtDesignerView(this);
}

QtDesignerPlugin* QtDesignerDocument::plugin() const
{
    return m_plugin;
}

QIODevice* QtDesignerDocument::buffer() const
{
    Q_ASSERT(m_buffer);
    return m_buffer;
}
