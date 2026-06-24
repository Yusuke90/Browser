#pragma once

#include <QWebEnginePage>

class CustomBrowserPage : public QWebEnginePage
{
    Q_OBJECT

public:
    explicit CustomBrowserPage(QWebEngineProfile *profile, QWidget *parent = nullptr);

signals:
    void popupBlocked(const QUrl &url);

protected:
    // This is what intercepts popup requests
    QWebEnginePage *createWindow(QWebEnginePage::WebWindowType type) override;
};