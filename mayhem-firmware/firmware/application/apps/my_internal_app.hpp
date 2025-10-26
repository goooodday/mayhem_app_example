#ifndef __UI_MY_INTERNAL_APP_H__
#define __UI_MY_INTERNAL_APP_H__

#include <atomic>
#include "ui_widget.hpp"
#include "ui_navigation.hpp"

namespace ui {
    class MyInternalAppView : public View {
    public:
        MyInternalAppView(NavigationView& nav);
        void focus() override;
        std::string title() const override { return "Internal App"; };

    private:
        // UI 요소 선언
        Labels label_{
            {{40, 60},
            "goooodday hyeongabshin",
            Theme::getInstance()->fg_light->foreground},
        };

        Button button_exit_{
            {100, 120, 120, 40},
            "Exit"
        };
    };
} // namespace ui

#endif // __UI_MY_INTERNAL_APP_H__
