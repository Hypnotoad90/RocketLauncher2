#include "commandlinedialog.h"
#include "ui_commandlinedialog.h"

CommandLineDialog::CommandLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommandLineDialog)
{
    ui->setupUi(this);

    connect(ui->button_copycmd, SIGNAL(pressed()), this, SLOT(copyText()));

}

void CommandLineDialog::setTextBox(QString cmdargs){
    ui->text_cmd->setPlainText(cmdargs);
    ui->text_cmd->setReadOnly(true);
}
void CommandLineDialog::copyText(){
    ui->text_cmd->selectAll();
    ui->text_cmd->copy();

}
