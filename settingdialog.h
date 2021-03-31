#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include "ui_settingdialog.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
    Ui::SettingDialog *ui;
    QDir *dir;

private slots:
    void startBrowse();
    void saveBrowse();
    void accepting();

signals:
    void setComplete(QString startDirectory,QString fileName,bool isPNG,QString saveDirectory);
};

#endif // SETTINGDIALOG_H
