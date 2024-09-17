#ifndef BASICNOTEPAD_H
#define BASICNOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class BasicNotepad;
}
QT_END_NAMESPACE

class BasicNotepad : public QMainWindow
{
    Q_OBJECT

public:
    BasicNotepad(QWidget *parent = nullptr);
    ~BasicNotepad();

private slots:

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void SaveFile();

    void closeEvent(QCloseEvent *event);

    void on_textEdit_textChanged();

private:
    Ui::BasicNotepad *ui;
    QString currentFile;
    bool isSaved;
};
#endif // BASICNOTEPAD_H
