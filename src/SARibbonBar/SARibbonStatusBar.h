#pragma once

#include <QObject>
#include <QStatusBar>

#include "SARibbonGlobal.h"

class SA_RIBBON_EXPORT SARibbonStatusBar : public QStatusBar
{
	Q_OBJECT
public:
	SARibbonStatusBar(QWidget * parent = 0);

};