#include "GLDCustomButton.h"
#include "GLDIrregularForm.h"

#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>

namespace GlodonMask
{
    GLDIrregularForm::GLDIrregularForm(QWidget *parent)
        : QWidget(parent)
        , m_pPushBtn(nullptr)
        , m_pCustomBtn(nullptr)
        , m_irregularFormPm("")
        , m_xPosition(0)
        , m_yPosition(0)
    {
        setFlagAndAttribute();
    }

    GLDIrregularForm::GLDIrregularForm(const QString & irregularImgPath, const QString & btnImgPath, QWidget *parent)
        : QWidget(parent)
        , m_pPushBtn(nullptr)
        , m_pCustomBtn(new GLDCustomButton(btnImgPath, this))
        , m_irregularFormPm("")
        , m_xPosition(0)
        , m_yPosition(0)
    {
        setFlagAndAttribute();

        loadPixmap(irregularImgPath);

        connect(m_pCustomBtn, &QPushButton::clicked, this, &GLDIrregularForm::irregularFormClicked);
    }

    GLDIrregularForm::GLDIrregularForm(const QString &irregularImgPath, QPushButton *btn, QWidget *parent)
        : QWidget(parent)
        , m_pPushBtn(btn)
        , m_pCustomBtn(nullptr)
        , m_irregularFormPm("")
        , m_xPosition(0)
        , m_yPosition(0)
    {
        setFlagAndAttribute();

        btn->setParent(this);

        loadPixmap(irregularImgPath);

        if (m_pPushBtn)
        {
            connect(m_pPushBtn, &QPushButton::clicked, this, &GLDIrregularForm::irregularFormClicked);
        }
        else
        {
            connect(m_pCustomBtn, &QPushButton::clicked, this, &GLDIrregularForm::irregularFormClicked);
        }
    }

    void GLDIrregularForm::setFlagAndAttribute()
    {
        setAttribute(Qt::WA_NoSystemBackground);
        setAttribute(Qt::WA_TranslucentBackground);
        setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    GLDIrregularForm::~GLDIrregularForm()
    {

    }

    QSize GLDIrregularForm::sizeHint() const
    {
        if (!m_irregularFormPm.isNull())
        {
            return m_irregularFormPm.size();
        }

        return QWidget::sizeHint();
    }

    void GLDIrregularForm::loadPixmap(const QString & pixmapPath)
    {
        QPixmap tempPixmap;
        tempPixmap.load(pixmapPath);
        setPixmap(tempPixmap);
    }

    void GLDIrregularForm::setPixmap(const QPixmap & pm)
    {
        m_irregularFormPm = pm;
        update();
    }

    void GLDIrregularForm::setBtnPos(QAbstractButton* pBtn, const int x, const int y)
    {
        m_xPosition = x;
        m_yPosition = y;
    }

    void GLDIrregularForm::paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);

        if (m_pPushBtn)
        {
            m_pPushBtn->move(m_xPosition, m_yPosition);
        }
        else
        {
            m_pCustomBtn->move(m_xPosition, m_yPosition);
        }

        painter.drawPixmap(0, 0, m_irregularFormPm);

        QWidget::paintEvent(event);
    }
}
