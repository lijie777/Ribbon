#include "UITest.h"
#include <QTextEdit>
#include <QCalendarWidget>
#include <QListWidget>
#include <QStatusBar>
#include <QPushButton>
#include <QTableWidget>

#include "SARibbonBar.h"
#include "SARibbonMenu.h"
#include "CustomDockWidget.h"
#include "SARibbonComboBox.h"
#include "SARibbonCheckBox.h"
#include "SARibbonGalleryGroup.h"
#include "SARibbonGallery.h"
#include "SARibbonQuickAccessBar.h"

UITest::UITest(QWidget* par /*= nullptr*/) :SARibbonMainWindow(par), m_edit(new QTextEdit(this))
{
	setWindowTitle(tr("UI Test"));

	setCentralWidget(m_edit);

	createDockWindows();
	//ribbon�˵���
	SARibbonBar* ribbon = ribbonBar();
	QFont f = ribbon->font();
	f.setFamily("΢���ź�");
	ribbon->setFont(f);
	ribbon->applitionButton()->setText(QStringLiteral("File"));

	SARibbonCategory* categoryMain = ribbon->addCategoryPage(QStringLiteral("HOME"));
	createCategoryMain(categoryMain);

	SARibbonCategory* categoryOther = ribbon->addCategoryPage(QStringLiteral("OTHER"));
	createCategoryOther(categoryOther);

	SARibbonCategory* categoryOther2 = ribbon->addCategoryPage(QStringLiteral("OTHER2"));
	createCategoryOther2(categoryOther2);

	//������Ӧ��
	QAction *act = new QAction(QIcon(":/icon/icon/chartDataManager.png"), "��ݼ�1", this);
	connect(act, &QAction::triggered, this, [this, act]() {m_edit->append(act->text()); });
	ribbon->quickAccessBar()->addButton(act);
	act = new QAction(QIcon(":/icon/icon/figureIcon.png"), "��ݼ�2", this);
	connect(act, &QAction::triggered, this, [this, act]() {m_edit->append(act->text()); });
	ribbon->quickAccessBar()->addButton(act);
	act = new QAction(QIcon(":/icon/icon/information.png"), "��ݼ�3", this);
	connect(act, &QAction::triggered, this, [this, act]() {m_edit->append(act->text()); });
	ribbon->quickAccessBar()->addButton(act);
	act = new QAction(QIcon(":/icon/icon/inRangDataRemove.png"), "��ݼ�4", this);
	connect(act, &QAction::triggered, this, [this, act]() {m_edit->append(act->text()); });
	ribbon->quickAccessBar()->addButton(act);
	
}

void UITest::onDefault()
{
	for each (CustomDockWidget* dockWidget in m_listDockWidget)
	{
		if (dockWidget->isHidden())
		{
			dockWidget->toggleViewAction()->activate(QAction::Trigger);
		}
	}
}

void UITest::onOpen()
{
	m_edit->append(QStringLiteral("open..."));
}

