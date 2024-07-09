#ifndef LANGUAGESETTINGS_H
#define LANGUAGESETTINGS_H

#include <QWidget>
#include <QMessageBox>
#include <QTranslator>

namespace Ui {
class LanguageSettings;
}

class LanguageSettings : public QDialog
{
    Q_OBJECT

public:
    explicit LanguageSettings(QWidget *parent = nullptr);
    ~LanguageSettings();


private slots:

    void on_radio_button_english_clicked();
    void on_radio_button_deutsch_clicked();
    void on_button_accept_clicked();

private:
    Ui::LanguageSettings *ui;
};

#endif // LANGUAGESETTINGS_H
