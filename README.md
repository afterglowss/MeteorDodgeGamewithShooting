# Meteor Dodge Game with Shooting

> 개발 언어: C  
> 게임 라이브러리: [Raylib](https://github.com/raysan5/raylib)  
> 팀 구성: 22011848 신혜원(팀장), 21011777 임우균, 22011796 우지원, 22011813 차서영  (Git Flow 전략 기반 협업)  
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
- 일정 시간마다 등장하는 아이템 획득
- 점수 시스템 및 생명 관리
- 게임오버 및 시작 화면 UI
- 다채로운 사운드

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

## 포함된 파일

| 파일명 | 설명 |
|--------|------|
| `MeteorDodgeGamewithShooting.exe` | Windows 실행 파일 |
| `main.c` 외 `.c/.h` | 게임 전체 소스 코드 |
| `resources/` | 게임 리소스 (사운드 등) |
| `README.md` | 프로젝트 설명 문서 |

---

## 운영체제별 빌드

### Windows (raylib 설치 필요 없음)

1. Release 에서 .exe 파일 다운로드
2. 더블클릭해서 실행

### 이외 운영체제 raylib 설치

- [Raylib](https://github.com/raysan5/raylib) README.md의 build and installation을 통해 자신의 운영체제에 맞게 raylib 설치
- 혹은 [Raylib 간편설치](https://github.com/raylib-extras/raylib-quickstart)

### Linux

```bash
cd ~/Downloads/MeteorDodgeGamewithShooting
gcc main.c game.c player.c bullet.c meteor.c item.c -o MeteorDodgeGamewithShooting -lraylib -lm -lpthread -ldl -lrt -lGL
./MeteorDodgeGamewithShooting
```

### macOS

```bash
cd ~/Downloads/MeteorDodgeGamewithShooting
gcc main.c game.c player.c bullet.c meteor.c item.c -o MeteorDodgeGamewithShooting -lraylib -framework OpenGL -framework Cocoa -framework IOKit
./MeteorDodgeGamewithShooting
```

---

## 플레이 방법

- `방향키` : 플레이어 조작 (← : 왼쪽으로 회전, → : 오른쪽으로 회전, ↑ : 앞으로 전진) 및 메뉴 조작
- `Space` : 총알 발사
- `BackSpace` : 메인화면으로 돌아가기
- `Enter` : 메인화면으로 돌아가기, 게임 재시작

---

## Contributor

<table>
<th>
<div class="profile" align="center">
  <img src="https://avatars.githubusercontent.com/u/115690299?s=400&u=9619ff1251d3f65bdd10824432a7fea1d3b495a6&v=4" width = "70" style = "border-radius: 25px"/>
</div>
<br>
<a href="https://github.com/afterglowss">신혜원</a>
</th>

<th>
<div class="profile" align="center">
  <img src="https://avatars.githubusercontent.com/u/69416899?v=4" width = "70" style = "border-radius: 25px"/>
</div>
<br>
<a href="https://github.com/dnrbs1713">임우균</a>
</th>

<th>
<div class="profile" align="center">
  <img src="https://avatars.githubusercontent.com/u/149660416?v=4" width = "70" style = "border-radius: 25px"/>
</div>
<br>
<a href="https://github.com/pieuniverse">우지원</a>
</th>

<th>
<div class="profile" align="center">
  <img src="https://avatars.githubusercontent.com/u/149660587?v=4" width = "70" style = "border-radius: 25px"/>
</div>
<br>
<a href="https://github.com/o0Orangee">차서영</a>
</th>
</table>




---

## 기여 방법

1. [CONTRIBUTING](https://github.com/afterglowss/MeteorDodgeGamewithShooting/blob/develop/CONTRIBUTING_raylib.md) 문서를 읽어주세요!
2. 이슈를 생성하거나 담당 이슈를 할당받습니다.
3. `feature/*` 브랜치를 생성해 작업합니다.
4. PR 생성 시 템플릿을 활용하여 설명을 작성합니다.
5. 리뷰어가 승인한 뒤 `develop`에 병합합니다.

---
