#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QSlider>
#include <rviz_common/panel.hpp>
#include <rviz_common/display_context.hpp>
#include <pluginlib/class_list_macros.hpp>
#include "rviz_widget.h"

class TestPanel : public rviz_common::Panel
{
  public:
    void onInitialize() override {
        try {
            auto node = getDisplayContext()->getRosNodeAbstraction().lock()->get_raw_node();

            auto layout = new QVBoxLayout();
            layout->addWidget(new TestWidget(node, this));
            setLayout(layout);
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
};

PLUGINLIB_EXPORT_CLASS(::TestPanel, rviz_common::Panel)