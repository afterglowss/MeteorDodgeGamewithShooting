# Meteor Dodge Game with Shooting

> 개발 언어: C  
> 게임 라이브러리: [Raylib](https://www.raylib.com/)  
> 팀 구성: 4인 팀  (Git Flow 전략 기반 협업)  
> 버전 관리: Git + GitHub + GitHub Projects + Issues + PR Reviews + SourceTree

---

## 게임 소개

이 프로젝트는 Raylib를 기반으로 제작된 2D 슈팅/도전형 게임입니다.  
플레이어는 운석을 피하거나 제거하며 최대한 높은 점수 획득을 목표로 합니다.  
게임은 C 언어로 작성되었으며, Raylib를 통해 그래픽 및 기능을 구현하였습니다.

---

## 주요 기능

- 플레이어 이동 및 총알 발사
- 운석 랜덤 스폰
- 충돌 처리 및 이펙트
- 점수 시스템 및 생명 관리
- 게임오버 및 시작 화면 UI

---

## 협업 방식

- **브랜치 전략**: Git Flow  
  - `main`: 안정 배포 버전  
  - `develop`: 통합 개발 브랜치  
  - `feature/*`: 기능 단위 브랜치  
  - `bugfix/*`: 버그 수정 브랜치  
  - `release/*`: 릴리스 준비 브랜치  
  - `hotfix/*`: 긴급 수정 브랜치

- **작업 흐름**
  1. 이슈 생성 후 브랜치 생성
  2. 코드 작성 및 커밋
  3. Pull Request 생성 및 리뷰 요청
  4. PR 승인 → `develop` 또는 `main` 병합
  5. 보드 자동화 연동으로 프로젝트 관리
  6. 디스코드로 Issue 및 PR 알림 자동화

---

## 컴파일 및 실행 방법

### 사전 준비

1. Release 에서 .exe 파일 다운로드
2. 더블클릭해서 실행 

### 빌드 예시

```bash
gcc -o game main.c player.c bullet.c enemy.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./game
```

> ※ 운영체제 및 사용한 모듈에 따라 링크 옵션이 다를 수 있습니다.

---

## 폴더 구조 예시

```
.
├── main.c               # 게임 루프 및 전체 흐름
├── player.c/.h          # 플레이어 조작 및 렌더링
├── bullet.c/.h          # 총알 생성 및 이동
├── meteor.c/.h          # 운석 생성 및 이동, 충돌
└── game.c/.h           # 공통 유틸리티 함수
```

---

## 코드 사용법 요약

- `InitWindow()` / `CloseWindow()` → 게임 창 초기화 및 종료
- `BeginDrawing()` / `EndDrawing()` → 매 프레임 렌더링 구간
- `IsKeyDown(KEY_SPACE)` → 키 입력 감지
- `CheckCollisionCicle()` → 충돌 판정

---

## 기여 방법

1. 이슈를 생성하거나 담당 이슈를 할당받습니다.
2. `feature/*` 브랜치를 생성해 작업합니다.
3. PR 생성 시 템플릿을 활용하여 설명을 작성합니다.
4. 리뷰어가 승인한 뒤 `develop`에 병합합니다.

---