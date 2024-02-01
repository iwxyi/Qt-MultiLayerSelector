#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // 创建测试数据
    LayerItemInfo* root = new LayerItemInfo("root");
    LayerItemInfo* item1 = new LayerItemInfo("item1");
    LayerItemInfo* item2 = new LayerItemInfo("item2");
    LayerItemInfo* item3 = new LayerItemInfo("item3");
    root->addSubItem(item1);
    root->addSubItem(item2);
    root->addSubItem(item3);
    root->setCurrentIndex(0);
    ui->widget->setData(root);
}

MainWindow::~MainWindow()
{
    delete ui;
}

