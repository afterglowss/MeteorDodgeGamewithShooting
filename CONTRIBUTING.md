# 팀 프로젝트 기여 가이드 (Raylib + Git Flow)

> Raylib 기반 2D 게임 개발 (C 언어)  
> 브랜치 전략: Git Flow (`main`, `develop`, `feature/*`, `release/*`, `hotfix/*`)

---

## 브랜치 전략

| 브랜치       | 용도                         |
|--------------|------------------------------|
| `main`       | 배포 가능한 완성 버전         |
| `develop`    | 최신 개발 통합 브랜치         |
| `feature/*`  | 기능 추가 및 개별 작업         |
| `bugfix/*`      | 버그 수정                    |
| `release/*`  | 릴리스 준비 및 QA             |
| `hotfix/*`   | 긴급 수정 및 배포             |

---

## 브랜치 생성 규칙

- `feature/player-move-8`
- `fix/collision-detect-error-24`
- `asset/background-image-49`
- `release/v1.0.0`
- `hotfix/segmentation-error-77`

---

## 커밋 메시지 규칙 (Conventional Commits)

```
<타입>: <변경 요약> [#이슈번호]
```

| 타입       | 설명             |
|------------|------------------|
| `feat`     | 기능 추가        |
| `fix`      | 버그 수정        |
| `refactor` | 리팩토링         |
| `style`    | 코드 포맷/정리   |
| `docs`     | 문서 수정        |
| `asset`    | 리소스 추가/변경 |
| `chore`    | 설정, 도구 변경  |

**예시**
```
feat: 적 총알 피격 로직 구현 (#12)
fix: 플레이어 체력 바 UI 오류 수정 (#30)
asset: 사운드 이펙트 추가 (#68)
```

---

## PR 작성 및 머지 규칙

- `feature/*` / `fix/*` → `develop`
- `release/*` → `main` + `develop`
- `hotfix/*` → `main` + `develop`
- PR 템플릿 사용 필수

---

## 이슈 등록 가이드

- 작업 단위로 하나씩 생성
- 템플릿 양식을 준수 (설명, 체크리스트 포함)

---

## 팀 커뮤니케이션

- Discord로 PR/이슈 공유
- 협업 규칙은 Notion에 기록
- 소통은 KakaoTalk 사용

---

> 모두가 같은 기준으로 협업하기 위한 가이드입니다. 팀원 모두가 확인해주세요!
