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

#ifndef QTDESIGNERDOCUMENT_H
#define QTDESIGNERDOCUMENT_H

// KDevPlatform
#include <sublime/urldocument.h>
#include <interfaces/idocument.h>

class QtDesignerPlugin;
class QBuffer;
class QIODevice;

namespace KDevelop
{
class ICore;
}

class QtDesignerDocument : public Sublime::UrlDocument, public KDevelop::IDocument
{
    Q_OBJECT

public:
    QtDesignerDocument(const QUrl& url, KDevelop::ICore* core, QtDesignerPlugin* plugin);

    ~QtDesignerDocument() override;

public: // KDevelop::IDocument API
    KTextEditor::Cursor cursorPosition() const override;
    bool isActive() const override;
    QMimeType mimeType() const override;
    KParts::Part* partForView(QWidget* widget) const override;
    DocumentState state() const override;
    KTextEditor::Document* textDocument() const override;
    QUrl url() const override;

    void activate(Sublime::View* view, KParts::MainWindow* mainWindow) override;
    bool close(IDocument::DocumentSaveMode = IDocument::Default) override;
    void reload() override;
    bool save(IDocument::DocumentSaveMode = IDocument::Default) override;
    void setCursorPosition(const KTextEditor::Cursor& cursor) override;
    void setTextSelection(const KTextEditor::Range& range) override;

public:
    QtDesignerPlugin* plugin() const;
    // only call after first newView() call
    QIODevice* buffer() const;

protected:
    Sublime::View* newView(Sublime::Document* document) override;

private:
    QtDesignerPlugin* const m_plugin;
    QBuffer* m_buffer = nullptr;
};

#endif // QTDESIGNERDOCUMENT_H
