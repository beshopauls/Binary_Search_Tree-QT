#include "mainwindow.h"
#include "bst_about_window.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QMenuBar>
#include <QSpacerItem>
#include <qglobal.h>
#include <QTime>
#include <QFileDialog>
#include <QStandardPaths>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QStringListIterator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) ;
    if (!QDir(directory).exists())
        QDir().mkdir(directory);
    this->bst = this->getBST();
    this->createMenu();
    deleteButton = new QPushButton("&Delete", this);
    insertButton = new QPushButton("Insert", this);
    insertValueLineEdit = new QLineEdit;
    deleteValueLineEdit = new QLineEdit;
    statusLabel = new QLabel;
    deleteButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    insertButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    insertValueLineEdit->setFixedWidth(100);
    insertValueLineEdit->setToolTip("Enter single value or multiple values separated by space");
    deleteValueLineEdit->setFixedWidth(100);
    deleteValueLineEdit->setToolTip("Enter value to delete");
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));
    connect(insertValueLineEdit, SIGNAL(returnPressed()), this, SLOT(insertClicked()));
    connect(deleteValueLineEdit, SIGNAL(returnPressed()), this, SLOT(deleteClicked()));
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(deleteValueLineEdit);
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(insertValueLineEdit);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(statusLabel);
    buttonLayout->addStretch(0);
    renderArea = new RenderArea(this->bst);
    treeScrollArea = new QScrollArea;
    treeScrollArea->setWidget(renderArea);
    treeScrollArea->installEventFilter(renderArea);
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(treeScrollArea);
    mainLayout->addLayout(buttonLayout);
    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget(centralWidget);
    this->setMinimumHeight(400);
    this->setWindowTitle("Binary Search Tree");
    this->show();
}
void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   this->renderArea->callRepaint();
}
MainWindow::~MainWindow()
{
    delete renderArea;
    delete deleteButton;
    delete insertButton;
    delete treeScrollArea;
    delete bst;
    delete centralWidget;
}
void MainWindow::createMenu()
{
    this->createActions();
    this->menuBar()->addAction(aboutAction);
}
void MainWindow::createActions()
{
    aboutAction = new QAction(tr(""), this);
}
void MainWindow::deleteClicked() const {
    QString value = deleteValueLineEdit->text();
    if(!this->bst->deleteItem(value.toInt()))
        this->statusLabel->setText("");
    else
        this->statusLabel->setText("");
    this->renderArea->repaint();
    this->deleteValueLineEdit->setText("");
    return;
}
void MainWindow::insertClicked() const
{
    QString values = insertValueLineEdit->text();
    QStringList valueList = values.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QStringListIterator iterator(valueList);
    while (iterator.hasNext())
    {
        if(!this->bst->insert(iterator.next().toInt()))
            this->statusLabel->setText("");
        else
            this->statusLabel->setText("");
    }
    this->renderArea->repaint();
    insertValueLineEdit->setText("");
    return;
}
BinarySearchTree<int>* MainWindow::getBST()
{
    BinarySearchTree<int> *bst = new BinarySearchTree<int>;
    QString fileName = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    QString text;
    QFile file(fileName);
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return bst;
    }
    QTextStream reader(&file);
    while (!reader.atEnd())
    {
        reader >> text;
        if (text != " " && text != "")
            bst->insert(text.toInt());
    }

    file.close();
    return bst;
}

