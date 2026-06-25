#pragma once

#include <QWidget>
#include <QNetworkAccessManager>

class QComboBox;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QNetworkReply;

class ApiTesterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ApiTesterWidget(QWidget *parent = nullptr);

private slots:
    void sendRequest();
    void handleReply(QNetworkReply *reply);

private:
    QComboBox *m_methodBox;
    QLineEdit *m_urlEdit;
    QTextEdit *m_bodyEdit;
    QTextEdit *m_responseEdit;
    QPushButton *m_sendButton;

    QNetworkAccessManager *m_networkManager;
};