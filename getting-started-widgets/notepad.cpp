#include "notepad.h"
#include "ui_notepad.h"

#include <QCoreApplication>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(onQuit()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onOpen()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(onSave()));
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::onQuit()
{
    QCoreApplication::quit();
}

void Notepad::onOpen()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, "Open file", QString(), "Text Files (*.txt);;C++ Files(*.cpp *.h)");

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open file");
        return;
    }

    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    file.close();
}

void Notepad::onSave()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save File As", QString(), "Text Files (*.txt);;C++ Files (*.cpp *.h)");

    if(fileName.isEmpty())
        return;

    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Could not save file");
        return;
    }

    QTextStream stream(&file);
    stream << ui->textEdit->toPlainText();
    stream.flush();
    file.close();
}
