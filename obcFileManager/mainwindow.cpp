#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::fileNameofPath(QString file_path){

    QFile file(file_path);
    QFileInfo fileInfo(file.fileName());
    QString filename(fileInfo.fileName());

    return filename;

}
QByteArray MainWindow::compressFileName(QString file_path){

    QString filename =fileNameofPath(file_path);
    int filename_sz = filename.length();
    QByteArray ba;
    ba.reserve(filename_sz);
    ba.append(filename.toLatin1());



    QByteArray compressedba = qCompress(ba);
    return compressedba;


}
QByteArray MainWindow::compressFile(QString file_path){


    QFile file(file_path);
    int sz = file.size();
    file.open(QIODevice::ReadOnly);
    QByteArray ba;
    ba.reserve(sz);
    ba = file.readAll();
    file.close();




    QByteArray compressedba = qCompress(ba);
    return compressedba;


}
QString MainWindow::uncompressFileName(QByteArray compressedFileName){

    QByteArray temp = qUncompress(compressedFileName);
    QString uncompressFileName = QString::fromLatin1(temp);
    return uncompressFileName;
}
QByteArray MainWindow::quint16toByteArray(quint16 givenNumber){

    QByteArray ba_quint16;
    ba_quint16.resize(2);
    memcpy(ba_quint16.data(), &givenNumber,2);

    return ba_quint16;

}
QByteArray MainWindow::inttoByteArray(int givenNumber){

    QByteArray ba_int;
    ba_int.resize(4);
    memcpy(ba_int.data(), &givenNumber,4);

    return ba_int;

}
QByteArray MainWindow::compressedFileName_sz(QByteArray compressedFileName){


    quint16 sayi = compressedFileName.size();

    QByteArray sayiarrayi = quint16toByteArray(sayi);

    return sayiarrayi;

}
QByteArray MainWindow::compressedFile_sz(QByteArray compressedFile){


    int sayi = compressedFile.size();

    QByteArray sayiarrayi = inttoByteArray(sayi);

    return sayiarrayi;

}
quint16  MainWindow::byteArraytoquint16(QByteArray inputData){

    quint16  cikti;
    memcpy(&cikti, inputData.data(), 2);

    return cikti;

}
quint16 MainWindow::numberofFileDecoder(QString obcFilePath){


    QFile file(obcFilePath);
    file.open(QIODevice::ReadOnly);
    QByteArray temp;
    temp.resize(2);

    temp =file.read(2);

    quint16  numberofFile = byteArraytoquint16(temp);

    return numberofFile;





}
int  MainWindow::byteArraytoint(QByteArray inputData){

    int  cikti;
    memcpy(&cikti, inputData.data(), 4);

    return cikti;

}
QByteArray MainWindow::partReader(QString filePath,int startingPoint, int size ){

    QFile file_2(filePath);
    file_2.open(QIODevice::ReadOnly);
    QByteArray output;
    output.resize(size);
    file_2.seek(startingPoint);
    output = file_2.read(size);
    file_2.close();

    return output;
}
quint16 MainWindow::fileNameSizeDecoder(QString obcFilePath,int startingPoint, int size){

    QByteArray temp = partReader(obcFilePath, startingPoint,size);
    quint16  numberofFile = byteArraytoquint16(temp);

    return numberofFile;





}
QString MainWindow::fileNameDecoder(QString obcFilePath,int startingPoint, int size){

    QByteArray temp = partReader(obcFilePath,startingPoint, size) ;
    QString fileName = qUncompress(temp);
    return fileName;
}
int MainWindow::fileSizeDecoder(QString obcFilePath,int startingPoint, int size){

    int fileSize =byteArraytoint(partReader(obcFilePath,startingPoint,size));

    return fileSize;
}
QByteArray MainWindow::fileDecoder(QString obcFilePath,int startingPoint, int size){

    QByteArray temp = partReader(obcFilePath,startingPoint, size) ;
    QByteArray file = qUncompress(temp);
    return file;
}



