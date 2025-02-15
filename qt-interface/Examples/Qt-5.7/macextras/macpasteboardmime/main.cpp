/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtMacExtras module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QWidget>

#include <qmacpasteboardmime.h>

class VCardMime : public QMacPasteboardMime
{
public:
    VCardMime() : QMacPasteboardMime(MIME_ALL)
    { }

    QString convertorName()
    {
        return QString("VCardMime");
    }

    bool canConvert(const QString &mime, QString flav)
    {
        return mimeFor(flav) == mime;
    }

    QString mimeFor(QString flav)
    {
        if (flav == QString("public.vcard"))
            return QString("application/x-mycompany-VCard");
        return QString();
    }

    QString flavorFor(const QString &mime)
    {
        if (mime == QString("application/x-mycompany-VCard"))
            return QString("public.vcard");
        return QString();
    }

    QVariant convertToMime(const QString &mime, QList<QByteArray> data, QString flav)
    {
        Q_UNUSED(mime);
        Q_UNUSED(flav);

        QByteArray all;
        foreach (QByteArray i, data) {
            all += i;
        }
        return QVariant(all);
    }

    QList<QByteArray> convertFromMime(const QString &mime, QVariant data, QString flav)
    {
        Q_UNUSED(mime);
        Q_UNUSED(data);
        Q_UNUSED(flav);
        // Todo: implement!
        return QList<QByteArray>();
    }

};

class TestWidget : public QWidget
{
public:
    TestWidget() : QWidget(0)
    {
        vcardMime = new VCardMime();
        setAcceptDrops(true);
    }

    ~TestWidget()
    {
        delete vcardMime;
    }

    void dragEnterEvent(QDragEnterEvent *e)
    {
        e->accept();

    }

    virtual void dropEvent(QDropEvent *e)
    {
        e->accept();
        contentsDropEvent(e);
    }

    void contentsDropEvent(QDropEvent* e)
    {
        if ( e->mimeData()->hasFormat( "application/x-mycompany-VCard" ) )
        {
            QString s = QString( e->mimeData()->data( "application/x-mycompany-VCard" ) );

            // s now contains text of vcard
            qDebug() << "got vcard" << s.count();

            e->acceptProposedAction();
        }
    }
private:
    VCardMime *vcardMime;
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    qRegisterDraggedTypes(QStringList() << QLatin1String("public.vcard"));

    TestWidget wid1;
    wid1.show();

    return app.exec();
}
