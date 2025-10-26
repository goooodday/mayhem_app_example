# 3. 외부 앱 (플러그인) 개발 가이드 (최종판)

이 문서는 실제 빌드에 성공한 코드를 기반으로, 외부 앱을 개발하는 표준 절차를 안내합니다.

> **워크플로우 알림:** 모든 파일 생성 및 수정은 **macOS에서**, 모든 빌드 및 컴파일은 **Docker 컨테이너 셸에서** 실행하는 것을 기준으로 합니다.

---

### 1단계: 애플리케이션 소스 파일 생성

외부 앱은 일반적으로 **앱 정보(`main.cpp`)**, **View 헤더(`.hpp`)**, **View 구현(`.cpp`)**의 세 파일로 구성됩니다. `my_external_app`이라는 이름의 샘플을 생성합니다.

- **디렉터리:** `firmware/application/external/my_external_app/`

#### 1-1. `main.cpp` (앱 정보 및 진입점)
```cpp
#include "my_external_app.hpp"

// 앱의 정보를 정의하는 구조체입니다.
// __attribute__를 사용하여 링커가 이 정보를 인식하도록 합니다.
extern "C" __attribute__((section(".external_app.app_my_external_app.application_information"), used))
const application_information_t _application_information_ui_new_external_app = {
    /*.memory_location = */ (uint8_t*)0x00000000,
    /*.externalAppEntry = */ ui::external_app::my_external_app::initialize_app,
    /*.header_version = */ CURRENT_HEADER_VERSION,
    /*.app_version = */ VERSION_MD5,
    /*.app_name = */ "NewExternalApp",
    /*.bitmap_data = */ { // 아이콘 데이터 (임시)
        0x54, 0x15, 0x54, 0x15, 0xFF, 0x7F, 0xFC, 0x1F,
        0xFF, 0x7F, 0xCC, 0x19, 0xAF, 0x7A, 0x6C, 0x1B,
        0xEF, 0x7B, 0xEC, 0x1B, 0xFF, 0x7F, 0xFC, 0x1F,
        0xFF, 0x7F, 0x54, 0x15, 0x54, 0x15, 0x00, 0x00,
    },
    /*.icon_color = */ ui::Color::cyan().v,
    /*.menu_location = */ app_location_t::DEBUG,
    /*.desired_menu_position = */ -1,
    /*.m4_app_tag = portapack::spi_flash::image_tag_none */ {0, 0, 0, 0},
    /*.m4_app_offset = */ 0x00000000,  // 컴파일 시 채워짐
};

namespace ui::external_app::my_external_app {
// 앱이 처음 실행될 때 호출되는 진입점 함수입니다.
void initialize_app(ui::NavigationView& nav) {
    nav.push<NewExternalAppView>();
}
} // namespace
```

#### 1-2. `my_external_app.hpp` (View 헤더)
```cpp
#ifndef __UI_NEW_EXTERNAL_APP_H__
#define __UI_NEW_EXTERNAL_APP_H__

#include "ui.hpp"
#include "ui_navigation.hpp"
#include "external_app.hpp"

namespace ui::external_app::my_external_app {

class NewExternalAppView : public View {
public:
    NewExternalAppView(NavigationView& nav);
    void focus() override;
    std::string title() const override { return "NewExternalApp"; };

private:
    NavigationView& nav_;
    Text text_widget{{0, 152, 240, 16}, "goooodday hyeongabshin"};
    Button button_exit{{184, 272, 64, 24}, "Exit"};
};

} // namespace

#endif
```

#### 1-3. `my_external_app.cpp` (View 구현)
```cpp
#include "my_external_app.hpp"

namespace ui::external_app::my_external_app {

NewExternalAppView::NewExternalAppView(NavigationView& nav)
    : nav_{nav} {
    add_children({&text_widget, &button_exit});
    button_exit.on_select = [this](Button&) {
        nav_.pop();
    };
}

void NewExternalAppView::focus() {
    button_exit.focus();
}

} // namespace
```

### 2단계: 링커 스크립트 수정 (`external.ld`)

외부 앱이 메모리의 어느 위치에 자리 잡을지 지정합니다. **이 단계는 매우 중요하며, 누락 시 빌드가 실패합니다.**

- **파일 열기:** `firmware/application/external/external.ld`

1.  **`MEMORY` 블록 수정:**
    파일 상단의 `MEMORY` 블록에서, 마지막 앱의 `org` 주소에 `len` 만큼(보통 32k = 0x8000) 더한 주소로 새 앱의 메모리 영역을 추가합니다.
    ```ld
    /* 예시: 마지막 앱의 org가 0xADDF0000 이었다면... */
    ram_external_app_adult_toys_controller (rwx) : org = 0xADDF0000, len = 32k
    /* ...새 앱의 org는 0xADDF0000 + 0x8000 = 0xADDF8000 이 됩니다. */
    ram_external_app_my_external_app (rwx) : org = 0xADDF8000, len = 32k
    ```

2.  **`SECTIONS` 블록 수정:**
    파일 하단의 `SECTIONS` 블록에 새 앱을 위한 섹션을 추가합니다. `app_my_external_app` 부분은 앱 이름에 맞게 수정합니다.
    ```ld
    .external_app_my_external_app : ALIGN(4) SUBALIGN(4)
    {
        KEEP(*(.external_app.app_my_external_app.application_information));
        *(*ui*external_app*my_external_app*);
    } > ram_external_app_my_external_app
    ```

### 3단계: 빌드 시스템 등록 (`external.cmake`)

- **파일 열기:** `firmware/application/external/external.cmake`

1.  **`EXTCPPSRC` 리스트에 소스 파일 추가:**
    ```cmake
    # my_external_app
    external/my_external_app/main.cpp
    external/my_external_app/my_external_app.cpp
    ```

2.  **`EXTAPPLIST` 리스트에 앱 이름 추가:**
    ```cmake
    my_external_app
    ```

### 4단계: 빌드 및 배포

1.  **빌드:** `./dockerize.sh` 또는 `ninja` 명령어로 전체 프로젝트를 빌드합니다.
2.  **배포:** `build/firmware/` 폴더에 생성된 `my_external_app.ppma` 파일을 SD 카드의 `/APPS` 폴더로 복사합니다.
3.  **실행:** 기기를 재부팅하고 `Debug` 메뉴(또는 `main.cpp`에서 지정한 위치)에서 "NewExternalApp"을 찾아 실행합니다.