#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QRegularExpression>

class Calculator : public QWidget {
    Q_OBJECT
public:
    explicit Calculator(QLineEdit *targetField, QWidget *parent = nullptr);

private slots:
    void onButtonClicked();

private:
    QLineEdit *display;
    QLineEdit *target;
    QString validateAndFormat(const QString &text);
};

#endif // CALCULATOR_H
