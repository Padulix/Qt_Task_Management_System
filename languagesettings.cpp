// languagesettings.cpp

#include "languagesettings.h"
#include "ui_languagesettings.h"



LanguageSettings::LanguageSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LanguageSettings)
{
    ui->setupUi(this);
    ui->radio_button_english->setChecked(true);

    connect(ui->button_accept, &QPushButton::clicked, this, &LanguageSettings::on_button_accept_clicked);

}

LanguageSettings::~LanguageSettings()
{
    delete ui;
}



void LanguageSettings::on_radio_button_english_clicked()
{

}


void LanguageSettings::on_radio_button_deutsch_clicked()
{

}


void LanguageSettings::on_button_accept_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Start Program"), tr("Do you want to start the Program with the selected Language?"),
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        if (ui->radio_button_deutsch->isChecked())
        {
            static QTranslator translator;
            qApp->removeTranslator(&translator);
            if (translator.load(":/translation/Projekt_Patrick_Pertler_de_DE.qm"))
            {
                qApp->installTranslator(&translator);
                ui->retranslateUi(this);
            }
            else
            {
                QMessageBox::warning(this, tr("Error"), tr("Failed to load German translation file!"));
            }
            close();
        }
        else if(ui->radio_button_english->isChecked())
        {
            static QTranslator translator;
            qApp->removeTranslator(&translator);
            if (translator.load(":/translation/Projekt_Patrick_Pertler_en_150.qm"))
            {
                qApp->installTranslator(&translator);
                ui->retranslateUi(this);
            }
            else
            {
                QMessageBox::warning(this, tr("Error"), tr("Failed to load English translation file!"));
            }
            close();
        }
    }
}



