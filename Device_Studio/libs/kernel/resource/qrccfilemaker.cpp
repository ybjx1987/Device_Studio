#include "qrccfilemaker.h"

#include "qresourcefile.h"

#include <QStack>
#include <QFile>

#define writeString(s) write(s, sizeof(s))


class ResourceFileInfo
{
public:
    ResourceFileInfo(const QString &name=QString(),const QByteArray &a=QByteArray());
    ~ResourceFileInfo();

public:
    qint64  writeDataBlob(QRccFileMaker &maker, qint64 offset);
    qint64  writeDataName(QRccFileMaker &maker, qint64 offset);
    void    writeDataInfo(QRccFileMaker &maker);
public:
    QString     m_name;
    QByteArray  m_data;

    int     m_flags;

    int     m_dataOffset;
    int     m_nameOffset;
    int     m_childOffset;

    ResourceFileInfo *m_parent;
    QHash<QString, ResourceFileInfo*> m_children;
};

ResourceFileInfo::ResourceFileInfo(const QString &name, const QByteArray &a):
    m_name(name),
    m_data(a),
    m_flags(0),
    m_dataOffset(0),
    m_nameOffset(0),
    m_childOffset(0),
    m_parent(NULL)
{

}

ResourceFileInfo::~ResourceFileInfo()
{
    qDeleteAll(m_children);
}

qint64 ResourceFileInfo::writeDataBlob(QRccFileMaker &maker, qint64 offset)
{
    m_dataOffset = offset;

    maker.writeNumber4(m_data.size());
    offset += 4;

    maker.writeByteArray(m_data);
    offset += m_data.size();
    return offset;
}

qint64 ResourceFileInfo::writeDataName(QRccFileMaker &maker, qint64 offset)
{
    m_nameOffset = offset;
    maker.writeNumber2(m_name.length());
    offset += 2;
    maker.writeNumber4(qHash(m_name));
    offset += 4;
    const QChar *unicode = m_name.unicode();
    for (int i = 0; i < m_name.length(); ++i)
    {
        maker.writeNumber2(unicode[i].unicode());
    }
    offset += m_name.length()*2;
    return offset;
}

void ResourceFileInfo::writeDataInfo(QRccFileMaker &maker)
{
    maker.writeNumber4(m_nameOffset);
    maker.writeNumber2(m_flags);
    if (m_flags & 2)
    {

        maker.writeNumber4(m_children.size());
        maker.writeNumber4(m_childOffset);
    }
    else
    {
        maker.writeNumber2(0);
        maker.writeNumber2(1);
        maker.writeNumber4(m_dataOffset);
    }
}

QRccFileMaker::QRccFileMaker():
    m_root(NULL),
    m_resourceFile(NULL)
{
}

QRccFileMaker::~QRccFileMaker()
{
    clear();
}

void QRccFileMaker::clear()
{
    if(m_root!=NULL)
    {
        delete m_root;
        m_root=NULL;
    }
    if(m_resourceFile!=NULL)
    {
        m_resourceFile=NULL;
    }
}

void QRccFileMaker::setResourceFile(QResourceFile *resourceFile)
{
    clear();
    m_resourceFile=resourceFile;
    m_root=new ResourceFileInfo;
    m_root->m_flags=2;
    addData(m_root,resourceFile->getPath(),resourceFile->getData());
}

void QRccFileMaker::addData(ResourceFileInfo *r, QString path, const QByteArray &a)
{
    int index=path.indexOf("/");
    QString str;
    if(index==-1)
    {
        str=path;
    }
    else
    {
        str=path.left(index);
    }
    ResourceFileInfo *c=r->m_children.value(str);
    if(c==NULL)
    {
        c=new ResourceFileInfo(str);
        c->m_parent=r;
        r->m_children.insert(str,c);
        if(str==path)
        {
            c->m_data=a;
            c->m_flags=0;
        }
        else
        {
            c->m_flags=2;
            addData(c,path.mid(index+1),a);
        }
    }
    else
    {
        addData(c,path.mid(index+1),a);
    }
}

void QRccFileMaker::write(const char *str, int len)
{
    --len;
    int n = m_out.size();
    m_out.resize(n + len);
    memcpy(m_out.data() + n, str, len);
}



void QRccFileMaker::writeNumber2(quint16 number)
{
    writeChar(number >> 8);
    writeChar(number);
}

void QRccFileMaker::writeNumber4(quint32 number)
{
    writeChar(number >> 24);
    writeChar(number >> 16);
    writeChar(number >> 8);
    writeChar(number);
}

void QRccFileMaker::writeByteArray(const QByteArray &other)
{
    m_out.append(other);
}

