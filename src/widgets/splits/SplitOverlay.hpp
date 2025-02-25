#pragma once

#include "widgets/BaseWidget.hpp"

#include <pajlada/signals/signalholder.hpp>
#include <QGridLayout>
#include <QPushButton>

namespace chatterino {

class Split;

class SplitOverlay : public BaseWidget
{
public:
    explicit SplitOverlay(Split *parent = nullptr);

protected:
    //    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    // fourtf: !!! preserve the order of left, up, right and down
    enum HoveredElement {
        None,
        SplitMove,
        SplitLeft,
        SplitUp,
        SplitRight,
        SplitDown
    };

    class ButtonEventFilter : public QObject
    {
        SplitOverlay *parent;
        HoveredElement hoveredElement;

    public:
        ButtonEventFilter(SplitOverlay *parent, HoveredElement hoveredElement);

    protected:
        bool eventFilter(QObject *watched, QEvent *event) override;
    };

    HoveredElement hoveredElement_ = None;
    Split *split_;
    QGridLayout *layout_;
    QPushButton *left_;
    QPushButton *up_;
    QPushButton *right_;
    QPushButton *down_;

    pajlada::Signals::SignalHolder signalHolder_;

    friend class ButtonEventFilter;
};

}  // namespace chatterino
