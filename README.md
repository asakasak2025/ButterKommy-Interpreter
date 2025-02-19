
# 코미버터-인터프리터

## 개요

코미버터-인터프리터는 간단하게 만들어진 인터프리터임임

- "코미"는 0, "버터"는 1을 지칭하는 2진수 코드를 읽음
- 4비트로 주요 명령어를 구분하고 4비트로 세부 명령어를 구분함
- 변수, 연산, 제어 구조, 입출력 등 기본적인 프로그래밍 기능을 지원함

## 인터프리터 구조

- **Box:** 기계어 코드 저장소
- **Val:** 정수형 변수 저장소
- **Stack:** 흐름 관리

실행 과정:
1. 파일 읽기
2. 코드 파싱 및 저장
3. engene 함수를 통해 코드 해석
4. 메모리 해제

## 지원하는 연산과 명령어

- **선언 (0001):** 숫자 변수, 텍스트 변수 선언
- **연산 (0010):** 사칙연산, 비교연산, 논리연산, 비트연산
- **이동 (0011):** 이동, 조건부 이동, 반복문, 이동후 리턴
- **함수 (0100):** 입출력 함수들

| 바이트 코드 | 인수 갯수 | 설명 |
| :-- | :-- | :-- |
| 0001 0001 | 3 | 변수 선언 가능함, 이름과 2바이트 값을 받음 |
| 0001 0010 | 2 | 문자열 선언 가능함, 이름과 아스키로 받음, NULL받을시 종료 |
| 0010 0001 | 3 | + |
| 0010 0010 | 3 | - |
| 0010 0011 | 3 | * |
| 0010 0100 | 3 | / |
| 0010 0101 | 3 | % |
| 0010 0110 | 3 | == |
| 0010 0111 | 3 | != |
| 0010 1000 | 3 | < |
| 0010 1001 | 3 | <= |
| 0010 1010 | 3 | > |
| 0010 1011 | 3 | >= |
| 0010 1100 | 3 | \|\| |
| 0010 1101 | 3 | \&\& |
| 0010 1110 | 3 | << |
| 0010 1111 | 3 | >> |
| 0011 0001 | 1 | GOTO 지점 생성 |
| 0011 0010 | 1 | GOTO 이동 |
| 0011 0011 | 2 | GOTO 조건부 이동 |
| 0011 0100 | 1 | 조건문, false일시 end까지 이동 |
| 0011 0101 | 1 | 반복문, x번 반복함 (상수 입력) |
| 0011 0110 | 2 | 반복문, x in range y (x, y) (x는 변수, y는 상수) |
| 0011 0111 | 1 | 반복문, while x임 |
| 0011 1001 | 0 | 이동후 리턴, 이동후 end 만나면 복귀함 |
| 0011 1010 | 1 | goto 지점 생성 \& end, 위랑 함수 만들때 쓰삼 |
| 0011 1011 | 0 | 시작점임, 없으면 위에서부터 읽음 |
| 0100 0001 | 1 | print int |
| 0100 0010 | 1 | print string |
| 0100 0011 | 1 | println string |
| 0100 0100 | 1 | get int |
| 0100 0101 | 1 | get char |

## 메모리 관리

메모리 관리는 간략하게 했습니다:

- 변수들은 포인터 연결 리스트 구조로 구현됨
- 문자열 변수와 코드는 1024바이트 크기씩 저장됨
- 제어 흐름을 위한 Stack도 연결 리스트로 구현됨

작은 프로젝트라 선택한 방식인데 실수했다는걸 뼈저리게 느끼면서 작업함

## 예제 코드

간단한? 예제입니다

```
코미코미코미버터 코미코미버터코미 코미코미코미코미 코미코미코미버터

코미버터코미코미 버터코미코미코미
코미버터버터코미 코미버터코미버터
코미버터버터코미 버터버터코미코미
코미버터버터코미 버터버터코미코미
코미버터버터코미 버터버터버터버터
코미코미버터코미 코미코미코미코미
코미버터코미버터 코미버터버터버터
코미버터버터코미 버터버터버터버터
코미버터버터버터 코미코미버터코미
코미버터버터코미 버터버터코미코미
코미버터버터코미 코미버터코미코미
코미코미코미코미 버터코미버터코미
코미코미코미코미 코미코미코미코미

코미버터코미코미 코미코미버터버터 코미코미코미코미 코미코미코미버터
```
"hello world"를 출력합니다.


더 간단한? 예제입니다

