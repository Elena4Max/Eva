#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "calculator.h"

double readTotalFromJson(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Could not open JSON file!");
        return 0.0;
    }
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qWarning("Invalid JSON format!");
        return 0.0;
    }

    QJsonArray arr = doc.array();
    double totalSum = 0.0;
    for (const QJsonValue &value : arr) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            totalSum += obj.value("total").toDouble();
        }
    }
    return totalSum;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QWidget w;

    QLabel *top_label = new QLabel("Закриття чека");
    top_label->setAlignment(Qt::AlignCenter);

    QLineEdit *label_bill_amount      = new QLineEdit();
    QLineEdit *label_cash             = new QLineEdit();
    QLineEdit *label_customers_amount = new QLineEdit();
    QLineEdit *label_rest             = new QLineEdit();

    label_bill_amount->setReadOnly(true);
    label_cash->setReadOnly(true);
    label_rest->setReadOnly(true);

    QRegularExpression regex(R"(^\d{0,7}(\.\d{0,2})?$)");
    label_customers_amount->setValidator(new QRegularExpressionValidator(regex));

    double totalSum = readTotalFromJson("data.json");
    label_bill_amount->setText(QString::number(totalSum, 'f', 2));
    label_cash->setText(QString::number(totalSum, 'f', 2));

    QFormLayout *form_layout = new QFormLayout;
    form_layout->addRow("Сума чеку:", label_bill_amount);
    form_layout->addRow("Готівкою:", label_cash);
    form_layout->addRow("Сума клієнта:", label_customers_amount);
    form_layout->addRow("Решта за чеком:", label_rest);

    QPushButton *no_button  = new QPushButton("Відмова");
    QPushButton *yes_button = new QPushButton("Оплатити");
    yes_button->setEnabled(false);

    QHBoxLayout *buttons_layout = new QHBoxLayout();
    buttons_layout->addWidget(no_button);
    buttons_layout->addWidget(yes_button);

    Calculator *calc = new Calculator(label_customers_amount);

    auto updateRest = [&]() {
        QString customerText = label_customers_amount->text();
        if (customerText.isEmpty()) {
            label_rest->clear();
            label_rest->setStyleSheet("");
            yes_button->setEnabled(false);
            return;
        }

        double bill = label_bill_amount->text().toDouble();
        double customer = customerText.toDouble();
        double rest = customer - bill;

        label_rest->setText(QString::number(rest, 'f', 2));

        if (rest >= 0) {
            label_rest->setStyleSheet("background-color: lightgreen;");
            yes_button->setEnabled(true);
        } else if (rest < 0) {
            label_rest->setStyleSheet("background-color: lightcoral;");
            yes_button->setEnabled(false);
        } else { // ровно 0
            label_rest->setStyleSheet("");
            yes_button->setEnabled(true);
        }
    };

    QObject::connect(label_customers_amount, &QLineEdit::textChanged, updateRest);

    QObject::connect(no_button, &QPushButton::clicked, [&]() {
        label_customers_amount->clear();
        label_rest->clear();
        label_rest->setStyleSheet("");
        yes_button->setEnabled(false);

        if (auto display = calc->findChild<QLineEdit*>()) {
            display->clear();
        }
    });

    QObject::connect(yes_button, &QPushButton::clicked, [&]() {
        double bill = label_bill_amount->text().toDouble();
        double customer = label_customers_amount->text().toDouble();
        double rest = label_rest->text().toDouble();

        QString message = QString(
            "Клієнт сплатив: %1 грн\n"
            "Сума чеку: %2 грн\n"
            "Решта: %3 грн")
            .arg(QString::number(customer, 'f', 2))
            .arg(QString::number(bill, 'f', 2))
            .arg(QString::number(rest, 'f', 2));

        QMessageBox::information(&w, "Оплата", message);
    });

    QVBoxLayout *left_layout = new QVBoxLayout;
    left_layout->addLayout(form_layout);
    left_layout->addLayout(buttons_layout);

    QHBoxLayout *main_hbox = new QHBoxLayout;
    main_hbox->addLayout(left_layout);
    main_hbox->addWidget(calc);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addWidget(top_label);
    main_layout->addLayout(main_hbox);

    w.setLayout(main_layout);
    w.setFixedSize(w.sizeHint());

    w.show();
    return a.exec();
}
