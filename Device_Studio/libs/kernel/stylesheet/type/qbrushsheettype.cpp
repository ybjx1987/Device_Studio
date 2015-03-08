#include "qbrushsheettype.h"

#include "../../qvarianttype.h"
#include "../../xmlnode.h"

#include <QIcon>
#include <QPainter>
#include <QPixmap>

QBrushSheetType::QBrushSheetType()
{

}

QBrushSheetType::~QBrushSheetType()
{

}

QString QBrushSheetType::getValueText()
{
    QString str;
    if(!getValue().isValid())
    {
        return "Invalid";
    }

    tagBrushSheetType value = getValue().value<tagBrushSheetType>();

    if(value.m_type == "Color")
    {
        QColor c = value.m_value.value<QColor>();
        if(value.m_alpha == "true")
        {
            str = QString("rgb(%1,%2,%3,%4)").arg(c.red())
                    .arg(c.green()).arg(c.blue()).arg(c.alpha());
        }
        else
        {
            str = QString("rgb(%1,%2,%3)").arg(c.red())
                    .arg(c.green()).arg(c.blue());
        }
    }
    else if(value.m_type == "Gradient")
    {
        QGradient g = value.m_value.value<QGradient>();
        switch (g.type())
        {
            case QGradient::LinearGradient:
                str = "Linear Gradient";
                break;
            case QGradient::RadialGradient:
                str = "Radial Gradient";
                break;
            case QGradient::ConicalGradient:
                str = "Conical Gradient";
                break;
            default:
                return "Invalid";
        }

        str +="(";

        foreach(QGradientStop stop,g.stops())
        {
            str += QString(" [%1 rgba(%2,%3,%4,%5)]")
                    .arg(stop.first)
                    .arg(stop.second.red())
                    .arg(stop.second.green())
                    .arg(stop.second.blue())
                    .arg(stop.second.alpha());
        }
        str += " )";
    }

    return str;
}

QIcon QBrushSheetType::getValueIcon()
{
    if(!getValue().isValid())
    {
        return QIcon();
    }
    tagBrushSheetType value = getValue().value<tagBrushSheetType>();
    QPixmap pixmap=QPixmap(16,16);
    QPainter p(&pixmap);
    p.fillRect(QRect(0,0,16,16),QColor(0,0,0));
    if(value.m_type == "Color")
    {
        p.fillRect(QRect(0,0,16,16),value.m_value.value<QColor>());
    }
    else if(value.m_type == "Gradient")
    {
        QGradient g = value.m_value.value<QGradient>();
        p.fillRect(QRect(0,0,16,16),g);
    }
    else
    {
        return QIcon();
    }
    return QIcon(pixmap);
}

QStringList QBrushSheetType::styleSheetParameters(const QGradient &gradient)
{
    QStringList result;

    if (gradient.type() != QGradient::ConicalGradient)
    {
        QString spread;
        switch (gradient.spread())
        {
            case QGradient::PadSpread:
                spread = QLatin1String("pad");
                break;
            case QGradient::ReflectSpread:
                spread = QLatin1String("reflect");
                break;
            case QGradient::RepeatSpread:
                spread = QLatin1String("repeat");
                break;
            default:
                break;
        }
        result << QLatin1String("spread:") + spread;
    }

    switch (gradient.type())
    {
    case QGradient::LinearGradient:
    {
        const QLinearGradient *linearGradient = static_cast<const QLinearGradient*>(&gradient);
        result << QLatin1String("x1:") + QString::number(linearGradient->start().x())
                << QLatin1String("y1:")    + QString::number(linearGradient->start().y())
                << QLatin1String("x2:")    + QString::number(linearGradient->finalStop().x())
                << QLatin1String("y2:")    + QString::number(linearGradient->finalStop().y());
        break;
    }
    case QGradient::RadialGradient:
    {
        const QRadialGradient *radialGradient = static_cast<const QRadialGradient*>(&gradient);
        result << QLatin1String("cx:")  + QString::number(radialGradient->center().x())
                << QLatin1String("cy:")     + QString::number(radialGradient->center().y())
                << QLatin1String("radius:") + QString::number(radialGradient->radius())
                << QLatin1String("fx:")     + QString::number(radialGradient->focalPoint().x())
                << QLatin1String("fy:")     + QString::number(radialGradient->focalPoint().y());
        break;
    }
    case QGradient::ConicalGradient:
    {
        const QConicalGradient *conicalGradient = static_cast<const QConicalGradient*>(&gradient);
        result << QLatin1String("cx:") + QString::number(conicalGradient->center().x())
                << QLatin1String("cy:")    + QString::number(conicalGradient->center().y())
                << QLatin1String("angle:") + QString::number(conicalGradient->angle());
        break;
    }
    default:
        break;
    }

    return result;
}

