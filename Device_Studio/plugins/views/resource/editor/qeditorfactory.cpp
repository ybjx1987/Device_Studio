#include "qeditorfactory.h"

#include "qimageeditor.h"

QList<EditorInfo> QEditorFactory::m_editorInfo;

void QEditorFactory::registerEditor(const QStringList &supportList, QMetaObject meta)
{
    EditorInfo info;
    info.m_supportList = supportList;
    info.m_metaObject = meta;

    m_editorInfo.append(info);
}

QAbstractFileEditor * QEditorFactory::createEditor(const QString &type)
{
    foreach(EditorInfo info,m_editorInfo)
    {
        if(info.m_supportList.contains(type))
        {
            QAbstractFileEditor * editor = (QAbstractFileEditor*)info.m_metaObject.newInstance();
            return editor;
        }
    }

    return NULL;
}

void QEditorFactory::registerInnerEditor()
{
    registerEditor(QImageEditor::getSupportFile(),QImageEditor::staticMetaObject);
}
