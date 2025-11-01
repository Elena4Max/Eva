#include "calculator.h"
#include <QRegularExpressionValidator>

Calculator::Calculator(QLineEdit *targetField, QWidget *parent)
    : QWidget(parent), target(targetField)
{
    display = new QLineEdit(this);
    display->setAlignment(Qt::AlignRight);
    display->setReadOnly(true);

    QGridLayout *layout = new QGridLayout(this);
    QStringList buttons = {"7","8","9",
                           "4","5","6",
                           "1","2","3",
                           "0",".","C"};

    int pos = 0;
    for (const QString &text : buttons) {
        QPushButton *btn = new QPushButton(text, this);
        layout->addWidget(btn, pos / 3 + 1, pos % 3);
        connect(btn, &QPushButton::clicked, this, &Calculator::onButtonClicked);
        pos++;
    }

    layout->addWidget(display, 0, 0, 1, 3);
    setLayout(layout);
}

QString Calculator::validateAndFormat(const QString &text) {
    QRegularExpression regex(R"(^\d{0,7}(\.\d{0,2})?$)");
    if (regex.match(text).hasMatch())
        return text;
    return display->text();
}

void Calculator::onButtonClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString text = btn->text();
    QString current = display->text();

    if (text == "C") {
        display->clear();
        target->clear();
        return;
    }

    if (text == "." && current.contains('.')) return;
    QString newText = current + text;
    newText = validateAndFormat(newText);
    display->setText(newText);
    target->setText(newText);
}
