#include "SAWindowButtonGroup.h"
#include <QToolButton>
#include <QResizeEvent>
#include <QStyle>
#include <QDebug>
#include <QPropertyAnimation>
#include <QString>
#include "SARibbonLineEdit.h"
#include "SARibbonMenu.h"
#include "SARibbonLabel.h"

//为了避免使用此框架的app设置了全局的qpushbutton 的 qss样式影响此按钮，定义了一个类

class SARibbonLineEdit;
class SARibbonMenu;
class SAWindowButtonGroupPrivate
{
public:

    SAWindowToolButton *buttonClose;
    SAWindowToolButton *buttonMinimize;
    SAWindowToolButton *buttonMaximize;
	SARibbonLineEdit *searchLne;
	SARibbonLabel *infoLabel;
	SARibbonMenu *skinMenu;
    SAWindowButtonGroupPrivate()
        : buttonClose(nullptr)
        , buttonMinimize(nullptr)
        , buttonMaximize(nullptr)
		, skinMenu(nullptr)
		, searchLne(nullptr)
		, infoLabel(nullptr)
    {
    }

	void setupSkinMenu(SAWindowButtonGroup *par, bool on, qreal iconscale = 0.5)
	{
		if (on) {
			if (!skinMenu) {
				skinMenu = new SARibbonMenu("skin", par);				
				skinMenu->setFixedSize(40, 28);				
				auto *act = new QAction(par);
				auto styleActionGroup = new QActionGroup(skinMenu);
				styleActionGroup->addAction(skinMenu->addAction(("blue"), [&]()
				{
					//setColor("rgb(43, 87, 154)");
				}));
				styleActionGroup->addAction(skinMenu->addAction(("green"), [&]()
				{
					//setColor("rgb(43, 87, 154)");
				}));
				styleActionGroup->addAction(skinMenu->addAction(("red"), [&]()
				{
					//setColor("rgb(183, 71, 42)");
				}));
			}
		}
		else {
			if (skinMenu) {
				delete skinMenu;
			}
		}
		updateSize(par);
	}

	void setupInfoLabel(SAWindowButtonGroup *par, bool on, qreal iconscale = 0.5)
	{
		if (on) {
			if (!infoLabel) {
				infoLabel = new SARibbonLabel(par);
				infoLabel->setText("custom info");
				infoLabel->setFixedSize(50, 28);				
			}
		}
		else {
			if (infoLabel) {
				delete infoLabel;
			}
		}
		updateSize(par);
	}

	void setupSearchLne(SAWindowButtonGroup *par, bool on, qreal iconscale = 0.5)
	{
		if (on) {
			if (!searchLne) {
				searchLne = new SARibbonLineEdit(par);
				searchLne->setPlaceholderText("search info");
				searchLne->setFixedSize(50, 28);
			}
		}
		else {
			if (searchLne) {
				delete searchLne;
			}
		}
		updateSize(par);
	}



    void setupMinimizeButton(SAWindowButtonGroup *par, bool on, qreal iconscale = 0.5)
    {
        if (on) {
            if (!buttonMinimize) {
                buttonMinimize = new SAWindowToolButton(par);
                buttonMinimize->setObjectName(QStringLiteral("SAMinimizeWindowButton"));
                buttonMinimize->setFixedSize(30, 28);
                buttonMinimize->setFocusPolicy(Qt::NoFocus);//避免铺抓到
                buttonMinimize->setStyleSheet(QString(""
                    "SAWindowToolButton"
                    "{ "
                    "    background-color: transparent; "
                    "    border:none;"
                    "}"
                    "SAWindowToolButton:hover {background-color:#C1D1B8;}"
                    "SAWindowToolButton:pressed {background-color:#A5AF9B;}"
                    "SAWindowToolButton:focus{outline: none}"));
                QIcon icon = par->style()->standardIcon(QStyle::SP_TitleBarMinButton);
                buttonMinimize->setIconSize(buttonMinimize->size()*iconscale);
                buttonMinimize->setIcon(icon);
                par->connect(buttonMinimize, &QAbstractButton::clicked
                    , par, &SAWindowButtonGroup::minimizeWindow);
            }
        }else {
            if (buttonMinimize) {
                delete buttonMinimize;
            }
        }
        updateSize(par);
    }