QStringList QBrushSheetType::styleSheetStops(const QGradient &gradient)
{
    QStringList result;
    foreach (const QGradientStop &stop, gradient.stops())
    {
        const QColor color = stop.second;

        const QString stopDescription = QLatin1String("stop:") + QString::number(stop.first) + QLatin1String(" rgba(")
                + QString::number(color.red()) + QLatin1String(", ")
                + QString::number(color.green()) + QLatin1String(", ")
                + QString::number(color.blue()) + QLatin1String(", ")
                + QString::number(color.alpha()) + QLatin1Char(')');
        result << (stopDescription);
    }

    return result;
}


QString QBrushSheetType::styleSheetFillName(const QGradient &gradient)
{
    QString result;

    switch (gradient.type())
    {
        case QGradient::LinearGradient:
            result += QLatin1String("qlineargradient");
            break;
        case QGradient::RadialGradient:
            result += QLatin1String("qradialgradient");
            break;
        case QGradient::ConicalGradient:
            result += QLatin1String("qconicalgradient");
            break;
        default:
        break;
    }

    return result;
}

QString QBrushSheetType::styleSheetCode(const QGradient &gradient)
{
    QString fillname=styleSheetFillName(gradient);

    QString ret;

    QStringList list=styleSheetParameters(gradient);

    ret=fillname+"("+list.join(QLatin1String(", "));
    ret += ",";
    list=styleSheetStops(gradient);
    ret += list.join("");
    ret+=")";
    return ret;
}

QString QBrushSheetType::getStyleSheet()
{
    if(!getValue().isValid())
    {
        return "";
    }
    QString str;
    tagBrushSheetType value = getValue().value<tagBrushSheetType>();
    if(value.m_type == "Color")
    {
        QColor c = value.m_value.value<QColor>();
        if(value.m_alpha == "true")
        {
            str = QString("rgb(%1,%2,%3,%4)").arg(c.red())
                    .arg(c.green()).arg(c.blue()).arg(c.alpha());
        }
        else
        {
            str = QString("rgb(%1,%2,%3)").arg(c.red())
                    .arg(c.green()).arg(c.blue());
        }
    }
    else if(value.m_type == "Gradient")
    {
        QGradient g = value.m_value.value<QGradient>();
        if(g.type() == QGradient::NoGradient)
        {
            return "";
        }
        str = styleSheetCode(g);
    }
    else
    {
        return "";
    }

    if(str != "")
    {
        str = m_name + ":" +str;
    }
    return str;
}

bool QBrushSheetType::toXml(XmlNode *xml)
{
    tagBrushSheetType value = getValue().value<tagBrushSheetType>();
    xml->setProperty("color_type",value.m_type);
    xml->setProperty("alpha",value.m_alpha);
    xml->setTitle("Property");
    xml->setProperty("type",getName());
    xml->setProperty("enabled",m_enabled?"true":"false");

    if(value.m_type == "Color")
    {
        QColor c= value.m_value.value<QColor>();
        xml->setProperty("red",QString::number(c.red()));
        xml->setProperty("green",QString::number(c.green()));
        xml->setProperty("blue",QString::number(c.blue()));
        if(value.m_alpha == "true")
        {
            xml->setProperty("alpha",QString::number(c.alpha()));
        }
    }
    else if(value.m_type == "Gradient")
    {
        QGradient g = value.m_value.value<QGradient>();
        if(g.type() != QGradient::NoGradient)
        {
            xml->setProperty("gradient_type",styleSheetFillName(g));

            if (g.type() != QGradient::ConicalGradient)
            {
                switch (g.spread())
                {
                    case QGradient::PadSpread:
                        xml->setProperty("spread","pad");
                        break;
                    case QGradient::ReflectSpread:
                        xml->setProperty("spread","reflect");
                        break;
                    case QGradient::RepeatSpread:
                        xml->setProperty("spread","repeat");
                        break;
                    default:
                        break;
                }
            }

            switch (g.type())
            {
            case QGradient::LinearGradient:
            {
                const QLinearGradient *linearGradient = static_cast<const QLinearGradient*>(&g);
                xml->setProperty("x1", QString::number(linearGradient->start().x()));
                xml->setProperty("y1", QString::number(linearGradient->start().y()));
                xml->setProperty("x2",QString::number(linearGradient->finalStop().x()));
                xml->setProperty("y2",QString::number(linearGradient->finalStop().y()));
                break;
            }
            case QGradient::RadialGradient:
            {
                const QRadialGradient *radialGradient = static_cast<const QRadialGradient*>(&g);
                xml->setProperty("cx",QString::number(radialGradient->center().x()));
                xml->setProperty("cy",QString::number(radialGradient->center().y()));
                xml->setProperty("radius",QString::number(radialGradient->radius()));
                xml->setProperty("fx",QString::number(radialGradient->focalPoint().x()));
                xml->setProperty("fy",QString::number(radialGradient->focalPoint().y()));
                break;
            }
            case QGradient::ConicalGradient:
            {
                const QConicalGradient *conicalGradient = static_cast<const QConicalGradient*>(&g);
                xml->setProperty("cx",QString::number(conicalGradient->center().x()));
                xml->setProperty("cy",QString::number(conicalGradient->center().y()));
                xml->setProperty("angle",QString::number(conicalGradient->angle()));
                break;
            }
            default:
                break;
            }

            foreach(QGradientStop stop,g.stops())
            {
                XmlNode * node = new XmlNode(xml);
                node->setTitle("Stop");
                node->setProperty("pos",QString::number(stop.first));
                node->setProperty("red",QString::number(stop.second.red()));
                node->setProperty("green",QString::number(stop.second.green()));
                node->setProperty("blue",QString::number(stop.second.blue()));
                node->setProperty("alpha",QString::number(stop.second.alpha()));
            }
        }
    }

    return true;
}

