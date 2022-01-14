#ifndef COMMANDLINEDIALOG_H
#define COMMANDLINEDIALOG_H

#include <QDialog>

namespace Ui {
class CommandLineDialog;
}

class CommandLineDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CommandLineDialog(QWidget *parent = 0);

private:
    Ui::CommandLineDialog *ui;

signals:

public slots:
    void setTextBox(const QString cmdargs);
    void copyText();
};

#endif // COMMANDLINEDIALOG_H
