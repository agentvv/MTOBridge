
#include <QtWidgets>
#include "addressbook.h"

AddressBook::AddressBook(QWidget *parent)
    : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;
    nameLine->setReadOnly(false);
    QLabel *addressLabel = new QLabel(tr("Address:"));
    addressText = new QTextEdit;
    addressText->setReadOnly(false);
    addButton = new QPushButton(tr("&Add"));
    nextButton = new QPushButton(tr("&Next"));
    nextButton->setEnabled(false);
    previousButton = new QPushButton(tr("&Previous"));
    previousButton->setEnabled(false);

    loadButton = new QPushButton(tr("&Load..."));
//! [tooltip 1]
    loadButton->setToolTip(tr("Load contacts from a file"));
//! [tooltip 1]
    saveButton = new QPushButton(tr("&Save..."));
//! [tooltip 2]
    saveButton->setToolTip(tr("Save contacts to a file"));
//! [tooltip 2]
    saveButton->setEnabled(false);


    connect(addButton, &QPushButton::clicked,
            this, &AddressBook::addContact);
    connect(nextButton, &QPushButton::clicked,
            this, &AddressBook::next);
    connect(previousButton, &QPushButton::clicked,
            this, &AddressBook::previous);
    connect(loadButton, &QPushButton::clicked,
            this, &AddressBook::loadFromFile);
    connect(saveButton, &QPushButton::clicked,
            this, &AddressBook::saveToFile);

    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(loadButton);
    buttonLayout1->addWidget(saveButton);
    buttonLayout1->addStretch();

    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameLine, 0, 1);
    mainLayout->addWidget(addressLabel, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(addressText, 1, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);
    mainLayout->addLayout(buttonLayout2, 2, 1);

    setLayout(mainLayout);
    setWindowTitle(tr("Simple Address Book"));
}

void AddressBook::addContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();



    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if (name.isEmpty() || address.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a name and address."));
        return;
    }


    if (!contacts.contains(name)) {
        contacts.insert(name, address);
        QMessageBox::information(this, tr("Add Successful"),
            tr("\"%1\" has been added to your address book.").arg(name));
    } else {
        QMessageBox::information(this, tr("Add Unsuccessful"),
            tr("Sorry, \"%1\" is already in your address book.").arg(name));
    }

    if (contacts.isEmpty()) {
        nameLine->clear();
        addressText->clear();
    }



    addButton->setEnabled(true);

    int number = contacts.size();

    nextButton->setEnabled(number > 1);
    previousButton->setEnabled(number > 1);



    loadButton->setEnabled(true);
    saveButton->setEnabled(number >= 1);

}



void AddressBook::next()
{
    QString name = nameLine->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if (i != contacts.end())
        i++;

    if (i == contacts.end())
        i = contacts.begin();

    nameLine->setText(i.key());
    addressText->setText(i.value());
}

void AddressBook::previous()
{
    QString name = nameLine->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if (i == contacts.end()) {
        nameLine->clear();
        addressText->clear();
        return;
    }

    if (i == contacts.begin())
        i = contacts.end();

    i--;
    nameLine->setText(i.key());
    addressText->setText(i.value());
}


//! [saveToFile() function part1]
void AddressBook::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Address Book"), "",
        tr("Address Book (*.abk);;All Files (*)"));

//! [saveToFile() function part1]
//! [saveToFile() function part2]
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

//! [saveToFile() function part2]
//! [saveToFile() function part3]
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << contacts;
    }
}
//! [saveToFile() function part3]

//! [loadFromFile() function part1]
void AddressBook::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Address Book"), "",
        tr("Address Book (*.abk);;All Files (*)"));
//! [loadFromFile() function part1]

//! [loadFromFile() function part2]
    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        contacts.clear();   // clear existing contacts
        in >> contacts;
//! [loadFromFile() function part2]

//! [loadFromFile() function part3]
        if (contacts.isEmpty()) {
            QMessageBox::information(this, tr("No contacts in file"),
                tr("The file you are attempting to open contains no contacts."));
        } else {
            QMap<QString, QString>::iterator i = contacts.begin();
            nameLine->setText(i.key());
            addressText->setText(i.value());
        }
    }


}
//! [loadFromFile() function part3]
