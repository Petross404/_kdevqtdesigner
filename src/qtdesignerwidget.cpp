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

#include "qtdesignerwidget.h"

// plugin
#include "qtdesignerplugin.h"
#include "qtdesignerdocument.h"
// Qt
#include <QMdiSubWindow>
#include <QDesignerFormEditorInterface>
#include <QDesignerFormWindowInterface>
#include <QDesignerFormWindowManagerInterface>


QtDesignerWidget::QtDesignerWidget(QWidget* parent, QtDesignerDocument* document)
    : QMdiArea(parent)
    , m_document(document)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    auto formWindowManager = m_document->plugin()->designerFormEditor()->formWindowManager();
    m_formWindow = formWindowManager->createFormWindow();
    auto buffer = m_document->buffer();
    buffer->open(QIODevice::ReadOnly | QIODevice::Text);
    m_formWindow->setContents(buffer);
    formWindowManager->setActiveFormWindow(m_formWindow);

    const Qt::WindowFlags windowFlags(Qt::Window | Qt::WindowShadeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    auto subWindow = addSubWindow(m_formWindow, windowFlags);
    subWindow->setWindowTitle(m_formWindow->mainContainer()->windowTitle());
}

QtDesignerWidget::~QtDesignerWidget() = default;
