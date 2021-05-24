#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QColorDialog>
#include <QColor>
#include "renderarea.h"
#include "bst_about_window.h"
#include "binarysearchtree.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *centralWidget;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    RenderArea *renderArea;
    QPushButton *deleteButton;
    QPushButton *insertButton;
    QLineEdit *insertValueLineEdit;
    QLineEdit *deleteValueLineEdit;
    QScrollArea *treeScrollArea;
    QVBoxLayout *mainLayout;
    QLabel *statusLabel;
    QAction *aboutAction;
      BinarySearchTree<int> *bst;
    BinarySearchTree<int> *getBST();
    void createMenu();
    void createActions();
protected:
    virtual void resizeEvent(QResizeEvent* event);
private slots:
    void insertClicked() const;
    void deleteClicked() const;

};

#endif
