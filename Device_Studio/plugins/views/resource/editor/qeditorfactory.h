#ifndef QEDITORFACTORY_H
#define QEDITORFACTORY_H

#include <QObject>
#include <QStringList>

class QAbstractFileEditor;

class EditorInfo
{
public:
    QStringList m_supportList;
    QMetaObject m_metaObject;
};

class QEditorFactory
{
public:
    static void    registerEditor(const QStringList & supportList,
                           QMetaObject  meta);

    static QAbstractFileEditor * createEditor(const QString & type);

    static void    registerInnerEditor();
protected:
    static QList<EditorInfo>       m_editorInfo;
};

#endif // QEDITORFACTORY_H
