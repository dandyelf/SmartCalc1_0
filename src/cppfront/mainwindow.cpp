#include "credit.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  //  Кнопки с цифрами
  connect(ui->push_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->push_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->push_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->push_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->push_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->push_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->push_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->push_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->push_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->push_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  //  Кнопка Х
  connect(ui->push_X, SIGNAL(clicked()), this, SLOT(x_button_push()));
  //  Рабочие кнопки
  connect(ui->push_AC, SIGNAL(clicked()), this, SLOT(AC_button()));
  connect(ui->push_ravno, SIGNAL(clicked()), this, SLOT(equals_button()));
  connect(ui->push_graf, SIGNAL(clicked()), this, SLOT(graf_button()));
  //  Тригонометрия
  connect(ui->push_cos, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->push_sin, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->push_tan, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->push_acos, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->push_asin, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->push_atan, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->push_log, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->push_ln, SIGNAL(clicked()), this, SLOT(func_button()));
  connect(ui->push_sqrt, SIGNAL(clicked()), this, SLOT(func_button()));
  //  Простые операции
  connect(ui->push_plus, SIGNAL(clicked()), this, SLOT(simp_math_button()));
  connect(ui->push_minus, SIGNAL(clicked()), this, SLOT(simp_math_button()));
  connect(ui->push_mult, SIGNAL(clicked()), this, SLOT(simp_math_button()));
  connect(ui->push_div, SIGNAL(clicked()), this, SLOT(simp_math_button()));
  connect(ui->push_mod, SIGNAL(clicked()), this, SLOT(simp_math_button()));
  connect(ui->push_stepen, SIGNAL(clicked()), this, SLOT(simp_math_button()));
  //  Скобки
  connect(ui->push_leftscob, SIGNAL(clicked()), this, SLOT(skobki()));
  //  Точка
  connect(ui->push_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  //  Input lines

  connect(ui->line_Y_from, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(on_line_Y_to_cursorPositionChanged()));
  connect(ui->line_Y_to, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(on_line_Y_to_cursorPositionChanged()));

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::x_button_push() {

  QPushButton *button = (QPushButton *)sender();

  QString new_lable;

  QByteArray ba = (ui->result_code->text()).toLocal8Bit();

  const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

  int validfunc = valid_func(c_str2); //  Валидация операции

  if (ui->result2->text() == "0" && validfunc) {

    ui->result2->setText(button->text());

    ui->result_code->setText(button->text());

  } else if (validfunc) {

    new_lable = ui->result2->text() + button->text();

    ui->result2->setText(new_lable);

    new_lable = ui->result_code->text() + button->text();

    ui->result_code->setText(new_lable);
  }
}

void MainWindow::digits_numbers() {

  QPushButton *button = (QPushButton *)sender();

  QString new_lable;

  QByteArray ba = (ui->result_code->text()).toLocal8Bit();

  const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

  int validfunc = valid_nums(c_str2); //  Валидация чисел

  if(validfunc && button->text() == ".") {

    validfunc = valid_dot(c_str2);

    }

  if (ui->result2->text() == "0" && validfunc) {

    ui->result2->setText(button->text());

    ui->result_code->setText(button->text());

  } else if (validfunc){

    new_lable = ui->result2->text() + button->text();

    ui->result2->setText(new_lable);

    new_lable = ui->result_code->text() + button->text();

    ui->result_code->setText(new_lable);
  }
}

//  Умные скобки, ставится та скобка, которая должна быть
void MainWindow::skobki() {

  QString new_lable;

//  Преобразование в str* для СИ
  QByteArray ba = (ui->result_code->text()).toLocal8Bit();

  const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

  int valid_line = smart_bracket(c_str2); //  Валидация скобки

  if (valid_line == TRUE) { //  Если валидация вернула Тру, ставим закрывающую
    new_lable = ')';
  } else if (valid_line == FALSE) { //  Если Фолс, открывающую
    new_lable = '(';
  }

  //  Если Эррор, установка скобки запрещена
  if (ui->result2->text() == "0" && valid_line != ERROR) {

//  Запись в строку для передачи в бэкЭнд
    ui->result_code->setText(new_lable);

    ui->result2->setText(new_lable); //  Запись для вывода на экран

  } else if (valid_line != ERROR) {
    //  Запись в строку для передачи в бэкЭнд
    ui->result_code->setText(
        ui->result_code->text() + new_lable);

 //  Запись для вывода на экран
    ui->result2->setText(ui->result2->text() + new_lable);

  }
}

void MainWindow::AC_button() {

  QString new_lable = "0";

  ui->result2->setText(new_lable);

  ui->result_code->setText(new_lable);

  ui->widget_graf->replot();
}

void MainWindow::equals_button() {

  QByteArray ba = (ui->result_code->text()).toLocal8Bit();

  const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

  if (ui->result2->text() != "0" && valid_equals(c_str2)) {

    double X = ui->line_X->text().toDouble();

    QByteArray ba = (ui->result_code->text()).toLocal8Bit();

    const char *c_str2 = ba.data();

    double res = start_calc(c_str2, X);

    QString new_lable;

    new_lable = QString::number(res, 'g', 15);

    ui->result2->setText(new_lable);
    ui->result_code->setText(new_lable);
  }
}

void MainWindow::graf_button() {

  QByteArray ba = (ui->result_code->text()).toLocal8Bit();

  const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

  if (ui->result2->text() != '0' && valid_equals(c_str2)) {

    QByteArray ba = (ui->result_code->text()).toLocal8Bit();
    const char *c_str2 = ba.data();

    h = 0.3;
    xBegin = ui->line_X_from->text().toDouble();
    xEnd = ui->line_X_to->text().toDouble();
    double Y_from = ui->line_Y_from->text().toDouble();
    double X_from = ui->line_Y_to->text().toDouble();

    ui->widget_graf->xAxis->setRange(xBegin, xEnd);
    ui->widget_graf->yAxis->setRange(Y_from, X_from);
    //    N = (xEnd - xBegin)/h + 2;

    for (X = xBegin; X <= xEnd; X += h) { //  Заполняем координаты
      x.push_back(X);
      y.push_back(start_calc(c_str2, X)); //  Формула для заполнения у
    }
    ui->widget_graf->addGraph();
    ui->widget_graf->graph(0)->addData(x, y);
    ui->widget_graf->replot();
    ui->widget_graf->graph(0)->data()->clear();
    //  Очищаем координаты
    x.clear();
    y.clear();
  }
}

void MainWindow::func_button() {

  QPushButton *button = (QPushButton *)sender();

  QString new_lable;

  QByteArray ba = (ui->result_code->text()).toLocal8Bit();

  const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

  int validfunc = valid_func(c_str2); //  Валидация операции

  if (ui->result2->text() == '0' && validfunc) {

    ui->result2->setText(button->text() + '(');
    ui->result_code->setText(button->whatsThis() + '(');

  } else if (validfunc){

    new_lable = ui->result2->text() + button->text() + '(';

    ui->result2->setText(new_lable);

    new_lable = ui->result_code->text() + button->whatsThis() + '(';

    ui->result_code->setText(new_lable);
  }
}

void MainWindow::simp_math_button() {

  QPushButton *button = (QPushButton *)sender();

  QString new_lable;

  QByteArray ba = (ui->result_code->text()).toLocal8Bit();

  const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

  int valid;

  valid = valid_simp_oper(c_str2); //  Валидация операции

  if(!valid && (button->text() == '-' || button->text() == '+')) {

    valid = valid_unar(c_str2);

  }

  if (ui->result2->text() == '0' && valid) {

    ui->result2->setText(button->text());

    ui->result_code->setText(button->whatsThis());

  } else if(valid) {

    new_lable = ui->result2->text() + button->text();

    ui->result2->setText(new_lable);

    new_lable = ui->result_code->text() + button->whatsThis();

    ui->result_code->setText(new_lable);
  }
}

void MainWindow::on_cred_Button_clicked()
{
    Credit credit_okno;
    credit_okno.setModal(true);
    credit_okno.exec();
}

void MainWindow::on_line_X_cursorPositionChanged()
{
    QByteArray ba = (ui->line_X->text()).toLocal8Bit();

    const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

    int valid;

    valid = super_valid(1000000, -1000000, c_str2); //  Валидация операции

    if(valid) {

        QString new_lable = ui->line_X->text();

        ui->line_X_bac->setText(new_lable);

    } else {

        QString new_lable = ui->line_X_bac->text();

        ui->line_X->setText(new_lable);

    }
}

void MainWindow::on_line_X_from_cursorPositionChanged()
{
    QByteArray ba = (ui->line_X_from->text()).toLocal8Bit();

    const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

    int valid;

    valid = super_valid(1000000, -1000000, c_str2); //  Валидация операции

    if(valid) {

        QString new_lable = ui->line_X_from->text();

        ui->line_X_from_bac->setText(new_lable);

    } else {

        QString new_lable = ui->line_X_from_bac->text();

        ui->line_X_from->setText(new_lable);

    }
}

void MainWindow::on_line_X_to_cursorPositionChanged()
{
    QByteArray ba = (ui->line_X_to->text()).toLocal8Bit();

    const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

    int valid;

    valid = super_valid(1000000, -1000000, c_str2); //  Валидация операции

    if(valid) {

        QString new_lable = ui->line_X_to->text();

        ui->line_X_to_bac->setText(new_lable);

    } else {

        QString new_lable = ui->line_X_to_bac->text();

        ui->line_X_to->setText(new_lable);

    }
}

void MainWindow::on_line_Y_from_cursorPositionChanged()
{
    QByteArray ba = (ui->line_Y_from->text()).toLocal8Bit();

    const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

    int valid;

    valid = super_valid(1000000, -1000000, c_str2); //  Валидация операции

    if(valid) {

        QString new_lable = ui->line_Y_from->text();

        ui->line_Y_from_bac->setText(new_lable);

    } else {

        QString new_lable = ui->line_Y_from_bac->text();

        ui->line_Y_from->setText(new_lable);

    }
}



void MainWindow::on_line_Y_to_cursorPositionChanged()
{
    QByteArray ba = (ui->line_Y_to->text()).toLocal8Bit();

    const char *c_str2 = ba.data(); //  Преобразование в str* для СИ

    int valid;

    valid = super_valid(1000000, -1000000, c_str2); //  Валидация операции

    if(valid) {

        QString new_lable = ui->line_Y_to->text();

        ui->line_Y_to_bac->setText(new_lable);

    } else {

        QString new_lable = ui->line_Y_to_bac->text();

        ui->line_Y_to->setText(new_lable);

    }
}
