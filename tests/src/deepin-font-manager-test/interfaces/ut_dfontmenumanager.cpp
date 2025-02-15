/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:
*
* Maintainer:
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "interfaces/dfontmenumanager.h"

#include <DApplicationHelper>
#include <DApplication>
#include <DMenu>
#include <DLog>

#include <gtest/gtest.h>
#include "../third-party/stub/stub.h"

namespace {
class TestDFontMenuManager : public testing::Test
{

protected:
    void SetUp()
    {
        fm = DFontMenuManager::getInstance();
    }
    void TearDown()
    {
//        delete fm;
    }
    // Some expensive resource shared by all tests.
    QWidget *w = new QWidget;
    DFontMenuManager *fm;
};

}

TEST_F(TestDFontMenuManager, checkCreateToolBarSettingsMenu)
{
    fm->initMenuData();
    DMenu *menu = fm->createToolBarSettingsMenu();

    EXPECT_FALSE(menu->isEmpty());
    //有一行分割线
    EXPECT_TRUE(fm->m_fontToolsBarMenus.count() == 1);

    DFontMenuManager::FMenuItem *item = new DFontMenuManager::FMenuItem(DApplication::translate("Menu", "Add font"),
                                                                        DFontMenuManager::MenuAction::M_AddFont, true, false);

    item->subMenulist.append(new DFontMenuManager::FMenuItem(DApplication::translate("Menu", "Add font"),
                                                             DFontMenuManager::MenuAction::M_AddFont, false, false));
    fm->m_fontToolBarMenuData.append(item);
    fm->createToolBarSettingsMenu();
    EXPECT_TRUE(fm->m_fontToolBarMenuData.count() == 5);
}

TEST_F(TestDFontMenuManager, checkCreateRightKeyMenu)
{
    DMenu *menu = fm->createRightKeyMenu();

    EXPECT_FALSE(menu->isEmpty());
    //有七项
    EXPECT_TRUE(fm->m_fontRightKeyMenus.count() == 7);

    DFontMenuManager::FMenuItem *item = new DFontMenuManager::FMenuItem(DApplication::translate("Menu", "Add font"),
                                                                        DFontMenuManager::MenuAction::M_AddFont, true, false);

    item->subMenulist.append(new DFontMenuManager::FMenuItem(DApplication::translate("Menu", "Add font"),
                                                             DFontMenuManager::MenuAction::M_AddFont, false, false));
    fm->m_fontRightMenuData.append(item);
    fm->createRightKeyMenu();
    EXPECT_FALSE(fm->m_fontRightKeyMenus.value(DFontMenuManager::MenuAction::M_AddFont)->fGroupSubMenu);
}

TEST_F(TestDFontMenuManager, checkOnRightKeyMenuPopup)
{
    DFontPreviewItemData data;
    data.fontData.setCollected(true);
    fm->onRightKeyMenuPopup(data, true, true, true);
    EXPECT_TRUE(fm->getActionByMenuAction(DFontMenuManager::M_DeleteFont,
                                          DFontMenuManager::MenuType::RightKeyMenu)->isEnabled());
    EXPECT_TRUE(fm->getActionByMenuAction(DFontMenuManager::M_ExportFont,
                                          DFontMenuManager::MenuType::RightKeyMenu)->isEnabled());
    data.fontData.setCollected(false);
    data.fontData.setEnabled(true);
    fm->onRightKeyMenuPopup(data, false, true, false);
    EXPECT_FALSE(fm->getActionByMenuAction(DFontMenuManager::M_DeleteFont,
                                           DFontMenuManager::MenuType::RightKeyMenu)->isEnabled());
    EXPECT_FALSE(fm->getActionByMenuAction(DFontMenuManager::M_ExportFont,
                                           DFontMenuManager::MenuType::RightKeyMenu)->isEnabled());

    data.fontData.setCollected(false);
    data.fontData.setEnabled(true);
    fm->onRightKeyMenuPopup(data, false, false, false);
    EXPECT_FALSE(fm->getActionByMenuAction(DFontMenuManager::M_DeleteFont,
                                           DFontMenuManager::MenuType::RightKeyMenu)->isEnabled());
    EXPECT_FALSE(fm->getActionByMenuAction(DFontMenuManager::M_ExportFont,
                                           DFontMenuManager::MenuType::RightKeyMenu)->isEnabled());
}

TEST_F(TestDFontMenuManager, checkGetActionByMenuAction)
{
    QAction *addAction = DFontMenuManager::getInstance()->getActionByMenuAction(
                             DFontMenuManager::M_AddFont, DFontMenuManager::MenuType::ToolBarMenu);

    EXPECT_TRUE(addAction->text() == "Add font");
}