void UITest::createCategoryMain(SARibbonCategory* page)
{
	SARibbonToolButton * btn;
	SARibbonMenu* menu = new SARibbonMenu(this);
	QAction *action1 = new QAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("test action1"), this);
	QAction *action2 = new QAction(QIcon(":/images/icon/image/folder-open.png"), QStringLiteral("test action2"), this);
	QAction *action3 = new QAction(QIcon(":/images/icon/image/save.png"), QStringLiteral("test action3"), this);
	connect(action1, &QAction::triggered, [this, action1]() {m_edit->append(action1->text()); });
	connect(action2, &QAction::triggered, [this, action2]() {m_edit->append(action2->text()); });
	connect(action3, &QAction::triggered, [this, action3]() {m_edit->append(action3->text()); });
	menu->addAction(action1);
	menu->addAction(action2);
	menu->addAction(action3);

	SARibbonPannel* pannel = page->addPannel(QStringLiteral("pannel"));

	//����
	QAction *act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/save.png"));
	act->setText(tr("����"));
	pannel->addLargeAction(act);
	connect(act, &QAction::triggered, this, [this]() {
		this->m_edit->append("action save clicked");
	});

	// ����
	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/chartDataManager.png"));
	act->setText(tr("&����"));
	act->setMenu(viewMenu);
	btn = pannel->addLargeAction(act);
	btn->setObjectName("buttonInstantPopup");
	btn->setPopupMode(QToolButton::InstantPopup);

	// ��
	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/folder.png"));
	act->setText(tr("��"));
	SARibbonMenu* openMenu = new SARibbonMenu(this);
	QAction *actionOpen = new QAction(QIcon(":/icon/icon/folder.png"), tr("��..."), this);
	openMenu->addAction(actionOpen);
	connect(actionOpen, &QAction::triggered, [this, actionOpen]() {m_edit->append(actionOpen->text()); });
	act->setMenu(openMenu);
	btn = pannel->addLargeAction(act);
	btn->setObjectName(tr("��"));
	btn->setPopupMode(QToolButton::MenuButtonPopup);
	connect(act, &QAction::triggered, this, [this, act]() {m_edit->append(act->text()); });

	// �л�����
	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/save.png"));
	act->setText(tr("�л�"));
	act->setCheckable(true);
	pannel->addSmallAction(act);
	connect(act, &QAction::triggered, this, [this, act](bool b) {
		if (b)
			ribbonBar()->setRibbonStyle(SARibbonBar::WpsLiteStyle);
		else
			ribbonBar()->setRibbonStyle(SARibbonBar::OfficeStyle);
		update();

		m_edit->append(act->text() + QString("%1").arg(b? tr("���Ͻ�"): tr("���Ͻ�")));
	});

	// ���԰�ť2
	act = new QAction(this);
	act->setIcon(QIcon(":/images/icon/image/file-text-o.png"));
	act->setText(tr("���԰�ť2"));
	act->setCheckable(true);
	pannel->addSmallAction(act);
	connect(act, &QAction::triggered, this, [this, act]() {
		m_edit->append(act->text());
	});
	// ���԰�ť3
	act = new QAction(this);
	act->setIcon(QIcon(":/images/icon/image/paste.png"));
	act->setText(tr("���԰�ť3"));
	act->setCheckable(true);
	pannel->addSmallAction(act);
	connect(act, &QAction::triggered, this, [this, act]() {
		m_edit->append(act->text());
	});
	// ���԰�ť4
	act = new QAction(this);
	act->setIcon(QIcon(":/images/icon/image/eye.png"));
	act->setText(tr("���԰�ť4"));
	act->setCheckable(true);
	pannel->addSmallAction(act);
	connect(act, &QAction::triggered, this, [this, act]() {
		m_edit->append(act->text());
	});

	// �����˵����ԣ�Qmenu��
	act = new QAction(this);
	act->setIcon(QIcon(":/images/icon/image/save.png"));
	act->setText(tr("���Բ˵���1"));
	act->setMenu(menu);
	btn = pannel->addSmallAction(act);
	btn->setPopupMode(QToolButton::MenuButtonPopup);

	// �����˵����ԣ�Qmenu2��
	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/folder.png"));
	act->setText(tr("���Բ˵���2"));
	act->setMenu(menu);
	btn = pannel->addSmallAction(act);
	btn->setPopupMode(QToolButton::InstantPopup);

	// ����combox1
	SARibbonComboBox * com = new SARibbonComboBox(this);
	com->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	for (int i = 0; i < 20; ++i)
	{
		com->addItem(QString("ComboBox test1 %1").arg(i));
	}
	connect(com, &QComboBox::currentTextChanged, [this](const QString tex) {m_edit->append(tex); });
	pannel->addWidget(com);
		
	// ����combox2
	com = new SARibbonComboBox(this);
	com->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	for (int i = 0; i < 20; ++i)
	{
		com->addItem(QString("ComboBox test2 %1").arg(i));
	}
	connect(com, &QComboBox::currentTextChanged, [this](const QString tex) {m_edit->append(tex); });
	pannel->addWidget(com);

	// ����checkbox
	SARibbonCheckBox *checkbox = new SARibbonCheckBox(this);
	checkbox->setText(tr("���Թ�ѡ��"));
	connect(checkbox, &QCheckBox::stateChanged, [this](int state) {
		m_edit->append(QString("checkbox state: %1").arg(state == Qt::Unchecked ? QString("unchecked") : QString("checked")));
	});
	pannel->addWidget(checkbox);

	// ȫ����ť
	act = new QAction(this);
	act->setIcon(QIcon(":/images/icon/image/fullscreen.png"));
	act->setText("ȫ��");
	pannel->addLargeAction(act);
	connect(act, &QAction::triggered, this, [this]() {menuBar()->hide();});




	//���2
	SARibbonPannel* panne2 = page->addPannel(QStringLiteral("pannel 2"));

	// ��
	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/folder.png"));
	act->setText(tr("��"));
	openMenu = new SARibbonMenu(this);
	actionOpen = new QAction(QIcon(":/icon/icon/folder.png"), tr("��..."), this);
	openMenu->addAction(actionOpen);
	connect(actionOpen, &QAction::triggered, [this, actionOpen]() {m_edit->append(actionOpen->text()); });
	act->setMenu(openMenu);
	btn = panne2->addLargeAction(act);
	btn->setObjectName(tr("��"));
	btn->setPopupMode(QToolButton::MenuButtonPopup);
	connect(act, &QAction::triggered, this, [this, act]() {m_edit->append(act->text()); });

	// �л�����
	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/save.png"));
	act->setText(tr("�л�"));
	act->setCheckable(true);
	pannel->addSmallAction(act);
	connect(act, &QAction::triggered, this, [this, act](bool b) {
		if (b)
			ribbonBar()->setRibbonStyle(SARibbonBar::WpsLiteStyle);
		else
			ribbonBar()->setRibbonStyle(SARibbonBar::OfficeStyle);
		update();

		m_edit->append(act->text() + QString("%1").arg(b ? tr("���Ͻ�") : tr("���Ͻ�")));
	});

	// ���԰�ť2
	act = new QAction(this);
	act->setIcon(QIcon(":/images/icon/image/file-text-o.png"));
	act->setText(tr("���԰�ť2"));
	act->setCheckable(true);
	panne2->addSmallAction(act);
	connect(act, &QAction::triggered, this, [this, act]() {
		m_edit->append(act->text());
	});
	// ���԰�ť3
	act = new QAction(this);
	act->setIcon(QIcon(":/images/icon/image/paste.png"));
	act->setText(tr("���԰�ť3"));
	act->setCheckable(true);
	panne2->addSmallAction(act);
	connect(act, &QAction::triggered, this, [this, act]() {
		m_edit->append(act->text());
	});
	// ���԰�ť4
	act = new QAction(this);
	act->setIcon(QIcon(":/images/icon/image/eye.png"));
	act->setText(tr("���԰�ť4"));
	act->setCheckable(true);
	panne2->addSmallAction(act);
	connect(act, &QAction::triggered, this, [this, act]() {
		m_edit->append(act->text());
	});

	// �����˵����ԣ�Qmenu��
	act = new QAction(this);
	act->setIcon(QIcon(":/images/icon/image/save.png"));
	act->setText(tr("���Բ˵���1"));
	act->setMenu(menu);
	btn = panne2->addSmallAction(act);
	btn->setPopupMode(QToolButton::MenuButtonPopup);

		
	//SARibbonGallery* gallery = pannel->addGallery();
	//SARibbonGalleryGroup*group = gallery->addGalleryGroup();
	//for (int i = 0; i < 100; ++i)
	//{
	//	group->addItem(QIcon(":/icon/icon/folder.png"));
	//}

	//pannel->setExpanding();
	//QAction* optAct = new QAction(this);
	//pannel->addOptionAction(optAct);
	//����
