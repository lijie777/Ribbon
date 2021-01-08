#include "SARibbonMainWindow.h"
#include "FramelessHelper.h"
#include "SAWindowButtonGroup.h"
#include "SARibbonBar.h"
#include "SARibbonStatusBar.h"
#include <QApplication>
#include <QDebug>
#include <QHash>
#include <QFile>
#include <QPropertyAnimation>
#include <QKeyEvent>

class SARibbonMainWindowPrivate
{
public:
    SARibbonMainWindowPrivate(SARibbonMainWindow *p);
    void init();

    SARibbonMainWindow *Parent; ///< 父窗口mainwindow
    SARibbonBar *ribbonBar;  ///< 菜单栏
    SARibbonMainWindow::RibbonTheme currentRibbonTheme;  ///< 主题
    SAWindowButtonGroup *windowButtonGroup; ///< 关闭，最小化，最大化等按钮组
	bool useRibbon;
	
#if 0
    QHash<SARibbonMainWindow::RibbonElement, QString> ribbonStyleSheet;
#endif
};

SARibbonMainWindowPrivate::SARibbonMainWindowPrivate(SARibbonMainWindow *p)
    : Parent(p)
	, ribbonBar(nullptr)
    , currentRibbonTheme(SARibbonMainWindow::NormalTheme)
	, windowButtonGroup(nullptr)
	, useRibbon(true)
{
}


void SARibbonMainWindowPrivate::init()
{
}


SARibbonMainWindow::SARibbonMainWindow(QWidget *parent,bool useRibbon)
    : QMainWindow(parent)
    , m_d(new SARibbonMainWindowPrivate(this))
{
    m_d->init();
	m_d->useRibbon = useRibbon;
	//启动画面
	splashAnimation();
	//窗体状态栏
	SARibbonStatusBar *statusBar = new SARibbonStatusBar(this);
	this->setStatusBar(statusBar);

	if (useRibbon)
	{
		setRibbonTheme(ribbonTheme());
		//窗体菜单栏
		m_d->ribbonBar = new SARibbonBar(this);
		setMenuWidget(m_d->ribbonBar);
		m_d->ribbonBar->installEventFilter(this);
		//窗体最大化最小化关闭按钮
		m_d->windowButtonGroup = new SAWindowButtonGroup(this);
		//窗体标题栏
		FramelessHelper *pHelper = new FramelessHelper(this);
		pHelper->setTitleHeight(m_d->ribbonBar->titleBarHeight()); //设置窗体的标题栏高度
	}

}


const SARibbonBar *SARibbonMainWindow::ribbonBar() const
{
    return (m_d->ribbonBar);
}


SARibbonBar *SARibbonMainWindow::ribbonBar()
{
    return (m_d->ribbonBar);
}


void SARibbonMainWindow::setRibbonTheme(SARibbonMainWindow::RibbonTheme theme)
{
    switch (theme)
    {
    case NormalTheme:
        loadTheme(":/theme/resource/default.qss");
        break;

    default:
        loadTheme(":/theme/resource/default.qss");
        break;
    }
}


SARibbonMainWindow::RibbonTheme SARibbonMainWindow::ribbonTheme() const
{
    return (m_d->currentRibbonTheme);
}


bool SARibbonMainWindow::isUseRibbon() const
{
	return m_d->useRibbon;
}

void SARibbonMainWindow::hideTab()
{

}

void SARibbonMainWindow::splashAnimation()
{
	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(1000);
	animation->setStartValue(0);
	animation->setEndValue(1);
	animation->setEasingCurve(QEasingCurve::Linear);//渐变时间曲线
	animation->start();
}

void SARibbonMainWindow::resizeEvent(QResizeEvent *event)
{
    if (m_d->ribbonBar) {
        if (m_d->ribbonBar->size().width() != this->size().width()) {
            m_d->ribbonBar->setFixedWidth(this->size().width());
        }
    }
    QMainWindow::resizeEvent(event);
}


bool SARibbonMainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == m_d->ribbonBar) {
        switch (e->type())
        {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseMove:
        case QEvent::Leave:
        case QEvent::HoverMove:
        case QEvent::MouseButtonDblClick:
            QApplication::sendEvent(this, e);

        default:
            break;
        }
    }
    return (QMainWindow::eventFilter(obj, e));
}


void SARibbonMainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape && menuBar()->isHidden())
	{
		menuBar()->setHidden(false);
	}
}

void SARibbonMainWindow::loadTheme(const QString& themeFile)
{
    QFile file(themeFile);

    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
        return;
    }
    setStyleSheet(file.readAll());
}
