# 2. 내부 앱 개발 가이드

이 문서는 메인 펌웨어에 직접 포함되는 **내부 앱(Internal App)**을 개발하는 방법을 설명합니다. 내부 앱은 펌웨어 바이너리의 일부가 되며, 주로 설정 메뉴나 정보 화면처럼 펌웨어의 핵심 기능과 밀접하게 연관된 경우에 사용됩니다.

> **워크플로우 알림:** 이 가이드의 모든 파일 생성 및 수정 작업은 **macOS에서** 선호하는 텍스트 에디터를 사용하고, 모든 빌드 및 컴파일 명령어는 **Docker 컨테이너 셸에서** 실행하는 것을 기준으로 합니다.

---

### 1단계: 애플리케이션 소스 파일 생성

`my_internal_app`이라는 이름의 샘플 앱을 생성합니다. 이 앱은 `Button` 위젯을 라벨처럼 사용하여 텍스트를 표시합니다.

- **헤더 파일: `apps/my_internal_app.hpp`**
  ```cpp
  #ifndef __UI_MY_INTERNAL_APP_H__
  #define __UI_MY_INTERNAL_APP_H__

  #include "ui_widget.hpp"
  #include "ui_navigation.hpp"
  #include "ui_theme.hpp"

  namespace ui {
  class MyInternalAppView : public View {
  public:
      MyInternalAppView(NavigationView& nav);
      void focus() override;
      std::string title() const override { return "Gooood Day"; };

  private:
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
  ```

- **소스 파일: `apps/my_internal_app.cpp`**
  ```cpp
  #include "apps/my_internal_app.hpp"

  namespace ui {
  MyInternalAppView::MyInternalAppView(NavigationView& nav) {
      add_children({&label_, &button_exit_}); // UI 요소들을 뷰에 추가
      
      // 종료 버튼에만 선택 이벤트를 할당
      button_exit_.on_select = [&nav](Button&) {
          nav.pop();
      };
  }

  void MyInternalAppView::focus() {
      button_exit_.focus(); // 종료 버튼에만 포커스
  }
  } // namespace ui
  ```

### 2단계: 빌드 시스템에 앱 등록

1.  **`CMakeLists.txt` 수정:**
    `firmware/application/CMakeLists.txt`의 `CPPSRC` 리스트에 `apps/my_internal_app.cpp`를 추가합니다.

2.  **메인 메뉴에 앱 추가 (`ui_navigation.cpp`):**
    `firmware/application/ui_navigation.cpp`의 `NavigationView::appList`에 아래 항목을 추가합니다. (아이콘은 임시로 `bitmap_icon_receivers` 사용)

    - **헤더 포함:**
      ```cpp
      #include "apps/my_internal_app.hpp"
      ```

    - **`appList`에 항목 추가:**
      ```cpp
      const NavigationView::AppList NavigationView::appList = {
          // ...
          {nullptr, "My Internal App", HOME, Color::white(), &bitmap_icon_receivers, new ViewFactory<MyInternalAppView>()},
          // ...
      };
      ```

### 3단계: 펌웨어 빌드 및 플래싱

내부 앱은 펌웨어의 일부이므로, 펌웨어 전체를 다시 빌드하고 기기에 플래시해야 합니다.

1.  **펌웨어 빌드:** `./dockerize.sh` 또는 `ninja` 명령어로 빌드합니다.
2.  **기기 플래싱:** `build/firmware/` 폴더에 생성된 `.bin` 파일을 기기에 플래시합니다.

### 4단계: 실행

기기를 재부팅한 후, 메인 메뉴에서 "My Internal App"을 찾아 실행합니다.
