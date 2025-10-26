# 1. 펌웨어 개발 환경 설정

이 문서는 Mayhem 펌웨어 개발 및 빌드를 위한 Docker 기반의 표준 개발 환경을 설정하는 방법을 안내합니다。

---

### 추천 개발 워크플로우 (macOS + Docker)

이 문서에서 설명하는 환경은 사용자의 MacBook Pro 환경에 최적화되어 있습니다. 핵심 워크플로우는 다음과 같습니다.

- **코드 편집:** **macOS에서** Visual Studio Code, Sublime Text 등 선호하는 텍스트 에디터를 사용하여 소스 코드를 편집합니다.
- **컴파일 및 빌드:** **Docker 컨테이너 내부에서** 빌드 명령을 실행합니다.

프로젝트 폴더가 Docker 컨테이너와 공유되므로, macOS에서 파일을 저장하면 변경사항이 즉시 컨테이너에 반영되어 빌드할 수 있습니다. 이 방식을 통해 macOS의 쾌적한 UI 환경과 Docker의 일관된 빌드 환경의 장점을 모두 활용할 수 있습니다.

**필수 요구사항:**
- [Docker Desktop](https://www.docker.com/products/docker-desktop/) (시스템에 설치 및 실행 중이어야 함)
- Git 클라이언트

---

### 0단계: Docker 데몬 실행 확인

모든 작업을 시작하기 전에, Docker 데몬(백그라운드 서비스)이 실행 중인지 확인해야 합니다.

- **Colima 사용자 (현재 환경):**
  터미널에서 다음 명령어로 상태를 확인합니다.
  ```sh
  colima status
  ```
  만약 `Stopped` 상태라면, 다음 명령어로 Colima를 시작합니다. 시작하는 데 시간이 다소 걸릴 수 있습니다.
  ```sh
  colima start
  ```

- **Docker Desktop 사용자:**
  macOS 상단 메뉴 막대나 응용 프로그램 폴더에서 Docker Desktop 앱이 실행 중인지 확인합니다.

---

### 1단계: 소스 코드 클론

먼저, `mayhem-firmware` Git 저장소를 로컬 컴퓨터로 클론합니다.

```sh
# mayhem-firmware 디렉터리가 이미 있다면 해당 디렉터리로 이동하십시오.
# git clone https://github.com/portapack-mayhem/mayhem-firmware.git
cd mayhem-firmware
```

### 2단계: Git 서브모듈 초기화

프로젝트는 `hackrf` 등 여러 Git 서브모듈에 의존하고 있습니다. 다음 명령어를 사용하여 서브모듈의 소스 코드를 다운로드해야 합니다. 이 단계는 최초 클론 후 한 번만 실행하면 됩니다.

```sh
# macOS 터미널에서 실행
git submodule update --init --recursive
```

### 2단계: Docker 이미지 빌드

프로젝트에는 Docker 환경 관리를 위한 헬퍼 스크립트가 포함되어 있습니다. 다음 명령을 실행하여 개발용 Docker 이미지를 빌드합니다. 이 과정은 최초 실행 시 다소 시간이 소요될 수 있습니다.

```sh
./dockerize.sh build
```

### 3단계: Docker 환경 사용하기

`dockerize.sh` 스크립트를 통해 Docker 환경을 사용하는 방법은 크게 두 가지로 나뉩니다.

#### A. 자동 빌드 실행 (가장 간단하고 권장되는 방법)

소스 코드 수정 후 펌웨어를 빌드만 하는 것이 목적일 때 사용합니다.

**macOS 터미널의 프로젝트 루트**에서 `shell` 인자 없이 `./dockerize.sh`를 실행하면, 스크립트가 자동으로 `cmake` 환경 구성(필요시)과 `ninja` 빌드를 순서대로 한 번에 수행합니다.

```sh
# macOS 터미널의 mayhem-firmware 폴더에서 실행
./dockerize.sh
```

빌드가 완료되면 터미널이 자동으로 종료됩니다. 

#### B. 대화형 셸 실행 (수동 제어 및 디버깅용)

빌드 과정을 직접 제어하거나, 파일을 생성/삭제하거나, 다른 디버깅 작업을 하고 싶을 때 사용합니다.

**macOS 터미널의 프로젝트 루트**에서 `shell` 인자를 붙여 실행합니다.

```sh
./dockerize.sh shell
```

명령어 실행 시, 터미널이 컨테이너 내부의 셸로 접속되며 프롬프트가 `$` 또는 `#`로 바뀝니다. 여기서부터 입력하는 명령어는 컨테이너 내부에서 실행됩니다.

- **경로 매핑:** macOS의 `mayhem-firmware` 프로젝트 폴더는 컨테이너의 `/havoc` 디렉터리에 연결되어 있습니다. `cd /havoc`으로 이동하면 모든 프로젝트 파일을 볼 수 있습니다.
- **수동 빌드:** 셸 안에서 수동으로 빌드하려면 다음 순서를 따릅니다. (최초 한 번만 `cmake` 과정 필요)
  ```sh
  cd /havoc
  mkdir -p build && cd build
  cmake ..
  ninja
  ```

---

### 4단계: 빌드 결과물 확인

빌드가 성공적으로 완료되면, 최종 결과물은 **호스트 컴퓨터(macOS)**의 프로젝트 폴더 내 여러 위치에 생성됩니다.

- **전체 펌웨어 바이너리:**
  - `build/firmware/` 폴더 안에 `.bin` 확장자를 가진 파일로 생성됩니다. (예: `portapack-h1_h2-mayhem.bin`)

- **외부 앱 (플러그인):**
  - `firmware_tar/APPS/` 폴더 안에 `.ppma` 확장자를 가진 파일로 생성됩니다.

- **통합 배포 패키지:**
  - 프로젝트 루트에 `portapack-mayhem_OCI.ppfw.tar` 와 같은 `.tar` 파일이 생성됩니다. 이 파일은 펌웨어와 외부 앱 등 모든 것을 포함하는 하나의 패키지일 가능성이 높습니다.
