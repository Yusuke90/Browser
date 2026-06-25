#include "apitesterwidget.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QMessageBox>

ApiTesterWidget::ApiTesterWidget(QWidget *parent):QWidget(parent)
{
    m_methodBox = new QComboBox(this);
    m_methodBox->addItem("GET");
    m_methodBox->addItem("POST");

    m_urlEdit = new QLineEdit(this);

    m_bodyEdit = new QTextEdit(this);

    m_responseEdit = new QTextEdit(this);
    m_responseEdit->setReadOnly(true);

    m_sendButton = new QPushButton("Send", this);

    m_networkManager = new QNetworkAccessManager(this);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(m_methodBox);
    layout->addWidget(m_urlEdit);
    layout->addWidget(m_bodyEdit);
    layout->addWidget(m_sendButton);
    layout->addWidget(m_responseEdit);

    setLayout(layout);

    connect(
        m_sendButton,
        &QPushButton::clicked,
        this,
        &ApiTesterWidget::sendRequest
        );
}

 void ApiTesterWidget::sendRequest()
    {
        QUrl url = QUrl::fromUserInput(m_urlEdit->text());

        if (!url.isValid())
        {
            QMessageBox::warning(
                this,
                "Invalid URL",
                "Please enter a valid URL."
                );
            return;
        }

        QNetworkRequest request(url);

        QNetworkReply *reply = nullptr;

        if (m_methodBox->currentText() == "GET")
        {
            reply = m_networkManager->get(request);
        }
        else
        {
            request.setHeader(
                QNetworkRequest::ContentTypeHeader,
                "application/json"
                );

            reply = m_networkManager->post(
                request,
                m_bodyEdit->toPlainText().toUtf8()
                );
        }

        connect(
            reply,
            &QNetworkReply::finished,
            this,
            [this, reply]()
            {
                handleReply(reply);
            }
            );
    }

void ApiTesterWidget::handleReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        m_responseEdit->setPlainText(reply->errorString());
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();

    QJsonParseError error;

    QJsonDocument document =
        QJsonDocument::fromJson(data, &error);

    if (error.error == QJsonParseError::NoError)
    {
        m_responseEdit->setPlainText(
            document.toJson(QJsonDocument::Indented)
            );
    }
    else
    {
        m_responseEdit->setPlainText(data);
    }

    reply->deleteLater();
}