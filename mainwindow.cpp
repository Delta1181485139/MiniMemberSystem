#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("世界上最好的社交平台");
    setFixedSize(1200,800);
    if(me->isAdministrator())
        ui->hello->setText("您好，尊敬的管理员大人！");
    else
        ui->hello->setText("您好，"+me->getName()+"，欢迎登录！");
    ui->last->setText(me->getLastLogin()==""?"这是您第一次登录！请多指教":"上次登出时间："+me->getLastLogin());
    if(me->isAdministrator()){
        ui->last->hide();
        ui->signatureLabel->hide();
        ui->signature->hide();
        ui->signatureEdit->hide();
        ui->changePwd->hide();
        ui->explore->hide();
        ui->mypublish->hide();
        ui->del->hide();
        ui->plainTextEdit->hide();
        ui->label->hide();
        ui->publish->hide();
        ui->scrollArea->hide();
        ui->deleteUser->hide();
        ui->findframe->hide();
        ui->pass->hide();
        ui->deleteReviewed->hide();
        this->on_manage_clicked();
    }else{
        ui->review->hide();
        ui->reviewed->hide();
        ui->manage->hide();
        ui->tableView->hide();
        ui->deleteUser->hide();
        ui->findframe->hide();
        ui->find->hide();
        ui->yes->hide();
        ui->no->hide();
        ui->pass->hide();
        ui->deleteReviewed->hide();
        ui->signature->setText(me->getSignature());
        ui->label->setText("0/"+QString::number(MAXTEXTSIZE));
        QVBoxLayout *vl = new QVBoxLayout();
        vl->setAlignment(Qt::AlignTop);
        ui->scrollAreaWidgetContents->setLayout(vl);
        this->on_mypublish_clicked();
    }
}

MainWindow::~MainWindow()
{
    if(!me->isAdministrator()){
        Database *query(new Database(dsn,hostname,username,password));
        query->updateLastLogin();
        delete query;
    }
    delete ui;
}

void MainWindow::on_signatureEdit_clicked()
{
    editText edit;
    if(edit.exec()==QDialog::Accepted){
        ui->signature->setText(me->getSignature());
    }
}

void MainWindow::on_publish_clicked()
{
    if(ui->plainTextEdit->toPlainText().count()>MAXTEXTSIZE){
        QMessageBox::information(NULL,"警告","超过最大数字限制");
    }else{
        Database* query(new Database(dsn,hostname,username,password));
        if(query->publishMoment(ui->plainTextEdit->toPlainText())){
            qDebug()<<"success publish";
        }
        delete query;
        this->on_mypublish_clicked();
    }
}

void MainWindow::on_mypublish_clicked()
{
    while(!list.empty()){
        QPlainTextEdit* tmp = list.back();
        list.removeLast();
        delete tmp;
    }
    Database* query(new Database(dsn,hostname,username,password));
    QList<QList<QString>> info(query->getUserPublish());
    delete query;
    for(auto i:info){
        QString str = i[3] == "0"?"(待审核)":"";
        QString content = "用户："+i[0]+"\n发布时间："+i[1]+"\n正文："+i[2]+"\n"+str;
        QPlainTextEdit *frame = new QPlainTextEdit();
        frame->setPlainText(content);
        frame->setReadOnly(true);
        frame->setMaximumHeight(200);
        frame->setMinimumHeight(150);
        ui->scrollAreaWidgetContents->layout()->addWidget(frame);
        list.append(frame);
    }
}

void MainWindow::on_plainTextEdit_textChanged()
{
    ui->label->setText(QString::number(ui->plainTextEdit->toPlainText().count())
                       +"/"+
                       QString::number(MAXTEXTSIZE));
}