//	pannel->addGallery();

}

void UITest::createCategoryOther(SARibbonCategory* page)
{
	SARibbonPannel* pannel = page->addPannel(QStringLiteral("pannelOther"));
	//����
	QAction *act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
	act->setText(tr("OTHER"));
	pannel->addLargeAction(act);
	connect(act, &QAction::triggered, this, [this]() {
		this->m_edit->append("action save clicked");
	});
}

void UITest::createCategoryOther2(SARibbonCategory* page)
{
	SARibbonPannel* pannel = page->addPannel(QStringLiteral("pannelOther2"));
	//����
	QAction *act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/save.png"));
	act->setText(tr("OTHER2"));
	pannel->addLargeAction(act);
	connect(act, &QAction::triggered, this, [this]() {
		this->m_edit->append("action save clicked");
	});
}

void UITest::createDockWindows()
{
	viewMenu = new SARibbonMenu(this);

	CustomDockWidget *dockWidget = new CustomDockWidget(tr("����������1"), this);
	dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
	QCalendarWidget *calenderWidget = new QCalendarWidget(dockWidget);
	dockWidget->setWidget(calenderWidget);
	dockWidget->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	//dockWidget->setTitleBarWidget(NULL);

	CustomDockWidget *dockWidget2 = new CustomDockWidget(tr("����������2"), this);
	dockWidget2->setAllowedAreas(Qt::AllDockWidgetAreas);
	QListWidget *listWidget2 = new QListWidget(dockWidget2);
	listWidget2->addItems(QStringList() << "�б�");
	dockWidget2->setWidget(listWidget2);
	dockWidget2->setFeatures(QDockWidget::AllDockWidgetFeatures);

	CustomDockWidget *dockWidget3 = new CustomDockWidget(tr("����������3"), this);
	dockWidget3->setAllowedAreas(Qt::AllDockWidgetAreas);
	QListWidget *listWidget3 = new QListWidget(dockWidget3);
	listWidget3->addItems(QStringList() << "�б�");
	dockWidget3->setWidget(listWidget3);
	dockWidget3->setFeatures(QDockWidget::AllDockWidgetFeatures);

	CustomDockWidget *dockWidget4 = new CustomDockWidget(tr("����������4"), this);
	dockWidget4->setAllowedAreas(Qt::AllDockWidgetAreas);
	QListWidget *listWidget4 = new QListWidget(dockWidget4);
	listWidget4->addItems(QStringList() << "�б�");
	dockWidget4->setWidget(listWidget4);
	dockWidget4->setFeatures(QDockWidget::AllDockWidgetFeatures);

	CustomDockWidget *dockWidget5 = new CustomDockWidget(tr("����������5"), this);
	dockWidget5->setAllowedAreas(Qt::AllDockWidgetAreas);
	QListWidget *listWidget5 = new QListWidget(dockWidget5);
	listWidget4->addItems(QStringList() << "�б�");
	dockWidget5->setWidget(listWidget5);
	dockWidget5->setFeatures(QDockWidget::AllDockWidgetFeatures);

	//��ӵ������� 
	this->addDockWidget(Qt::RightDockWidgetArea, dynamic_cast<QDockWidget*>(dockWidget));
	this->addDockWidget(Qt::RightDockWidgetArea, dynamic_cast<QDockWidget*>(dockWidget2));
	this->addDockWidget(Qt::LeftDockWidgetArea, dynamic_cast<QDockWidget*>(dockWidget3));
	this->addDockWidget(Qt::LeftDockWidgetArea, dynamic_cast<QDockWidget*>(dockWidget4));
	this->addDockWidget(Qt::BottomDockWidgetArea, dynamic_cast<QDockWidget*>(dockWidget5));

	QAction *defaultAct = new QAction(QIcon(":/icon/icon/filter.png"), tr("default"), this);
	connect(defaultAct, &QAction::triggered, this, &UITest::onDefault);
	viewMenu->addAction(defaultAct);	

	//��ʾ/����
	viewMenu->addAction(dockWidget->toggleViewAction());
	viewMenu->addAction(dockWidget2->toggleViewAction());
	viewMenu->addAction(dockWidget3->toggleViewAction());
	viewMenu->addAction(dockWidget4->toggleViewAction());
	viewMenu->addAction(dockWidget5->toggleViewAction());

	m_listDockWidget.append(dockWidget);
	m_listDockWidget.append(dockWidget2);
	m_listDockWidget.append(dockWidget3);
	m_listDockWidget.append(dockWidget4);
	m_listDockWidget.append(dockWidget5);
}
