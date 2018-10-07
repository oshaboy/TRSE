/*
 * Turbo Rascal Syntax error, “;” expected but “BEGIN” (TRSE, Turbo Rascal SE)
 * 8 bit software development IDE for the Commodore 64
 * Copyright (C) 2018  Nicolaas Ervik Groeneboom (nicolaas.groeneboom@gmail.com)
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program (LICENSE.txt).
 *   If not, see <https://www.gnu.org/licenses/>.
*/

#include "dialogtrsesettings.h"
#include "ui_dialogtrsesettings.h"
#include "source/LeLib/util/util.h"
#include <QFileDialog>
#include "source/LeLib/util/util.h"
#include <QStringList>
#include <QDir>


DialogTRSESettings::DialogTRSESettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTRSESettings)
{
    ui->setupUi(this);
}

void DialogTRSESettings::FillFromIni()
{
    ui->leDasm->setText(m_ini->getString("dasm"));
    ui->leEmulator->setText(m_ini->getString("emulator"));
    ui->leVic20Emulator->setText(m_ini->getString("vic20_emulator"));
    ui->leExomizer->setText(m_ini->getString("exomizer"));
//    if (ui->cmbPalette->currentText()=="Dark")
    if (m_ini->getdouble("windowpalette")==0)
        ui->cmbPalette->setCurrentText("Dark");
    if (m_ini->getdouble("windowpalette")==1)
        ui->cmbPalette->setCurrentText("Light");


    QDir directory(Util::path+"themes/");
    QStringList  themes = directory.entryList(QStringList() << "*.ini");
    ui->cmbTheme->clear();
    qDebug() << "themes : " << themes;
    QStringList washed;
    for (QString s: themes) {
        QString name = s.split(".")[0];
        qDebug() << name;
        washed << name;
    }
    ui->cmbTheme->addItems(washed);
    ui->cmbTheme->setCurrentText(m_ini->getString("theme").split(".")[0]);

    ui->leFontSize->setText(QString::number((int)m_ini->getdouble("font_size")));
    ui->leTabWidth->setText(QString::number((int)m_ini->getdouble("tab_width")));

    ui->leFontSizeMemoryAnalyzer->setText(QString::number((int)m_ini->getdouble("memory_analyzer_font_size")));
    ui->chkExomizerFootprint->setChecked(m_ini->getdouble("hide_exomizer_footprint")==1.0);


}


void DialogTRSESettings::FillToIni()
{
    m_ini->setString("dasm", ui->leDasm->text());
    m_ini->setString("exomizer", ui->leExomizer->text());
    m_ini->setString("emulator", ui->leEmulator->text());
    m_ini->setString("vic20_emulator", ui->leVic20Emulator->text());
    m_ini->setString("theme", ui->cmbTheme->currentText() + ".ini");

    m_ini->setFloat("font_size", ui->leFontSize->text().toInt());
    m_ini->setFloat("tab_width", ui->leTabWidth->text().toInt());
    m_ini->setFloat("memory_analyzer_font_size", ui->leFontSizeMemoryAnalyzer->text().toInt());

    m_ini->setFloat("hide_exomizer_footprint", ui->chkExomizerFootprint->isChecked()?1:0);

    if (ui->cmbPalette->currentText()=="Dark")
        m_ini->setFloat("windowpalette",0);
    if (ui->cmbPalette->currentText()=="Light")
        m_ini->setFloat("windowpalette",1);

}

DialogTRSESettings::~DialogTRSESettings()
{
    delete ui;
}

void DialogTRSESettings::on_pushButton_clicked()
{
    FillToIni();
    m_ini->Save();
    close();
}

void DialogTRSESettings::on_btnEmulator_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Emulator location"), m_ini->getString("project_path"), "*");
    ui->leEmulator->setText(filename);

}

void DialogTRSESettings::on_btnExomizer_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Exomizer location"), m_ini->getString("project_path"), "*");
    ui->leExomizer->setText(filename);

}

void DialogTRSESettings::on_btnDasm_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Dasm location"), m_ini->getString("project_path"), "*");
    ui->leDasm->setText(filename);

}