    void setupMaximizeButton(SAWindowButtonGroup *par, bool on, qreal iconscale = 0.5)
    {
        if (on) {
            if (!buttonMaximize) {
                buttonMaximize = new SAWindowToolButton(par);
                buttonMaximize->setObjectName(QStringLiteral("SAMaximizeWindowButton"));
                buttonMaximize->setFixedSize(30, 28);
                buttonMaximize->setFocusPolicy(Qt::NoFocus);//避免铺抓到
                buttonMaximize->setStyleSheet(QString(""
                    "SAWindowToolButton"
                    "{ "
                    "    background-color: transparent; "
                    "    border:none;"
                    "}\n"
                    "SAWindowToolButton:hover {background-color:#C1D1B8;}"
                    "SAWindowToolButton:pressed {background-color:#A5AF9B;}"
                    "SAWindowToolButton:focus{outline: none;}"));
                QIcon icon = par->style()->standardIcon(QStyle::SP_TitleBarMaxButton);
                buttonMaximize->setIconSize(buttonMaximize->size()*iconscale);
                buttonMaximize->setIcon(icon);
                par->connect(buttonMaximize, &QAbstractButton::clicked
                    , par, &SAWindowButtonGroup::maximizeWindow);
            }
        }else {
            if (buttonMaximize) {
                delete buttonMaximize;
            }
        }
        updateSize(par);
    }


    void setupCloseButton(SAWindowButtonGroup *par, bool on, qreal iconscale = 0.5)
    {
        if (on) {
            if (!buttonClose) {
                buttonClose = new SAWindowToolButton(par);
                buttonClose->setObjectName(QStringLiteral("SACloseWindowButton"));
                buttonClose->setFixedSize(40, 28);
                buttonClose->setFocusPolicy(Qt::NoFocus);//避免铺抓到
                //buttonClose->setFlat(true);
                par->connect(buttonClose, &QAbstractButton::clicked
                    , par, &SAWindowButtonGroup::closeWindow);
                buttonClose->setStyleSheet(QString(""
                    "SAWindowToolButton"
                    "{ "
                    "    background-color: transparent; "
                    "    border:none;"
                    "}"
                    "SAWindowToolButton:hover {background-color:#F0604D;}"
                    "SAWindowToolButton:pressed {background-color:#F0604D;}"
                    "SAWindowToolButton:focus{outline: none;}"));
                QIcon icon = par->style()->standardIcon(QStyle::SP_TitleBarCloseButton);
                buttonClose->setIconSize(buttonClose->size()*iconscale);
                buttonClose->setIcon(icon);
            }
        }else {
            if (buttonClose) {
                delete buttonClose;
            }
        }
        updateSize(par);
    }


    void updateSize(SAWindowButtonGroup *par)
    {
        par->setFixedSize(sizeHint());
        int span = 0;
#if 1		
		if (buttonClose) {
			buttonClose->move(par->width() - buttonClose->width()
				, par->y());
			span += buttonClose->width();
		}
		if (buttonMaximize) {
			buttonMaximize->move(par->width() - buttonMaximize->width() - span
				, par->y());
			span += buttonMaximize->width();
		}
		if (buttonMinimize) {
			buttonMinimize->move(par->width() - buttonMinimize->width() - span
				, par->y());
		}
#else
		QRect r = par->rect();
		if (infoLabel) {
			infoLabel->move(par->width() - infoLabel->width()
				, par->y());
			span = infoLabel->width();
		}
		if (skinMenu) {
			skinMenu->move(par->width() - skinMenu->width() - span
				, par->y());
			span += skinMenu->width();
		}
		if (searchLne) {
			searchLne->move(par->width() - searchLne->width() - span
				, par->y());

			span += searchLne->width();
		}

		if (buttonClose) {
			buttonClose->move(par->width() - buttonClose->width() - span
				, par->y());
			span += buttonClose->width();
		}
		if (buttonMaximize) {
			buttonMaximize->move(par->width() - buttonMaximize->width() - span
				, par->y());
			span += buttonMaximize->width();
		}
		if (buttonMinimize) {
			buttonMinimize->move(par->width() - buttonMinimize->width() - span
				, par->y());
		}
#endif
		
    }


    QSize sizeHint() const
    {
        int width = 0;
        int height = 0;
		/*if (infoLabel) {
			width += infoLabel->width();
			height = qMax(height, infoLabel->height());
		}
		if (skinMenu) {
			width += skinMenu->width();
			height = qMax(height, skinMenu->height());
		}
		if (searchLne){
			width += searchLne->width();
			height = qMax(height, searchLne->height());
		}
		*/
		
        if (buttonClose) {
            width += buttonClose->width();
            height = qMax(height, buttonClose->height());
        }
        if (buttonMaximize) {
            width += buttonMaximize->width();
            height = qMax(height, buttonMaximize->height());
        }
        if (buttonMinimize) {
            width += buttonMinimize->width();
            height = qMax(height, buttonMinimize->height());
        }
        return (QSize(width, height));
    }
};

SAWindowToolButton::SAWindowToolButton(QWidget *p):QToolButton(p)
{
    setAutoRaise(true);
}

SAWindowButtonGroup::SAWindowButtonGroup(QWidget *parent, qreal iconscale) : QWidget(parent)
    , m_d(new SAWindowButtonGroupPrivate())
{
    updateWindowFlag(iconscale);
    if (parent) {
        parent->installEventFilter(this);
    }
}


