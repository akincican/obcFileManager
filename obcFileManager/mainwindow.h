#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    class obcfileInfo{                                      //this class contains location of first byte, size and the file name of compressed file inside the obc file
    public:
        int startIndex;
        int size;
        QString fileName;

    };

    obcfileInfo inf[100];
    QString filePathforopen;

    QString fileNameofPath(QString file_path);                                          //returns file name from filepath
    QByteArray compressFileName(QString file_path);                                     //returns qcompressed filename bytearray from filepath
    QByteArray compressFile(QString file_path);                                         //returns qcompressed rawdata bytearray from filepath
    QString uncompressFileName(QByteArray compressedFileName);                          //returns original file name as QString from compressed file name QByteArray
    QByteArray quint16toByteArray(quint16 givenNumber);                                 //returns 2byte bytearray from quint16
    QByteArray inttoByteArray(int givenNumber);                                         //returns 4byte bytearray from int
    QByteArray compressedFileName_sz(QByteArray compressedFileName);                    //returns size of bytearray as 2byte quint16 bytearray
    QByteArray compressedFile_sz(QByteArray compressedFile);                            //returns size of bytearray as 4byte int bytearray
    quint16 byteArraytoquint16(QByteArray inputData);                                   //returns quint16 from 2byte bytearray
    quint16 numberofFileDecoder(QString obcFilePath);                                   //returns numberoffile as quint16 value from obc file
    int byteArraytoint(QByteArray inputData);                                           //returns int from 4byte bytearray
    QByteArray partReader(QString filePath, int startingPoint, int size);               //returns specific part of file as QByteArray
    quint16 fileNameSizeDecoder(QString obcFilePath, int startingPoint, int size = 2);  //returns size of filename which is written via compressedFile_sz function
    QString fileNameDecoder(QString obcFilePath, int startingPoint, int size);          //returns original filename as a qstring from compreesed file name data that located specific point in a obc file
    int fileSizeDecoder(QString obcFilePath, int startingPoint, int size = 4);          //returns size of compressed file data located in obc file as int
    QByteArray fileDecoder(QString obcFilePath, int startingPoint, int size);           //returns uncompressed raw file data as QByteArray

private slots:
    void on_addFileButton_clicked();                                                    //Add File at Create Tab
    void on_removeFileButton_clicked();                                                 //Remove File at Create Tab
    void on_createButton_clicked();                                                     //Create OBC File at Create Tab
    void on_openFileButton_clicked();                                                   //open obc file at Extract Tab
    void on_extractButton_clicked();                                                    //extract at Extract Tab
    void on_extractAllButton_clicked();                                                 //extract all at Extract Tab

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
