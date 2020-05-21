#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication2.h"
#include <qtextedit.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <regex>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <QTextStream>
#include <string>
#include <qlineedit.h>
#include "sqlite3.h"

class QtGuiApplication2 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication2(QWidget *parent = Q_NULLPTR);

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
private:
	Ui::QtGuiApplication2Class ui;
	QLineEdit *article_title = new QLineEdit();
	QLineEdit *genders = new QLineEdit;
	QLineEdit *max_age = new QLineEdit;
	QLineEdit *min_age = new QLineEdit;
	QLineEdit *nationality = new QLineEdit;
	QLineEdit *participants_nr = new QLineEdit;
	QLineEdit *sd = new QLineEdit;
	QLineEdit *type = new QLineEdit;
	QLineEdit *variables = new QLineEdit;
};
