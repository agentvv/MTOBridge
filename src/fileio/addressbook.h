// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
#include <QMap>


QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QLineEdit;
class QTextEdit;
QT_END_NAMESPACE


class AddressBook : public QWidget
{
    Q_OBJECT

public:
    AddressBook(QWidget *parent = nullptr);
    enum Mode { NavigationMode, AddingMode, EditingMode };

public slots:
    void addContact();
    void next();
    void previous();
//! [save and load functions declaration]
    void saveToFile();
    void loadFromFile();
//! [save and load functions declaration]

private:
    void updateInterface(Mode mode);

    QPushButton *addButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
//! [save and load buttons declaration]
    QPushButton *loadButton;
    QPushButton *saveButton;
//! [save and load buttons declaration]
    QLineEdit *nameLine;
    QTextEdit *addressText;

    QMap<QString, QString> contacts;
    //FindDialog *dialog;
    QString oldName;
    QString oldAddress;
    Mode currentMode;
};

#endif
