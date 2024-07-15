#include "settings_dlg.h"
#include "ui_settings_dlg.h"

SettingsDlg::SettingsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDlg)
{
    ui->setupUi(this);

    ui->combo_color->addItem("Черный", QColor(Qt::black));
    ui->combo_color->addItem("Белый", QColor(Qt::white));
    ui->combo_color->addItem("Красный", QColor(Qt::red));
    ui->combo_color->addItem("Зеленый", QColor(Qt::green));
    ui->combo_color->addItem("Синий", QColor(Qt::blue));
    ui->combo_color->addItem("Желтый", QColor(Qt::yellow));
    ui->combo_color->addItem("Голубой", QColor(Qt::cyan));

    ui->combo_background_color->addItem("Прозрачный", QColor(Qt::transparent));
    ui->combo_background_color->addItem("Черный", QColor(Qt::black));
    ui->combo_background_color->addItem("Белый", QColor(Qt::white));
    ui->combo_background_color->addItem("Красный", QColor(Qt::red));
    ui->combo_background_color->addItem("Зеленый", QColor(Qt::green));
    ui->combo_background_color->addItem("Синий", QColor(Qt::blue));
    ui->combo_background_color->addItem("Желтый", QColor(Qt::yellow));
    ui->combo_background_color->addItem("Голубой", QColor(Qt::cyan));
}

SettingsDlg::~SettingsDlg()
{
    delete ui;
}

void SettingsDlg::setCurrentFont(const QFont &font)
{
    ui->combo_font->setCurrentFont(font);
}

QFont SettingsDlg::currentFont() const
{
    return ui->combo_font->currentFont();
}

void SettingsDlg::setFontSize(int size)
{
    ui->spin_size->setValue(size);
}

int SettingsDlg::fontSize() const
{
    return ui->spin_size->value();
}

void SettingsDlg::setFontColor(const QColor &color)
{
    ui->combo_color->setCurrentIndex(ui->combo_color->findData(color));
}

QColor SettingsDlg::fontColor() const
{
    return qvariant_cast<QColor>(ui->combo_color->currentData());
}

void SettingsDlg::setFontBackgroundColor(const QColor &color)
{
    ui->combo_background_color->setCurrentIndex(ui->combo_background_color->findData(color));
}

QColor SettingsDlg::fontBackgroundColor() const
{
    return qvariant_cast<QColor>(ui->combo_background_color->currentData());
}
