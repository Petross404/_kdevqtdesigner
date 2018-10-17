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

#include "qtdesignerview.h"

// plugin
#include "qtdesignerdocument.h"
#include "qtdesignerwidget.h"

QtDesignerView::QtDesignerView(QtDesignerDocument* document)
  : Sublime::View(document, View::TakeOwnership)
{
}

QtDesignerView::~QtDesignerView() = default;

QWidget* QtDesignerView::createWidget(QWidget* parent)
{
    auto document = static_cast<QtDesignerDocument*>(this->document());
    return new QtDesignerWidget(parent, document);
}
