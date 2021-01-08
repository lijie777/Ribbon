#pragma once

#include "SARibbonMainWindow.h"
class SARibbonCategory;
class SARibbonContextCategory;
class QTextEdit;
class CustomDockWidget;
class SARibbonMenu;

class UITest : public SARibbonMainWindow
{
	Q_OBJECT
public:
	UITest(QWidget* par = nullptr);

public slots :
	void onDefault();
	void onOpen();
private:
	void createCategoryMain(SARibbonCategory* page);

	void createCategoryOther(SARibbonCategory* page);

	void createCategoryOther2(SARibbonCategory* page);

	void createDockWindows();
private:
	SARibbonMenu *viewMenu;// 更改布局结构菜单
	QList<CustomDockWidget *> m_listDockWidget;
	SARibbonContextCategory* m_contextCategory;
	QTextEdit* m_edit;
};
