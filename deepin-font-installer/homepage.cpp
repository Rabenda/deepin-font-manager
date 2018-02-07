/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
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

#include "homepage.h"
#include "utils.h"
#include <DSvgRenderer>
#include <QApplication>
#include <QStandardPaths>
#include <QDir>

QString configPath()
{
    return QDir(QDir(QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first())
                .filePath(qApp->organizationName())).filePath(qApp->applicationName());
}

HomePage::HomePage(QWidget *parent)
    : QWidget(parent),
      m_layout(new QVBoxLayout(this)),
      m_iconLabel(new QLabel),
      m_tipsLabel(new QLabel(tr("Drag font file here"))),
      m_splitLine(new QLabel),
      m_chooseBtn(new DLinkButton(tr("Select file"))),
      m_settings(new QSettings(QDir(configPath()).filePath("config.conf"), QSettings::IniFormat))
{
    const auto ratio = devicePixelRatioF();

    m_unloadPixmap = DSvgRenderer::render(":/images/font_unload.svg", QSize(160, 160) * ratio);
    m_unloadPixmap.setDevicePixelRatio(ratio);

    m_loadedPixmap = DSvgRenderer::render(":/images/font_loaded.svg", QSize(160, 160) * ratio);
    m_loadedPixmap.setDevicePixelRatio(ratio);

    m_iconLabel->setFixedSize(160, 160);
    m_iconLabel->setPixmap(m_unloadPixmap);
    m_splitLine->setPixmap(QPixmap(":/images/split_line.svg"));
    m_tipsLabel->setStyleSheet("QLabel { color: #6a6a6a; }");

    if (m_settings->value("dir").toString().isEmpty()) {
        m_settings->setValue("dir", "");
    }

    m_layout->addSpacing(40);
    m_layout->addWidget(m_iconLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    m_layout->addSpacing(20);
    m_layout->addWidget(m_tipsLabel, 0, Qt::AlignHCenter);
    m_layout->addSpacing(15);
    m_layout->addWidget(m_splitLine, 0, Qt::AlignHCenter);
    m_layout->addSpacing(15);
    m_layout->addWidget(m_chooseBtn, 0, Qt::AlignHCenter);
    m_layout->addStretch();
    m_layout->setSpacing(0);

    connect(m_chooseBtn, &DLinkButton::clicked, this, &HomePage::onChooseBtnClicked);
}

HomePage::~HomePage()
{
}

void HomePage::setIconPixmap(bool isLoaded)
{
    if (isLoaded) {
        m_iconLabel->setPixmap(m_loadedPixmap);
    } else {
        m_iconLabel->setPixmap(m_unloadPixmap);
    }
}

void HomePage::onChooseBtnClicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(Utils::suffixList());
    dialog.setDirectory(m_settings->value("dir").toString());

    const int mode = dialog.exec();
    m_settings->setValue("dir", dialog.directoryUrl().toLocalFile());

    if (mode != QDialog::Accepted) {
        return;
    }

    emit fileSelected(dialog.selectedFiles());
}
