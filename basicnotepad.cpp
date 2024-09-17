#include "basicnotepad.h"
#include "./ui_basicnotepad.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>

BasicNotepad::BasicNotepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BasicNotepad)
{
    ui->setupUi(this);
}

BasicNotepad::~BasicNotepad()
{
    delete ui;
}


void BasicNotepad::closeEvent(QCloseEvent *event){

    if(ui->textEdit->toPlainText().isEmpty() ||  isSaved){
        event->accept();
    }
    else{
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Save", "Do you want to save?\n",QMessageBox::No | QMessageBox::Yes);
        if(resBtn != QMessageBox::Yes){
            event->ignore();
        }
        else{
            event->accept();
        }
    }


}

void BasicNotepad::on_actionNew_triggered()
{
    currentFile.clear();

    ui->textEdit->setText(QString());
}


void BasicNotepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open the file");
    if(fileName.isEmpty()) return;

    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot open file: "+ file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();





}



void BasicNotepad::SaveFile(){
    QString fileName;
    if(currentFile.isEmpty()){
        fileName = QFileDialog::getSaveFileName(this,"Save");
        if(fileName.isEmpty()) return;
        currentFile = fileName;
    }
    else{
        fileName = currentFile;
    }

    QFile file(fileName + ".txt");
    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
    isSaved = true;
}

void BasicNotepad::on_actionSave_triggered()
{
    SaveFile();
}


void BasicNotepad::on_actionSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save as");

    QFile file(fileName + ".txt");

    if(!file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning","Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
    isSaved = true;
}


void BasicNotepad::on_actionPrint_triggered()
{
#if defined(QT_PRINTSUPPORT_LIB)&& QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev,this);
    if(dialog.exec() == QDialog::Rejected) return;
#endif // QT_CONFIG(printdialog)
    ui->textEdit->print(&printDev);
#endif // QT_CONFIG(printer)
}


void BasicNotepad::on_actionExit_triggered()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Quit","Are you sure?",QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){

        if(ui->textEdit->toPlainText().isEmpty() || isSaved){
            QApplication::exit();
        }
        else{
            QMessageBox::StandardButton saveReply;
            saveReply = QMessageBox::question(this,"Save","Do you want to save document?",QMessageBox::Yes | QMessageBox::No);
            if(saveReply == QMessageBox::Yes){
                SaveFile();

            }
            QApplication::exit();
        }

    }

}


void BasicNotepad::on_textEdit_textChanged(){
    isSaved = false;
}


