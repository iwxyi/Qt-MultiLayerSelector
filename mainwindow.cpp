#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建测试数据
    LayerItemInfo *root = new LayerItemInfo("root");
    LayerItemInfo *item1 = new LayerItemInfo(root, "item1");
    LayerItemInfo *item2 = new LayerItemInfo(root, "item2");
    LayerItemInfo *item3 = new LayerItemInfo(root, "item3");

    LayerItemInfo *item11 = new LayerItemInfo(item1, "item11");
    LayerItemInfo *item12 = new LayerItemInfo(item1, "item12");
    LayerItemInfo *item13 = new LayerItemInfo(item1, "item13");
    LayerItemInfo *item21 = new LayerItemInfo(item2, "item21");
    LayerItemInfo *item22 = new LayerItemInfo(item2, "item22");
    LayerItemInfo *item23 = new LayerItemInfo(item2, "item23");
    LayerItemInfo *item31 = new LayerItemInfo(item3, "item31");
    LayerItemInfo *item32 = new LayerItemInfo(item3, "item32");
    LayerItemInfo *item33 = new LayerItemInfo(item3, "item33");
    
    LayerItemInfo *item111 = new LayerItemInfo(item11, "item111");
    LayerItemInfo *item112 = new LayerItemInfo(item11, "item112");
    LayerItemInfo *item113 = new LayerItemInfo(item11, "item113");
    LayerItemInfo *item121 = new LayerItemInfo(item12, "item121");
    LayerItemInfo *item122 = new LayerItemInfo(item12, "item122");
    LayerItemInfo *item123 = new LayerItemInfo(item12, "item123");
    LayerItemInfo *item131 = new LayerItemInfo(item13, "item131");
    LayerItemInfo *item132 = new LayerItemInfo(item13, "item132");
    LayerItemInfo *item133 = new LayerItemInfo(item13, "item133");
    LayerItemInfo *item211 = new LayerItemInfo(item21, "item211");
    LayerItemInfo *item212 = new LayerItemInfo(item21, "item212");
    LayerItemInfo *item213 = new LayerItemInfo(item21, "item213");
    LayerItemInfo *item221 = new LayerItemInfo(item22, "item221");
    LayerItemInfo *item222 = new LayerItemInfo(item22, "item222");
    LayerItemInfo *item223 = new LayerItemInfo(item22, "item223");
    LayerItemInfo *item231 = new LayerItemInfo(item23, "item231");
    LayerItemInfo *item232 = new LayerItemInfo(item23, "item232");
    LayerItemInfo *item233 = new LayerItemInfo(item23, "item233");
    LayerItemInfo *item311 = new LayerItemInfo(item31, "item311");
    LayerItemInfo *item312 = new LayerItemInfo(item31, "item312");
    LayerItemInfo *item313 = new LayerItemInfo(item31, "item313");
    LayerItemInfo *item321 = new LayerItemInfo(item32, "item321");
    LayerItemInfo *item322 = new LayerItemInfo(item32, "item322");
    LayerItemInfo *item323 = new LayerItemInfo(item32, "item323");
    LayerItemInfo *item331 = new LayerItemInfo(item33, "item331");
    LayerItemInfo *item332 = new LayerItemInfo(item33, "item332");
    LayerItemInfo *item333 = new LayerItemInfo(item33, "item333");
    
    root->setCurrentIndex(0);
    
    ui->widget->setData(root);
    
    connect(ui->widget, &MultiLayerSelector::signalItemClicked, [=](QVariant data) {
        qInfo() << "signalItemClicked:" << data;
    });
    connect(ui->widget, &MultiLayerSelector::signalGroupClicked, [=](QVariant data) {
        qInfo() << "signalGroupClicked:" << data;
    });
    connect(ui->widget, &MultiLayerSelector::signalChildClicked, [=](QVariant data) {
        qInfo() << "signalChildClicked:" << data;
    });
    connect(ui->widget, &MultiLayerSelector::signalPathClicked, [=](QList<QVariant> data) {
        qInfo() << "signalPathClicked:" << data;
    });
    connect(ui->widget, &MultiLayerSelector::signalPathIndexClicked, [=](QList<int> data) {
        qInfo() << "signalPathIndexClicked:" << data;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
