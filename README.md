# Mayhem Firmware for HackRF PortaPack

이 디렉터리에는 [HackRF](http://greatscottgadgets.com/hackrf/)용 애드온인 [PortaPack](https://github.com/sharebrained/portapack-hackrf)의 [Mayhem 펌웨어](https://github.com/portapack-mayhem/mayhem-firmware)가 포함되어 있습니다. 이 펌웨어는 원래의 Havoc 펌웨어를 기반으로 다양한 기능과 수정 사항을 추가한 버전입니다.

## 주요 기능

`sdcard` 디렉터리 구조에서 유추한 주요 기능은 다음과 같습니다:

- **ADSB:** 항공기 위치 수신
- **AIS:** 선박 자동 식별 시스템
- **BLETX:** 블루투스 저전력 송신
- **GPS:** GPS 시뮬레이션 및 수신
- **SSTV:** 저속 주사 텔레비전
- **Sub-GHz:** 다양한 Sub-GHz 프로토콜 통신
- **OOK/AM/FM:** 기본 변조 신호 송수신
- **Frequency Manager:** 주파수 관리
- 그 외 다수

## 프로젝트 구조

- `mayhem-firmware/`: 메인 펌웨어 소스 코드 및 빌드 관련 파일이 위치합니다.
  - `firmware/`: 펌웨어의 핵심 소스 코드가 들어있습니다.
  - `sdcard/`: 펌웨어 실행에 필요한 파일 및 데이터가 저장되는 SD 카드의 구조를 보여줍니다.
  - `flashing/`: 펌웨어를 기기에 플래싱하기 위한 스크립트와 도구가 포함되어 있습니다.
  - `hardware/`: PortaPack 하드웨어 관련 정보가 있습니다.
  - `docs/`: 프로젝트 관련 문서가 있습니다.

## 시작하기

### 빌드

이 프로젝트는 Docker를 사용하여 빌드 환경을 구성할 수 있습니다. `docker-compose.yml`과 `dockerfile`을 참조하여 빌드 컨테이너를 설정하고 `CMakeLists.txt`를 통해 펌웨어를 빌드할 수 있습니다.

### 펌웨어 업데이트

`flashing/` 디렉터리에 포함된 스크립트 (`flash_portapack_mayhem.bat` 등)와 `README.txt` 파일을 참조하여 펌웨어를 업데이트할 수 있습니다.

## 상세 정보

더 자세한 정보, 최신 릴리스, 기여 방법 등은 `mayhem-firmware/README.md` 파일과 [공식 GitHub 저장소](https://github.com/portapack-mayhem/mayhem-firmware)를 참조하십시오.
# mayhem_app_example
