#include "apps/my_internal_app.hpp"

namespace ui {
MyInternalAppView::MyInternalAppView(NavigationView& nav) {
    add_children({&label_, &button_exit_}); // UI 요소를 뷰에 추가
    button_exit_.on_select = [&nav](Button&) {
        nav.pop(); // "Exit" 버튼 클릭 시 이전 메뉴로 복귀
    };
}

void MyInternalAppView::focus() {
    button_exit_.focus(); // 앱 시작 시 "Exit" 버튼에 포커스
}
} // namespace ui
