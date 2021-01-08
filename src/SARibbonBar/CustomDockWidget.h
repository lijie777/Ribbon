#pragma once

#include <QObject>
#include <QDockWidget>
#include "SARibbonGlobal.h"

class SA_RIBBON_EXPORT CustomDockWidget : public QDockWidget
{
	Q_OBJECT
public:
	CustomDockWidget(QWidget * parent = 0, Qt::WindowFlags flags = 0) :QDockWidget(parent, flags) {}
	CustomDockWidget(const QString & title, QWidget * parent = 0, Qt::WindowFlags flags = 0)
		: QDockWidget(title, parent, flags) {}


};