/**
 *
 * ==================================================================
 *
 *       @Author : KONAN Kouakou Abel
 *
 * ===================================================================
 *
 *      @pp : Calculator
 *
 * ================================================================
 *
 *      @version 1.0.A
 *
 * =================================================================
 *
 *  ___            ___               ___
 *  |     /--\ |   |    |   |  |    |___
 *  |__  /   \ |__ |__  |___|  |___ |___
 *
 *  =================================================================
 *
 *                CPP
 *
 *  =======================================================
*/




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
    this->setWindowTitle("Calculator");
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
    opr="+";
}
void MyCalculator::miultiplication(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+" x ");
    opr="x";
}
void MyCalculator::soustraction(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+" - ");
    opr="-";
}
void MyCalculator::division(){
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+" ÷ ");
    opr="÷";
}
void MyCalculator::equal() {
    QString value = ui->lineEdit->text();
    value = value.simplified(); // Supprime les espaces en trop

    // Expression régulière pour extraire les nombres (y compris flottants) et opérateurs
    QRegularExpression regex("(-?\\d+(\\.\\d+)?|[-+x÷])"); // Capture les nombres flottants ou entiers, et les opérateurs
    QRegularExpressionMatchIterator matchIterator = regex.globalMatch(value);

    // Liste pour stocker les nombres et opérateurs
    QList<QString> tokens;
    while (matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        tokens.append(match.captured(0));
    }

    // Vérifier que la liste est valide
    if (tokens.isEmpty() || tokens.size() < 3) {
        ui->lineEdit->setText("Erreur");
        return;
    }

    // Étape 1 : Résoudre les multiplications et divisions en priorité
    for (int i = 1; i < tokens.size() - 1; i++) {
        QString op = tokens[i];
        if (op == "x" || op == "÷") {
            double left = tokens[i - 1].toDouble();
            double right = tokens[i + 1].toDouble();

            // Effectuer l'opération
            double intermediateResult;
            if (op == "x") {
                intermediateResult = left * right;
            } else { // op == "÷"
                if (right == 0) {
                    std::cerr << "Erreur : Division par zéro !" << std::endl;
                    ui->lineEdit->setText("Erreur");
                    state=true;
                    opr="";
                    return;
                }
                intermediateResult = left / right;
            }

            // Remplacer le sous-calcul par son résultat dans la liste
            tokens[i - 1] = QString::number(intermediateResult, 'f', 10); // Formate en double
            tokens.removeAt(i);   // Supprimer l'opérateur
            tokens.removeAt(i);   // Supprimer le nombre suivant
            i--; // Reculer l'indice pour réévaluer au cas où il y a une autre priorité
        }
    }

    // Étape 2 : Résoudre les additions et soustractions
    double result = tokens[0].toDouble(); // Premier nombre
    for (int i = 1; i + 1 < tokens.size(); i += 2) {
        QString op = tokens[i];
        double number = tokens[i + 1].toDouble();

        if (op == "+") {
            result += number;
        } else if (op == "-") {
            result -= number;
        }
    }

    // Afficher le résultat (limité à 10 décimales pour éviter les formats trop longs)
    ui->lineEdit->clear();
    ui->lineEdit->setText(QString::number(result, 'f', 10).remove(QRegularExpression("0+$")).remove(QRegularExpression("\\.$"))); // Supprime les zéros inutiles
    state=true;
    opr="";
}


void MyCalculator::cleaning(){
    ui->lineEdit->clear();
}
void MyCalculator::nbr_0(){
    if(state && opr.isEmpty()){
        cleaning();
        state=false;
    }
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"0");
}
void MyCalculator::nbr_1(){
    if(state && opr.isEmpty()){
        cleaning();
        state=false;
    }
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"1");
}
void MyCalculator::nbr_2(){
    if(state && opr.isEmpty()){
        cleaning();
        state=false;
    }
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"2");
}
void MyCalculator::nbr_3(){
    if(state && opr.isEmpty()){
        cleaning();
        state=false;
    }
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"3");
}
void MyCalculator::nbr_4(){
    if(state && opr.isEmpty()){
        cleaning();
        state=false;
    }
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"4");
}
void MyCalculator::nbr_5(){
    if(state && opr.isEmpty()){
        cleaning();
        state=false;
    }
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"5");
}
void MyCalculator::nbr_6(){
    if(state && opr.isEmpty()){
        cleaning();
        state=false;
    }
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"6");
}
void MyCalculator::nbr_7(){
    if(state && opr.isEmpty()){
        cleaning();
        state=false;
    }
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"7");
}
void MyCalculator::nbr_8(){
    if(state && opr.isEmpty()){
        cleaning();
        state=false;
    }
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"8");
}
void MyCalculator::nbr_9(){
    if(state && opr.isEmpty()){
        cleaning();
        state=false;
    }
    operation = ui->lineEdit->text();
    ui->lineEdit->setText(operation+"9");
}
