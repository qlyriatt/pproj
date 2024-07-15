#pragma once

#include <QDialog>

namespace Ui
{
class SettingsDlg;
}

class SettingsDlg : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDlg(QWidget *parent = nullptr);
    ~SettingsDlg() override;

    void setCurrentFont(const QFont &font);
    QFont currentFont() const;

    void setFontSize(int size);
    int fontSize() const;

    void setFontColor(const QColor &color);
    QColor fontColor() const;

    void setFontBackgroundColor(const QColor &color);
    QColor fontBackgroundColor() const;
private:
    Ui::SettingsDlg *ui;
};

