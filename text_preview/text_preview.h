#pragma once

#include <QMainWindow>

namespace Ui
{
class TextPreview;
}

class TextPreview : public QMainWindow
{
    Q_OBJECT
public:
    TextPreview(QWidget *parent = nullptr);
    ~TextPreview() override;

private slots:
    void openSettings();
    void clear();
    void updateEdit();
private:
    Ui::TextPreview *ui;
};
