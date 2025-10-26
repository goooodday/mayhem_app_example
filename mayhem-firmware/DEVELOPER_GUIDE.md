# Mayhem 펌웨어 개발 가이드

이 문서는 Mayhem 펌웨어의 커스텀 앱 개발을 시작하는 데 필요한 정보와 주요 문서들을 안내합니다.

---

## 1. 공식 소스 코드 저장소

모든 개발은 공식 Mayhem 펌웨어 GitHub 저장소를 기반으로 합니다. 최신 변경사항이나 다른 기여자들의 코드를 참고하려면 항상 공식 저장소를 확인하는 것이 좋습니다.

- **공식 GitHub 저장소:** [https://github.com/portapack-mayhem/mayhem-firmware](https://github.com/portapack-mayhem/mayhem-firmware)

---

## 2. 개발 시작하기

펌웨어 개발은 크게 **환경 설정**, **내부 앱 개발**, **외부 앱 개발**의 세 단계로 나뉩니다. 아래의 가이드들은 각 단계에 대한 상세한 절차를 설명합니다.

개발을 시작하기 전, 아래 순서대로 문서를 읽는 것을 권장합니다.

1.  **[펌웨어 개발 환경 설정 (01_FIRMWARE_ENVIRONMENT_SETUP.md)](../01_FIRMWARE_ENVIRONMENT_SETUP.md)**
    - Docker와 Colima를 사용한 macOS 기반의 개발 환경 설정 방법을 안내합니다. 펌웨어를 빌드하고 결과물을 확인하는 방법까지 포함됩니다.

2.  **[내부 앱 개발 가이드 (02_INTERNAL_APP_DEVELOPMENT.md)](../02_INTERNAL_APP_DEVELOPMENT.md)**
    - 펌웨어의 일부로 직접 컴파일되는 "내부 앱"을 개발하는 방법을 안내합니다. 예제 코드와 함께 빌드 시스템에 앱을 등록하는 방법을 설명합니다.

3.  **[외부 앱(플러그인) 개발 가이드 (03_EXTERNAL_APP_DEVELOPMENT.md)](../03_EXTERNAL_APP_DEVELOPMENT.md)**
    - SD 카드에서 동적으로 로드되는 "외부 앱"(.ppma 파일)을 개발하는 방법을 안내합니다. 빠른 테스트와 배포에 유리한 플러그인 방식의 개발 절차를 설명합니다.
