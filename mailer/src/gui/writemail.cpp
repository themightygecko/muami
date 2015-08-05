#include <QDesktopWidget>
#include "src/gui/writemail.h"
#include "ui_writemail.h"
#include "src/gui/addressbook.h"
#include "src/gui/handleissues.h"
#include "src/gui/attachfilewindow.h"


WriteMail::WriteMail(QWidget *parent, bool display) :
    QMainWindow(parent),
    ui(new Ui::WriteMail)
{
    ui->setupUi(this);
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignLeft,
            this->size(),
            qApp->desktop()->availableGeometry()
            )
        ) ;

    ui->title->setMaxLength(80);
    ui->message->setFontPointSize(11);
    ui->message->setFontWeight(40) ;
    ui->closeAddressBook->setVisible(false);
    ui->attachedFiles->setVisible(false);
    ui->deleteFile->setVisible(false);
    ui->attachedLabel->setVisible(false);

    connect(ui->addressBookButton,
            SIGNAL(clicked()),
            SLOT(addAddressBook())) ;

    if (!display)
    {
        ui->title->setVisible(false);
        ui->titleLabel->setVisible(false);
        ui->to->setVisible(false);
        ui->toLabel->setVisible(false);
        ui->cc->setVisible(false);
        ui->ccLabel->setVisible(false);
        ui->bcc->setVisible(false);
        ui->bccLabel->setVisible(false);
        ui->addressBookButton->setVisible(false);
        ui->attachButton->setVisible(false);
        ui->messageLabel->setText("");
        ui->messageLabel->setStyleSheet("color:#333536");
        ui->sendButton->setVisible(false);
        ui->cancelButton->setVisible(false);
        ui->message->setReadOnly(true);
    }
    else
    {
        ui->replyAllButton->setVisible(false);
        ui->replyButton->setVisible(false);
        ui->transferButton->setVisible(false);
        ui->closeButton->setVisible(false);
        ui->deleteButton->setVisible(false);
    }

}

WriteMail::~WriteMail()
{
    delete ui;
}

void WriteMail::addContent(QStringList content)
{
    ui->to->setText(content[0]);
    ui->cc->setText(content[1]);
    ui->bcc->setText(content[2]);
    ui->title->setText(content[3]);
    ui->message->setText(content[4]);
}


void WriteMail::addAddressBook()
{
    AddressBook *book = new AddressBook(this);
    book->show();
    ui->closeAddressBook->setVisible(true);

    connect(ui->closeAddressBook,
            SIGNAL(clicked()),
            book,
            SLOT(close()));

    connect(ui->closeAddressBook,
            SIGNAL(clicked(bool)),
            ui->closeAddressBook,
            SLOT(setVisible(bool)));

    connect(ui->deleteButton,
            SIGNAL(clicked()),
            SLOT(deleteAttachedFile()));
}

void WriteMail::setVisibleBookButton(bool n)
{
    ui->closeAddressBook->setVisible(n);
}


/** ++ Gestion de l'envoi ++ **/
void WriteMail::on_sendButton_clicked()
{
    on_actionSend_triggered();
}

void WriteMail::on_actionSend_triggered()
{
    QString alarm ;
    QString block ;

    if (ui->title->text() == "")
    {
        alarm.append("- Il manque l'objet du mail.\n") ;
        block = "forceSending";
    }

    if (ui->message->toPlainText() == "")
    {
        alarm.append("- Il manque le corps du mail.\n") ;
        block = "forceSending";
    }

    if (ui->to->text().length() > 0)
    {
        QRegExp mailRegex("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b") ;
        mailRegex.setCaseSensitivity(Qt::CaseInsensitive);
        mailRegex.setPatternSyntax(QRegExp::RegExp);

        if (!mailRegex.exactMatch(ui->to->text()))
        {
            alarm.append("- L'adresse mail est invalide.\n") ;
            block = "forbidSending" ;
        }
    }

    if (ui->to->text().length() == 0)
    {
        alarm.append("- Il manque un destinataire.\n") ;
        block = "forbidSending" ;
    }

    if (block.length() > 0)
    {
        HandleIssues *box = new HandleIssues(this, alarm, block) ;
        box->show();
    }

    else if (block.length() == 0)
    {
        // send_confirmed() en dessous
        this->close() ;
    }
}