SAWindowButtonGroup::~SAWindowButtonGroup()
{
    delete m_d;
}


void SAWindowButtonGroup::setupMinimizeButton(bool on, qreal iconscale)
{
    m_d->setupMinimizeButton(this, on, iconscale);
}


void SAWindowButtonGroup::setupMaximizeButton(bool on, qreal iconscale)
{
    m_d->setupMaximizeButton(this, on, iconscale);
    updateMaximizeButtonIcon();
}


void SAWindowButtonGroup::setupCloseButton(bool on, qreal iconscale)
{
    m_d->setupCloseButton(this, on, iconscale);
}


void SAWindowButtonGroup::setupSearchLne(bool on, qreal iconscale /*= 0.5*/)
{
	m_d->setupSearchLne(this, on, iconscale);
}

void SAWindowButtonGroup::setupInfoLabel(bool on, qreal iconscale /*= 0.5*/)
{
	m_d->setupInfoLabel(this, on, iconscale);
}

void SAWindowButtonGroup::setupSkinMenu(bool on, qreal iconscale /*= 0.5*/)
{
	m_d->setupSkinMenu(this, on, iconscale);
}

void SAWindowButtonGroup::updateWindowFlag(qreal iconscale)
{
    Qt::WindowFlags flags = parentWidget()->windowFlags();

	/*setupSkinMenu(true, iconscale);
	setupInfoLabel(true, iconscale);
	setupSearchLne(true, iconscale);*/


    setupMinimizeButton(flags & Qt::WindowMinimizeButtonHint, iconscale);
	
    setupMaximizeButton(flags & Qt::WindowMaximizeButtonHint, iconscale);
	
    setupCloseButton(flags & Qt::WindowCloseButtonHint, iconscale);

	
}


QSize SAWindowButtonGroup::sizeHint() const
{
    return (m_d->sizeHint());
}


bool SAWindowButtonGroup::eventFilter(QObject *watched, QEvent *e)
{
    if (watched == parentWidget()) {
        switch (e->type())
        {
        case QEvent::Resize:
            parentResize();
            break;

        default:
            break;
        }
    }
    return (false);
}


void SAWindowButtonGroup::parentResize()
{
    QWidget *par = parentWidget();

    if (par) {
        QSize parSize = par->size();
        move(parSize.width() - width()-1, 1);
    }
}


void SAWindowButtonGroup::updateMaximizeButtonIcon()
{
    QWidget *par = parentWidget();

    if (par) {
        if (par->isMaximized()) {
            if (m_d->buttonMaximize) {
                m_d->buttonMaximize->setIcon(style()->standardIcon(QStyle::SP_TitleBarNormalButton));
            }
        }else {
            if (m_d->buttonMaximize) {
                m_d->buttonMaximize->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
            }
        }
    }
}


void SAWindowButtonGroup::closeMainWindow()
{
	QPropertyAnimation *closeAnimation = new QPropertyAnimation(parentWidget(), "geometry");
	const QRect rect = parentWidget()->geometry();
	closeAnimation->setDuration(300);

	closeAnimation->setStartValue(rect);

	closeAnimation->setEndValue(QRect(rect.x(), rect.y() + parentWidget()->height(), 0, 0));

	closeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
	connect(closeAnimation, &QPropertyAnimation::finished, [this]() {parentWidget()->close(); });
}

void SAWindowButtonGroup::closeWindow()
{
    if (parentWidget()) {
		closeMainWindow();
    }


}


void SAWindowButtonGroup::minimizeWindow()
{
    if (parentWidget()) {
        parentWidget()->showMinimized();
    }
}


void SAWindowButtonGroup::maximizeWindow()
{
    QWidget *par = parentWidget();
	static QRect rect = par->geometry();
    if (par) 
	{
#if 1
		if (par->isMaximized()) 
		{
			par->showNormal();
		}
		else
		{
			par->showMaximized();
		}
#else
        if (par->isMaximized()) 
		{
			QPropertyAnimation *normalAnimation = new QPropertyAnimation(par, "geometry");
			normalAnimation->setDuration(300);
			normalAnimation->setStartValue(par->geometry());
			normalAnimation->setEndValue(par->normalGeometry());
			normalAnimation->start();
			connect(normalAnimation, &QPropertyAnimation::finished, [par]()
			{
				par->showNormal();
			});
			rect = par->geometry();
			
        }
		else
		{
			QPropertyAnimation *maxAnimation = new QPropertyAnimation(par, "geometry");
			maxAnimation->setDuration(300);
			maxAnimation->setStartValue(par->geometry());
			maxAnimation->setEndValue(rect);
			maxAnimation->start();
			connect(maxAnimation, &QPropertyAnimation::finished, [par]()
			{
				par->showMaximized();
			});		
        }
#endif

	}
	updateMaximizeButtonIcon();
}




