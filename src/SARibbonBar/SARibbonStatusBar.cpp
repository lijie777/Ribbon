#include "SARibbonStatusBar.h"
#include <QLabel>
#include <QProgressBar>

SARibbonStatusBar::SARibbonStatusBar(QWidget * parent /*= 0*/) :QStatusBar(parent)
{
	QLabel *label = new QLabel(tr("×´Ì¬À¸1"));
	addWidget(label,2);

	label = new QLabel(tr("×´Ì¬À¸2"));
	addWidget(label,2);
	label = new QLabel(tr("×´Ì¬À¸3"));
	addWidget(label,2);
	QProgressBar *progress = new QProgressBar(this);
	progress->setValue(50);

	addWidget(progress,6);
}
