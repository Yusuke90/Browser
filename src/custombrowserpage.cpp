#include "custombrowserpage.h"
#include <QWebEngineProfile>
#include <QWebEngineCertificateError>

CustomBrowserPage::CustomBrowserPage(QWebEngineProfile *profile, QWidget *parent)
    : QWebEnginePage(profile, nullptr)
{
    Q_UNUSED(parent)
}
QWebEnginePage *CustomBrowserPage::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type)
    // Block the popup and notify MainWindow via signal
    emit popupBlocked(requestedUrl());
    return nullptr; // returning nullptr = popup is blocked
}