```
코미코미코미버터 코미코미코미버터 코미코미코미코미 코미코미코미버터

코미코미코미코미 코미코미코미코미 코미코미코미코미 코미코미코미코미


코미코미코미버터 코미코미코미버터 코미코미코미코미 코미코미버터코미

코미코미코미코미 코미코미코미코미 코미코미코미코미 코미코미코미코미


코미코미코미버터 코미코미코미버터 코미코미코미코미 코미코미버터버터

코미코미코미코미 코미코미코미코미 코미코미코미코미 코미코미코미코미


코미코미코미버터 코미코미코미버터 코미코미코미코미 코미버터코미코미

코미코미코미코미 코미코미코미코미 코미코미코미코미 코미코미코미버터


코미코미코미버터 코미코미코미버터 코미코미코미코미 코미버터코미버터

코미코미코미코미 코미코미코미코미 코미코미코미코미 버터코미코미버터



코미코미코미버터 코미코미버터코미 코미코미코미코미 코미코미버터코미

코미코미버터코미 코미코미코미코미 코미코미코미코미 코미코미코미코미


코미코미코미버터 코미코미버터코미 코미코미코미코미 코미코미버터버터

코미코미코미코미 버터코미버터코미 코미코미코미코미 코미코미코미코미




코미코미버터버터 코미버터버터코미 코미코미코미코미 코미코미코미버터 코미코미코미코미 버터코미코미버터


코미코미버터코미 코미코미코미버터 코미코미코미코미 코미코미코미버터 코미코미코미코미 코미버터코미코미 코미코미코미코미 코미코미코미버터


코미코미버터버터 코미버터버터코미 코미코미코미코미 코미코미버터코미 코미코미코미코미 버터코미코미버터


코미코미버터코미 코미코미코미버터 코미코미코미코미 코미코미버터코미 코미코미코미코미 코미버터코미코미 코미코미코미코미 코미코미버터코미


코미코미버터코미 코미코미버터버터 코미코미코미코미 코미코미버터버터 코미코미코미코미 코미코미코미버터 코미코미코미코미 코미코미버터코미

코미코미버터코미 버터코미코미버터 코미코미코미코미 코미코미버터코미 코미코미코미코미 코미코미버터버터 코미코미코미코미 코미버터코미버터


코미코미버터버터 코미버터코미코미 코미코미코미코미 코미코미버터코미

코미버터코미코미 코미코미버터코미 코미코미코미코미 코미코미버터코미

코미코미버터버터 버터코미코미코미


코미버터코미코미 코미코미코미버터 코미코미코미코미 코미코미버터버터

코미버터코미코미 코미코미버터코미 코미코미코미코미 코미코미버터코미



코미코미버터버터 버터코미코미코미

코미버터코미코미 코미코미버터코미 코미코미코미코미 코미코미버터버터

코미코미버터버터 버터코미코미코미
```
구구단을 출력합니다.

이번엔 진짜로 더 간단한 예제입니다.
```
코미코미코미버터 코미코미코미버터 코미코미코미코미 코미버터버터코미

코미코미코미코미 코미코미코미코미 코미코미코미코미 코미코미코미코미


코미코미코미버터 코미코미코미버터 코미코미코미코미 코미버터버터버터

코미코미코미코미 코미코미코미코미 코미코미코미코미 코미코미코미코미


코미코미코미버터 코미코미코미버터 코미코미코미코미 버터코미코미코미

코미코미코미코미 코미코미코미코미 코미코미코미코미 코미코미코미코미



코미코미코미버터 코미코미버터코미 코미코미코미코미 코미버터코미코미

코미버터버터코미 코미버터코미버터 코미버터버터코미 버터버터버터코미
코미버터버터버터 코미버터코미코미 코미버터버터코미 코미버터코미버터
코미버터버터버터 코미코미버터코미 코미코미버터버터 버터코미버터코미
코미코미버터코미 코미코미코미코미 코미코미코미코미 코미코미코미코미


코미코미코미버터 코미코미버터코미 코미코미코미코미 코미버터코미버터

코미코미버터코미 코미코미코미코미 코미코미버터코미 버터코미버터버터
코미코미버터코미 코미코미코미코미 코미코미코미코미 코미코미코미코미


코미코미코미버터 코미코미버터코미 코미코미코미코미 코미버터버터코미

코미코미버터코미 코미코미코미코미 코미코미버터버터 버터버터코미버터
코미코미버터코미 코미코미코미코미 코미코미코미코미 코미코미코미코미



코미코미코미버터 코미코미버터코미 코미코미코미코미 코미버터버터버터

코미코미코미코미 버터코미버터코미 코미코미코미코미 코미코미코미코미


코미버터코미코미 코미코미버터버터 코미코미코미코미 코미버터버터버터

코미버터코미코미 코미코미버터코미 코미코미코미코미 코미버터코미코미

코미버터코미코미 코미버터코미코미 코미코미코미코미 코미버터버터코미

코미버터코미코미 코미코미버터코미 코미코미코미코미 코미버터코미코미

코미버터코미코미 코미버터코미코미 코미코미코미코미 코미버터버터버터

코미버터코미코미 코미코미버터버터 코미코미코미코미 코미버터버터버터

코미버터코미코미 코미코미코미버터 코미코미코미코미 코미버터버터코미

코미버터코미코미 코미코미버터코미 코미코미코미코미 코미버터코미버터

코미버터코미코미 코미코미코미버터 코미코미코미코미 코미버터버터버터

코미버터코미코미 코미코미버터코미 코미코미코미코미 코미버터버터코미


코미코미버터코미 코미코미코미버터 코미코미코미코미 버터코미코미코미 코미코미코미코미 코미버터버터코미  코미코미코미코미 코미버터버터버터

코미버터코미코미 코미코미코미버터 코미코미코미코미 버터코미코미코미

코미버터코미코미 코미코미버터버터 코미코미코미코미 코미버터버터버터
```
x + y = 를 출력하는 예제입니다. enter: 로 두번 정수를 입력 받습니다.
