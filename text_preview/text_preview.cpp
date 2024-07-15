#include "text_preview.h"
#include "ui_text_preview.h"

#include "settings_dlg.h"

TextPreview::TextPreview(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextPreview)
{
    ui->setupUi(this);

    ui->edit->setTextColor(Qt::white);
    ui->edit->setTextBackgroundColor(Qt::transparent);

    ui->combo_font->setCurrentFont(ui->edit->font());
    ui->spin_size->setValue(ui->edit->font().pointSize());

    ui->combo_color->addItem("Черный", QColor(Qt::black));
    ui->combo_color->addItem("Белый", QColor(Qt::white));
    ui->combo_color->addItem("Красный", QColor(Qt::red));
    ui->combo_color->addItem("Зеленый", QColor(Qt::green));
    ui->combo_color->addItem("Синий", QColor(Qt::blue));
    ui->combo_color->addItem("Желтый", QColor(Qt::yellow));
    ui->combo_color->addItem("Голубой", QColor(Qt::cyan));
    ui->combo_color->setCurrentIndex(ui->combo_color->findData(ui->edit->textColor()));

    ui->combo_background_color->addItem("Прозрачный", QColor(Qt::transparent));
    ui->combo_background_color->addItem("Черный", QColor(Qt::black));
    ui->combo_background_color->addItem("Белый", QColor(Qt::white));
    ui->combo_background_color->addItem("Красный", QColor(Qt::red));
    ui->combo_background_color->addItem("Зеленый", QColor(Qt::green));
    ui->combo_background_color->addItem("Синий", QColor(Qt::blue));
    ui->combo_background_color->addItem("Желтый", QColor(Qt::yellow));
    ui->combo_background_color->addItem("Голубой", QColor(Qt::cyan));
    ui->combo_background_color->setCurrentIndex(ui->combo_background_color->findData(ui->edit->textBackgroundColor()));

    connect(ui->edit_text, &QLineEdit::textChanged, ui->edit, &QTextEdit::setText);
    connect(ui->btn_settings, &QPushButton::clicked, this, &TextPreview::openSettings);
    connect(ui->btn_clear, &QPushButton::clicked, this, &TextPreview::clear);
}

TextPreview::~TextPreview()
{
    delete ui;
}

void TextPreview::openSettings()
{
    auto *dlg = new SettingsDlg(this);
    dlg->setCurrentFont(ui->combo_font->currentFont());
    dlg->setFontSize(ui->spin_size->value());
    dlg->setFontColor(qvariant_cast<QColor>(ui->combo_color->currentData()));
    dlg->setFontBackgroundColor(qvariant_cast<QColor>(ui->combo_background_color->currentData()));;

    connect(dlg, &QDialog::accepted, this, [this, dlg]
    {
        ui->combo_font->setCurrentFont(dlg->currentFont());
        ui->spin_size->setValue(dlg->fontSize());
        ui->combo_color->setCurrentIndex(ui->combo_color->findData(dlg->fontColor()));
        ui->combo_background_color->setCurrentIndex(ui->combo_background_color->findData(dlg->fontBackgroundColor()));
        updateEdit();
    });
    dlg->open();
}

void TextPreview::clear()
{
    ui->edit_text->clear();
}

void TextPreview::updateEdit()
{
    ui->edit->selectAll();

    auto f = ui->combo_font->currentFont();
    f.setPointSize(ui->spin_size->value());
    ui->edit->setCurrentFont(f);
    ui->edit->setTextColor(qvariant_cast<QColor>(ui->combo_color->currentData()));
    ui->edit->setTextBackgroundColor(qvariant_cast<QColor>(ui->combo_background_color->currentData()));

    ui->edit->moveCursor(QTextCursor::End);
}

