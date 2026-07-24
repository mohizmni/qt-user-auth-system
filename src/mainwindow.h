#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QIntValidator>
#include <QCryptographicHash>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class SignInWindow;
class SignUpWindow;

class SignUpWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLineEdit *username;
    QLineEdit *password;
    QLineEdit *fullname;
    QLineEdit *email;
    QLineEdit *age;
    QComboBox *gender;

public:
    SignUpWindow(QWidget *parent = nullptr) : QMainWindow(parent){
        setWindowTitle("Sign Up");
        resize (300, 350);

        auto *layout = new QVBoxLayout;
        auto *widget = new QWidget;
        widget->setLayout(layout);
        setCentralWidget(widget);

        layout->addWidget(new QLabel("username: "));
        username = new QLineEdit(this);
        layout->addWidget(username);

        layout->addWidget(new QLabel("Password: "));
        password = new QLineEdit(this);
        password->setEchoMode(QLineEdit::Password);
        layout->addWidget(password);

        layout->addWidget(new QLabel("Full Name: "));
        fullname = new QLineEdit(this);
        layout->addWidget(fullname);

        layout->addWidget(new QLabel("Email: "));
        email = new QLineEdit (this);
        layout->addWidget(email);
        
        layout->addWidget(new QLabel("Age: "));
        age = new QLineEdit(this);
        QIntValidator *validator = new QIntValidator(0, 100, this);
        age->setValidator(validator);
        layout->addWidget(age);

        layout->addWidget(new QLabel("Gender: "));
        //gender combobox or QRadioButton
        gender = new QComboBox(this);
        gender->addItem("Male");
        gender->addItem("Female");
        layout->addWidget(gender);

        QPushButton *confirmButton = new QPushButton("Confirm", this);
        layout->addWidget(confirmButton);

        connect(confirmButton, &QPushButton::clicked, this, &SignUpWindow::confirm);
    }
private slots:
    void confirm(){
        QString Susername = username->text();
        QString Spassword = password->text();
        QString Sfullname = fullname->text();
        QString Semail = email->text();
        QString Sage = age->text();
        QString Sgender = gender->currentText();

    //Hash Password:
        QByteArray hashedPassword = QCryptographicHash::hash(Spassword.toUtf8(), QCryptographicHash::Sha256).toHex();
    //Save to fike:
        QFile file("user.txt");
        if(file.open(QIODevice::Append | QIODevice::Text)){
            QTextStream out (&file);
            out << Susername <<","<< hashedPassword <<","<< Sfullname <<","<< Semail
                <<"," << Sage <<","<< Sgender << "\n";
                // endl is undeclared ;
            file.close();
            QMessageBox::information(this, "Signed IN" ,"Successfully");
            close();//close signup window
        } else{
            QMessageBox::warning(this, "Erro" ," error occurded");
        }
    }

};

class SignInWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLineEdit *username;
    QLineEdit *password;

public:
    SignInWindow(QWidget *parent = nullptr) : QMainWindow(parent){
        setAttribute(Qt::WA_DeleteOnClose);
        setWindowTitle("Sign In");
        resize(300,200);

        auto *layout = new QVBoxLayout;
        auto *widget = new QWidget;
        widget->setLayout(layout);
        setCentralWidget(widget);

        layout->addWidget(new QLabel("Username: "));
        username = new QLineEdit(this);
        layout->addWidget(username);

        layout->addWidget(new QLabel("Password: "));
        password = new QLineEdit(this);
        password->setEchoMode(QLineEdit::Password);
        layout->addWidget(password);

        QPushButton *loginButton = new QPushButton("Login" , this);
        layout ->addWidget(loginButton);
        connect (loginButton , &QPushButton::clicked, this ,&SignUp::login);

        QPushButton *clearButton = new QPushButton("Clear" ,this);
        layout->addWidget(clearButton);
        connect(clearButton, &QPushButton::clicked, this, &SignUp::clear);

    }
private slots:
    void login(){
        QString Susername = username->text();//get the text from user
        QString Spassword = password->text();

        //hash
        QByteArray hashedPassword = QCryptographicHash::hash(Spassword.toUtf8(), QCryptographicHash::Sha256).toHex();
        QFile file("user.txt");
        if(file.open(QIODevice::ReadOnly| QIODevice:: Text)){
            QTextStream in(&file);
            QString line;
            bool logined = false;

            while(in.readLineInto(&line)){
                QStringList info = line.split(",");//split line info ,
                if(info.size() >= 2){
                    QString storedusername = info[0];
                    QString storedpassword = info[1];

                    if(Susername == storedusername && hashedPassword == storedpassword){
                        logined =true;
                        break;
                    }
                }
            }
            file.close();

            if(logined){
                QMessageBox::information(this , "success", "login successfully");
                close();
            } else {
                QMessageBox::warning(this, "error" ,"invalid inpit");
            }
        } else {
            QMessageBox::warning(this , "Error", "file is not opened");
        }
    }

    void clear(){
        username->setText("");
        password->setText("");
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr):QMainWindow(parent) {
        setWindowTitle("Welcome");
        resize(250,200);

        auto *layout = new QVBoxLayout;
        auto *widget = new QWidget;
        widget->setLayout(layout);
        setCentralWidget(widget);

        QLabel *title  =new QLabel ("User Management System" , this);
        title->setStyleSheet("font-size: 24px; font-weight: bold; color: blue;");
        layout->addWidget(title);

        QPushButton *signinButton = new QPushButton("Sign In" , this);
        signinButton->setStyleSheet("background-color: green ; color: white;");
        layout->addWidget(signinButton);
        connect(signinButton, &QPushButton::clicked, this, &MainWindow::openSignInWindow);

        QPushButton *signupButton = new QPushButton("Sign UP" , this);
        signupButton->setStyleSheet("background-color: blue; color: white;");
        layout->addWidget(signupButton);
        connect(signupButton, &QPushButton::clicked, this, &MainWindow::openSignUPWindow);
    }
    ~MainWindow();
private slots:
    void openSignInWindow()
    {
        SignInWindow *signin = new SignInWindow(this);
        signin->show();
    }

    void openSignUPWindow()
    {
        SignUpWindow *signup = new SignUpWindow(this);
        signup->show();
    }
private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