QByteArray QRccFileMaker::rccData()
{
    m_out.clear();
    writeHeader();
    if (m_root) {
        if (!writeDataBlobs())
        {
            goto LOOP;
        }
        if (!writeDataNames())
        {
            goto LOOP;
        }
        if (!writeDataStructure())
        {
            goto LOOP;
        }
    }
    writeInitializer();
    return m_out;
    LOOP:
    m_out.clear();
    return m_out;
}

bool QRccFileMaker::writeHeader()
{
    writeString("qres");
    writeNumber4(0);
    writeNumber4(0);
    writeNumber4(0);
    writeNumber4(0);
    return true;
}

bool QRccFileMaker::writeDataBlobs()
{
    m_dataOffset = m_out.size();
    QStack<ResourceFileInfo*> pending;

    if (!m_root)
        return false;

    pending.push(m_root);
    qint64 offset = 0;
    while (!pending.isEmpty())
    {
        ResourceFileInfo *file = pending.pop();
        for (QHash<QString, ResourceFileInfo*>::iterator it = file->m_children.begin();
            it != file->m_children.end(); ++it)
        {
            ResourceFileInfo *child = it.value();
            if (child->m_flags & 2)
                pending.push(child);
            else
            {
                offset = child->writeDataBlob(*this, offset);
            }
        }
    }
    return true;
}

bool QRccFileMaker::writeDataNames()
{
    m_namesOffset = m_out.size();

    QHash<QString, int> names;
    QStack<ResourceFileInfo*> pending;

    if (!m_root)
        return false;

    pending.push(m_root);
    qint64 offset = 0;
    while (!pending.isEmpty())
    {
        ResourceFileInfo *file = pending.pop();
        for (QHash<QString, ResourceFileInfo*>::iterator it = file->m_children.begin();
            it != file->m_children.end(); ++it)
        {
            ResourceFileInfo *child = it.value();
            if (child->m_flags & 2)
                pending.push(child);
            if (names.contains(child->m_name))
            {
                child->m_nameOffset = names.value(child->m_name);
            }
            else
            {
                names.insert(child->m_name, offset);
                offset = child->writeDataName(*this, offset);
            }
        }
    }
    return true;
}

static bool qt_rcc_compare_hash(const ResourceFileInfo *left, const ResourceFileInfo *right)
{
    return qHash(left->m_name) < qHash(right->m_name);
}

bool QRccFileMaker::writeDataStructure()
{
    m_treeOffset = m_out.size();
    QStack<ResourceFileInfo*> pending;

    if (!m_root)
        return false;
    pending.push(m_root);
    int offset = 1;
    while (!pending.isEmpty())
    {
        ResourceFileInfo *file = pending.pop();
        file->m_childOffset = offset;

        QList<ResourceFileInfo*> m_children = file->m_children.values();
        qSort(m_children.begin(), m_children.end(), qt_rcc_compare_hash);

        for (int i = 0; i < m_children.size(); ++i)
        {
            ResourceFileInfo *child = m_children.at(i);
            ++offset;
            if (child->m_flags & 2)
                pending.push(child);
        }
    }

    pending.push(m_root);
    m_root->writeDataInfo(*this);
    while (!pending.isEmpty())
    {
        ResourceFileInfo *file = pending.pop();

        QList<ResourceFileInfo*> m_children = file->m_children.values();
        qSort(m_children.begin(), m_children.end(), qt_rcc_compare_hash);
        for (int i = 0; i < m_children.size(); ++i)
        {
            ResourceFileInfo *child = m_children.at(i);
            child->writeDataInfo(*this);
            if (child->m_flags & 2)
                pending.push(child);
        }
    }
    return true;
}

bool QRccFileMaker::writeInitializer()
{
    int i = 4;
    char *p = m_out.data();
    p[i++] = 0;
    p[i++] = 0;
    p[i++] = 0;
    p[i++] = 1;

    p[i++] = (m_treeOffset >> 24) & 0xff;
    p[i++] = (m_treeOffset >> 16) & 0xff;
    p[i++] = (m_treeOffset >>  8) & 0xff;
    p[i++] = (m_treeOffset >>  0) & 0xff;

    p[i++] = (m_dataOffset >> 24) & 0xff;
    p[i++] = (m_dataOffset >> 16) & 0xff;
    p[i++] = (m_dataOffset >>  8) & 0xff;
    p[i++] = (m_dataOffset >>  0) & 0xff;

    p[i++] = (m_namesOffset >> 24) & 0xff;
    p[i++] = (m_namesOffset >> 16) & 0xff;
    p[i++] = (m_namesOffset >>  8) & 0xff;
    p[i++] = (m_namesOffset >>  0) & 0xff;
    return true;
}