void MainWindow::on_addFileButton_clicked()   //Add File
{
    QStringList file_names = QFileDialog::getOpenFileNames(this, "Open a file", QDir::homePath());
    ui->listWidget->addItems(file_names);

}

void MainWindow::on_removeFileButton_clicked()  //Remove File
{

    QList <QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }


}

void MainWindow::on_createButton_clicked() //Create OBC File
{

    quint16 numberofFile = ui->listWidget->count();
    QString paths_of_files[numberofFile];
    QListWidgetItem item;


    if(numberofFile>0){

        QString obcFilePath = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),"OBC File, (*.obc)");
        for(int i = 0; i < (numberofFile); i++){
            item = *(ui->listWidget->item(i));
            QString path = item.text();
            paths_of_files[i] = path;
        }

        QByteArray numberofFileArray = quint16toByteArray(numberofFile);
        QFile obcFile(obcFilePath);
        obcFile.open(QIODevice::WriteOnly);
        obcFile.write(numberofFileArray);
        obcFile.close();

        obcFile.open(QIODevice::Append);

        for(int i = 0; i < (numberofFile); i++){
            QByteArray compressedFileName = compressFileName(paths_of_files[i]);
            QByteArray compressedFileNameSize = compressedFileName_sz(compressedFileName);
            QByteArray compressedFile = compressFile(paths_of_files[i]);
            QByteArray compressedFileSize = compressedFile_sz(compressedFile);





            obcFile.write(compressedFileNameSize);
            obcFile.write(compressedFileName);
            obcFile.write(compressedFileSize);
            obcFile.write(compressedFile);

        }

        obcFile.close();
    }
}

void MainWindow::on_openFileButton_clicked(){  //open obc file


    filePathforopen = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath(),"OBC Files (*.obc)");
    ui->label_4->setText(fileNameofPath(filePathforopen));

    quint16 numberofFile = numberofFileDecoder(filePathforopen);

    ui->listWidget_5->clear();

    int cursor=2;
    for(int i=0; i<numberofFile; i++){
        quint16 fileNameSize = fileNameSizeDecoder(filePathforopen,cursor);
        cursor = cursor+2;
        inf[i].fileName = fileNameDecoder(filePathforopen,cursor,fileNameSize);
        cursor = cursor+fileNameSize;
        inf[i].size = fileSizeDecoder(filePathforopen,cursor);
        cursor = cursor+4;
        inf[i].startIndex = cursor;
        cursor = cursor+inf[i].size;
        ui->listWidget_5->addItem(inf[i].fileName);

    }



}

void MainWindow::on_extractButton_clicked()  //extract
{
    int index = ui->listWidget_5->currentRow();
    if(index > -1){
        QString extractPath = QFileDialog::getExistingDirectory(this,"Extracting location",QDir::homePath());
        QString extractFileName = extractPath+"/"+inf[index].fileName;

        QFile file(extractFileName);
        file.open(QIODevice::WriteOnly);
        QByteArray filedata = fileDecoder(filePathforopen,inf[index].startIndex,inf[index].size);
        file.write(filedata);
        file.close();

    }
    else{
        QMessageBox::warning(this,"warning","please open a obc file first!");
    }
}

void MainWindow::on_extractAllButton_clicked()  //extract all
{
    QString extractPath = QFileDialog::getExistingDirectory(this,"Extracting location",QDir::homePath());
    quint16 numberofFile = numberofFileDecoder(filePathforopen);


    for(int i= 0; i < numberofFile ;i++){

        QString extractFileName = extractPath+"/"+inf[i].fileName;

        QFile file(extractFileName);
        file.open(QIODevice::WriteOnly);
        QByteArray filedata = fileDecoder(filePathforopen,inf[i].startIndex,inf[i].size);
        file.write(filedata);
        file.close();

    }




}

