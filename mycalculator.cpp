#include "mycalculator.h"
#include "ui_mycalculator.h"
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <iostream>

MyCalculator::MyCalculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyCalculator)
{
    ui->setupUi(this);
    connect(ui->clear, &QPushButton::clicked, this, &MyCalculator::cleaning);
    connect(ui->nb_0, &QPushButton::clicked, this, &MyCalculator::nbr_0);
    connect(ui->nb_1, &QPushButton::clicked, this, &MyCalculator::nbr_1);
    connect(ui->nb_2, &QPushButton::clicked, this, &MyCalculator::nbr_2);
    connect(ui->nb_3, &QPushButton::clicked, this, &MyCalculator::nbr_3);
    connect(ui->nb_4, &QPushButton::clicked, this, &MyCalculator::nbr_4);
    connect(ui->nb_5, &QPushButton::clicked, this, &MyCalculator::nbr_5);
    connect(ui->nb_6, &QPushButton::clicked, this, &MyCalculator::nbr_6);
    connect(ui->nb_7, &QPushButton::clicked, this, &MyCalculator::nbr_7);
    connect(ui->nb_8, &QPushButton::clicked, this, &MyCalculator::nbr_8);
    connect(ui->nb_9, &QPushButton::clicked, this, &MyCalculator::nbr_9);
    connect(ui->divise, &QPushButton::clicked, this, &MyCalculator::division);
    connect(ui->multi, &QPushButton::clicked, this, &MyCalculator::miultiplication);
    connect(ui->moins, &QPushButton::clicked, this, &MyCalculator::soustraction);
    connect(ui->plus, &QPushButton::clicked, this, &MyCalculator::addition);
    connect(ui->equal, &QPushButton::clicked, this, &MyCalculator::equal);
}

MyCalculator::~MyCalculator()
{
    delete ui;
}

void MyCalculator:: addition(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+" + ");
    op="+";
}
void MyCalculator::miultiplication(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+" x ");
    op="x";
}
void MyCalculator::soustraction(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+" - ");
    op="-";
}
void MyCalculator::division(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+" ÷ ");
    op="÷";
}
void MyCalculator::equal() {
    QString value = ui->lineEdit->text();
    value = value.simplified(); // Supprime les espaces en trop

    // Expression régulière pour extraire les nombres et opérateurs
    QRegularExpression regex("(-?\\d+|[-+x÷])"); // Capture les nombres (positifs/négatifs) et les opérateurs
    QRegularExpressionMatchIterator matchIterator = regex.globalMatch(value);

    // Liste pour stocker les nombres et opérateurs
    QList<QString> tokens;
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        tokens.append(match.captured(0));
    }

    // Étape 1 : Résoudre les multiplications et divisions en priorité
    for (int i = 1; i < tokens.size() - 1; i++) {
        QString op = tokens[i];
        if (op == "x" || op == "÷") {
            int left = tokens[i - 1].toInt();
            int right = tokens[i + 1].toInt();

            // Effectuer l'opération
            int intermediateResult;
            if (op == "x") {
                intermediateResult = left * right;
            } else { // op == "÷"
                if (right == 0) {
                    std::cerr << "Erreur : Division par zéro !" << std::endl;
                    ui->lineEdit->setText("Erreur");
                    return;
                }
                intermediateResult = left / right;
            }

            // Remplacer le sous-calcul par son résultat dans la liste
            tokens[i - 1] = QString::number(intermediateResult);
            tokens.removeAt(i);   // Supprimer l'opérateur
            tokens.removeAt(i);   // Supprimer le nombre suivant
            i--; // Reculer l'indice pour réévaluer au cas où il y a une autre priorité
        }
    }

    // Étape 2 : Résoudre les additions et soustractions
    int result = tokens[0].toInt(); // Premier nombre
    for (int i = 1; i < tokens.size(); i += 2) {
        QString op = tokens[i];
        int number = tokens[i + 1].toInt();

        if (op == "+") {
            result += number;
        } else if (op == "-") {
            result -= number;
        }
    }

    // Afficher le résultat
    ui->lineEdit->clear();
    ui->lineEdit->setText(QString::number(result));
}

void MyCalculator::cleaning(){
    ui->lineEdit->clear();
}
void MyCalculator::nbr_0(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"0");
}
void MyCalculator::nbr_1(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"1");
}
void MyCalculator::nbr_2(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"2");
}
void MyCalculator::nbr_3(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"3");
}
void MyCalculator::nbr_4(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"4");
}
void MyCalculator::nbr_5(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"5");
}
void MyCalculator::nbr_6(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"6");
}
void MyCalculator::nbr_7(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"7");
}
void MyCalculator::nbr_8(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"8");
}
void MyCalculator::nbr_9(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"9");
}
