#include "rviz_widget.h"
#include <QApplication>
#include <rclcpp/rclcpp.hpp>

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    QApplication app(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("rviz_gui_panel");
    TestWidget widget(node);
    widget.show();
    return app.exec();
}