void WriteMail::sendConfirmed()    // PARSER LES DONNEES POUR GESTION PAR LES FONCTIONS DE MM
{
    // ACTION D'ENVOI
    // GERER LES OBJETS ATTACHES
}
/** ~~ Gestion de l'envoi ~~ **/


/** ++ Gestion des réponses ++ **/
void WriteMail::on_replyButton_clicked()
{
    on_actionReply_triggered();
}

void WriteMail::on_actionReply_triggered()
{
    setStuff() ;
    // remplir les champs to, cc, etc..
}


void WriteMail::on_replyAllButton_clicked()
{
    on_actionReplyAll_triggered();
}

void WriteMail::on_actionReplyAll_triggered()
{
    setStuff() ;
    // idem que reply
}


void WriteMail::on_transferButton_clicked()
{
    on_actionTransfer_triggered();
}

void WriteMail::on_actionTransfer_triggered()
{
    setStuff() ;
    // idem que reply
}
/** ~~ Gestion des réponses ~~ **/


/** ++ Gestion des actions diverses ++ **/
void WriteMail::on_deleteButton_clicked()
{
    on_actionDelete_triggered();
}

void WriteMail::on_actionDelete_triggered()
{
    QString str = "Voulez-vous supprimer ce courrier ?" ;
    HandleIssues *box = new HandleIssues(this, str, "deleteFromNew") ;
    box->show();
}

void WriteMail::on_cancelButton_clicked()
{
    on_actionCancel_triggered() ;
}

void WriteMail::on_actionCancel_triggered()
{
    QString str = "Voulez-vous annuler les modifications et fermer la fenêtre ?" ;
    HandleIssues *box = new HandleIssues(this, str, "cancelFromNew") ;
    box->show();
}

void WriteMail::on_saveButton_clicked()
{
    on_actionSave_triggered();
}

void WriteMail::on_actionSave_triggered()       // Sauvegarder sur DD ou brouillon ?
{

}

void WriteMail::on_closeButton_clicked()
{
    on_actionClose_triggered();
}

void WriteMail::on_actionClose_triggered()
{
    this->close();
}

void WriteMail::setStuff()
{
    ui->title->setVisible(true);
    ui->titleLabel->setVisible(true);
    ui->to->setVisible(true);
    ui->toLabel->setVisible(true);
    ui->cc->setVisible(true);
    ui->ccLabel->setVisible(true);
    ui->bcc->setVisible(true);
    ui->bccLabel->setVisible(true);
    ui->addressBookButton->setVisible(true);
    ui->attachButton->setVisible(true);
    ui->messageLabel->setText("corps :");
    ui->messageLabel->setStyleSheet("color:#DCE0E3; font:bold");
    ui->sendButton->setVisible(true);
    ui->cancelButton->setVisible(true);
    ui->closeButton->setVisible(false);
    ui->replyAllButton->setVisible(false);
    ui->replyButton->setVisible(false);
    ui->transferButton->setVisible(false);
    ui->message->setReadOnly(false);
}
/** ~~ Gestion des actions diverses ~~ **/


/** ++ Gestion des pièces jointes ++ **/
void WriteMail::on_attachButton_clicked()
{
    on_actionAttach_triggered() ;
}

void WriteMail::on_actionAttach_triggered()
{
    AttachFileWindow *box = new AttachFileWindow(this) ;
    box->show();
}

void WriteMail::addFile(QString filepath)
{
    QStringList parts = filepath.split("\\");
    QString file = parts.last();
    ui->attachedFiles->setVisible(true);
    ui->deleteFile->setVisible(true);
    ui->attachedLabel->setVisible(true);
    QListWidgetItem *item = new QListWidgetItem(ui->attachedFiles);
    item->setText(file);
}

void WriteMail::addFileToMail(QString filepath)
{
    QStringList parts = filepath.split("\\");
    QString file = parts.last();
    ui->attachedFiles->setVisible(true);
    ui->deleteFile->setVisible(true);
    ui->attachedLabel->setVisible(true);
    QListWidgetItem *item = new QListWidgetItem(ui->attachedFiles);
    item->setText(file);
}

void WriteMail::deleteAttachedFile()
{
    if(ui->attachedFiles->currentItem())
    {
        delete ui->attachedFiles->currentItem();
    }
}

/** ~~ Gestion des pièces jointes ~~ **/