bool QBrushSheetType::fromXml(XmlNode *xml)
{
    tagBrushSheetType value;
    value.m_type = xml->getProperty("color_type");
    value.m_alpha = xml->getProperty("alpha");

    if(value.m_type == "Color")
    {
        int red = xml->getProperty("red").toInt();
        int green = xml->getProperty("green").toInt();
        int blue = xml->getProperty("blue").toInt();
        int alpha = xml->getProperty("alpha").toInt();
        QColor c(red,green,blue);
        if(value.m_alpha == "true")
        {
            c.setAlpha(alpha);
        }
        if(c.isValid())
        {
            value.m_value = QVariant::fromValue<QColor>(c);
        }
    }
    else if(value.m_type == "Gradient")
    {
        QString gradient_type = xml->getProperty("gradient_type");
        QGradient g;
        if(gradient_type == "qlineargradient")
        {
            QLinearGradient lg;

            QPointF pf;

            pf.setX(xml->getProperty("x1").toFloat());
            pf.setY(xml->getProperty("y1").toFloat());
            lg.setStart(pf);
            pf.setX(xml->getProperty("x2").toFloat());
            pf.setY(xml->getProperty("y2").toFloat());
            lg.setFinalStop(pf);

            g = lg;
        }
        else if(gradient_type =="qradialgradient")
        {
            QRadialGradient rg;
            QPointF pf;

            pf.setX(xml->getProperty("cx").toFloat());
            pf.setY(xml->getProperty("cy").toFloat());
            rg.setCenter(pf);
            pf.setX(xml->getProperty("fx").toFloat());
            pf.setY(xml->getProperty("fy").toFloat());
            rg.setFocalPoint(pf);
            rg.setRadius(xml->getProperty("radius").toFloat());

            g = rg;
        }
        else if(gradient_type == "qconicalgradient")
        {
            QConicalGradient cg;
            QPointF pf;

            pf.setX(xml->getProperty("cx").toFloat());
            pf.setY(xml->getProperty("cy").toFloat());
            cg.setCenter(pf);
            cg.setAngle(xml->getProperty("angle").toFloat());

            g = cg;
        }
        else
        {
            return true;
        }
        g.setCoordinateMode(QGradient::StretchToDeviceMode);
        if(g.type() != QGradient::ConicalGradient)
        {
            QString spread = xml->getProperty("spread");
            if(spread == "pad")
            {
                g.setSpread(QGradient::PadSpread);
            }
            else if(spread == "reflect")
            {
                g.setSpread(QGradient::ReflectSpread);
            }
            else if(spread == "repeat")
            {
                g.setSpread(QGradient::RepeatSpread);
            }
        }
        QGradientStops stops;
        foreach(XmlNode * obj,xml->getChildren())
        {
            if(obj->getTitle() == "Stop")
            {
                QGradientStop stop;
                stop.first = obj->getProperty("pos").toFloat();
                stop.second.setRed(obj->getProperty("red").toInt());
                stop.second.setGreen(obj->getProperty("green").toInt());
                stop.second.setBlue(obj->getProperty("blue").toInt());
                stop.second.setAlpha(obj->getProperty("alpha").toInt());
                stops.append(stop);
            }
        }
        g.setStops(stops);

        if(stops.size() > 0)
        {
            value.m_value = QVariant::fromValue<QGradient>(g);
        }
    }

    m_enabled = xml->getProperty("enabled") =="true";

    if(!value.m_value.isValid())
    {
        m_value = QVariant();
    }
    else
    {
        m_value=QVariant::fromValue<tagBrushSheetType>(value);
    }
    return true;
}

bool QBrushSheetType::equal(const QVariant &value)
{
    tagBrushSheetType v1 = m_value.value<tagBrushSheetType>();
    tagBrushSheetType v2 = value.value<tagBrushSheetType>();

    return (v1 == v2);
}