void MainWindow::on_explore_clicked()
{
    while(!list.empty()){
        QPlainTextEdit* tmp = list.back();
        list.removeLast();
        delete tmp;  
    }
    Database* query(new Database(dsn,hostname,username,password));
    QList<QList<QString>> info(query->getWholeMes());
    delete query;
    for(auto i:info){
        QString content = "用户："+i[0]+"\n发布时间："+i[1]+"\n正文："+i[2]+"\n";
        QPlainTextEdit *frame = new QPlainTextEdit();
        frame->setPlainText(content);
        frame->setReadOnly(true);
        frame->setMaximumHeight(200);
        ui->scrollAreaWidgetContents->layout()->addWidget(frame);
        list.append(frame);
    }
}

void MainWindow::on_del_clicked()
{
    Deltext de;
    de.exec();
    this->on_mypublish_clicked();
}

void MainWindow::on_manage_clicked()
{
    ui->deleteUser->show();
    ui->findframe->show();
    ui->find->show();
    ui->pass->hide();
    ui->deleteReviewed->hide();

    manageMember = new QSqlTableModel(this);
    manageMember->setTable("UserInfo");
    ui->tableView->setModel(manageMember);
    manageMember->setFilter("IsAd=0");
    manageMember->select();
    manageMember->setHeaderData(0,Qt::Horizontal,"用户名");
    manageMember->setHeaderData(1,Qt::Horizontal,"密码");
    manageMember->setHeaderData(2,Qt::Horizontal,"注册日期");
    manageMember->setHeaderData(3,Qt::Horizontal,"上次登出时间");
    manageMember->setHeaderData(4,Qt::Horizontal,"个性签名");
    manageMember->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnWidth(2,200);
    ui->tableView->setColumnWidth(3,200);
}

void MainWindow::on_deleteUser_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndexList delelist = selection->selectedRows();
    for(int i(0);i<delelist.size();i++){
        manageMember->removeRow(delelist.at(i).row());
    }
    delete selection;
}

void MainWindow::on_yes_clicked()
{
    manageMember->submitAll();
}

void MainWindow::on_no_clicked()
{
    manageMember->revertAll();
    manageMember->submitAll();
}

void MainWindow::on_find_clicked()
{
    QString mes = ui->findframe->text();
    if(mes!=""){
        QString filter = QString("UserName='"+mes+"'AND IsAd=0");
        manageMember->setFilter(filter);
    }
    manageMember->select();
}

void MainWindow::on_reviewed_clicked()
{
    ui->deleteUser->hide();
    ui->findframe->hide();
    ui->find->hide();
    ui->pass->hide();
    ui->deleteReviewed->show();
    manageMember = new QSqlTableModel(this);
    manageMember->setTable("Moment");
    ui->tableView->setModel(manageMember);
    manageMember->setFilter("IsReview=1");
    manageMember->select();
    manageMember->setHeaderData(0,Qt::Horizontal,"用户名");
    manageMember->setHeaderData(1,Qt::Horizontal,"发布日期");
    manageMember->setHeaderData(2,Qt::Horizontal,"正文内容");
    manageMember->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,600);
}

void MainWindow::on_deleteReviewed_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndexList delelist = selection->selectedRows();
    for(int i(0);i<delelist.size();i++){
        manageMember->removeRow(delelist.at(i).row());
    }
    delete selection;
}

void MainWindow::on_review_clicked()
{
    ui->deleteUser->hide();
    ui->findframe->hide();
    ui->find->hide();
    ui->deleteReviewed->hide();
    ui->pass->show();
    manageMember = new QSqlTableModel(this);
    manageMember->setTable("Moment");
    ui->tableView->setModel(manageMember);
    manageMember->setFilter("IsReview=0");
    manageMember->select();
    manageMember->setHeaderData(0,Qt::Horizontal,"用户名");
    manageMember->setHeaderData(1,Qt::Horizontal,"发布日期");
    manageMember->setHeaderData(2,Qt::Horizontal,"正文内容");
    manageMember->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnWidth(1,200);
}

void MainWindow::on_pass_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndexList delelist = selection->selectedRows();
    for(int i(0);i<delelist.size();i++){
        QVariant value = 1;
        manageMember->setData(manageMember->index(delelist.at(i).row(),3),value);
    }
    delete selection;
}

void MainWindow::on_changePwd_clicked()
{
    ChangePwd cp;
    cp.exec();
}
