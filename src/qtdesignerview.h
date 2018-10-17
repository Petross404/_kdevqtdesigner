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

#ifndef QTDESIGNERVIEW_H
#define QTDESIGNERVIEW_H

// KDev
#include <sublime/view.h>

class QtDesignerDocument;

class QtDesignerView : public Sublime::View
{
    Q_OBJECT

public:
    explicit QtDesignerView(QtDesignerDocument* deocument);
    ~QtDesignerView() override;

public: // Sublime::View API
    QWidget* createWidget(QWidget* parent) override;
};

#endif // QTDESIGNERVIEW_H
