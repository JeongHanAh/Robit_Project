"""
도서 대출 관리 시스템

리팩터링 포인트 (코드 품질 개선 중심):
1. 인자 개수 검증 로직을 @require_args 데코레이터로 통일 (중복 코드 제거)
2. if-elif 명령어 분기를 딕셔너리 매핑(COMMANDS)으로 통일 (list 핸들러 시그니처도 통일)
3. 함수 시그니처에 타입 힌트 추가
4. 메인 루프에 넓은 예외 처리 추가 (핸들러 내부 예외로 프로그램이 죽지 않도록)

※ 책 이름에 공백이 들어가는 케이스, 데이터 영속성(파일 저장) 등은
  이번 개선 범위에서 의도적으로 제외함 (별도 개선 과제로 분리).
"""

from functools import wraps
from typing import Callable

# 시스템 데이터 초기화
books: dict[str, int] = {}         # {책이름: 남은수량} -> 등록 순서 유지됨
user_loans: dict[str, set[str]] = {}  # {사용자: set(대출한 책이름들)}


def require_args(count: int, usage: str) -> Callable:
    """인자 개수를 검증하는 데코레이터.

    각 handle_* 함수마다 반복되던
    'if len(args) != N: print(ERROR...); return' 패턴을 공통화한다.
    """
    def decorator(func: Callable) -> Callable:
        @wraps(func)
        def wrapper(args: list[str]):
            if len(args) != count:
                print(f"ERROR: 잘못된 명령어 형식입니다. (사용법: {usage})")
                return
            return func(args)
        return wrapper
    return decorator


@require_args(2, "add [책이름] [수량]")
def handle_add(args: list[str]) -> None:
    """책 등록 및 수량 추가"""
    book_name, quantity_str = args
    if not quantity_str.isdigit():
        print("ERROR: 수량은 0 이상의 정수여야 합니다.")
        return

    quantity = int(quantity_str)
    if book_name in books:
        books[book_name] += quantity
    else:
        books[book_name] = quantity


@require_args(2, "borrow [사용자] [책이름]")
def handle_borrow(args: list[str]) -> None:
    """도서 대출"""
    username, book_name = args

    # 1. 책 존재 여부 및 수량 확인
    if book_name not in books or books[book_name] <= 0:
        print(f"ERROR: '{book_name}' 책의 대출 가능한 수량이 없습니다.")
        return

    # 2. 동일 사용자 중복 대출 확인
    if username in user_loans and book_name in user_loans[username]:
        print(f"ERROR: 사용자 '{username}'은(는) 이미 '{book_name}'을(를) 대출 중입니다.")
        return

    # 대출 처리
    books[book_name] -= 1
    if username not in user_loans:
        user_loans[username] = set()
    user_loans[username].add(book_name)
    print(f"SUCCESS: '{username}'님이 '{book_name}'을(를) 대출했습니다.")


@require_args(2, "return [사용자] [책이름]")
def handle_return(args: list[str]) -> None:
    """도서 반납"""
    username, book_name = args

    # 실제 대출 중인지 확인
    if username not in user_loans or book_name not in user_loans[username]:
        print(f"ERROR: 사용자 '{username}'이(가) '{book_name}'을(를) 대출한 기록이 없습니다.")
        return

    # 반납 처리
    books[book_name] += 1
    user_loans[username].remove(book_name)

    # 사용자의 대출 목록이 비었으면 key 삭제
    if not user_loans[username]:
        del user_loans[username]

    print(f"SUCCESS: '{username}'님이 '{book_name}'을(를) 반납했습니다.")


@require_args(1, "status [책이름]")
def handle_status(args: list[str]) -> None:
    """책 상태(남은 수량) 출력"""
    book_name = args[0]
    if book_name not in books:
        print(f"ERROR: '{book_name}'은(는) 존재하지 않는 책입니다.")
    else:
        print(f"{book_name}: 남은 수량 {books[book_name]}권")


@require_args(1, "user [사용자]")
def handle_user(args: list[str]) -> None:
    """사용자의 대출 목록 출력"""
    username = args[0]
    if username not in user_loans or not user_loans[username]:
        print("EMPTY")
    else:
        # 보기 편하게 쉼표로 구분하여 출력
        print(f"{username}의 대출 목록: {', '.join(sorted(user_loans[username]))}")


@require_args(0, "list")
def handle_list(args: list[str]) -> None:
    """전체 책 목록을 등록 순서대로 출력

    (기존에는 main()에서 별도로 인자 검증을 했으나,
     다른 핸들러들과 시그니처/검증 방식을 통일함)
    """
    if not books:
        print("등록된 책이 없습니다.")
        return

    print("--- 전체 도서 목록 (등록 순) ---")
    for book_name, quantity in books.items():
        print(f"- {book_name}: {quantity}권")


# 명령어 분기 매핑 (if-elif 체인 대신 딕셔너리로 관리 -> 명령어 추가/삭제가 쉬움)
COMMANDS: dict[str, Callable[[list[str]], None]] = {
    "add": handle_add,
    "borrow": handle_borrow,
    "return": handle_return,
    "status": handle_status,
    "user": handle_user,
    "list": handle_list,
}


def main() -> None:
    print("도서 대출 관리 시스템이 시작되었습니다. 명령어를 입력하세요. (종료: Exit)")

    while True:
        try:
            line = input(">> ").strip()
        except (KeyboardInterrupt, EOFError):
            print("\n시스템을 종료합니다.")
            break

        if not line:
            continue

        # 공백 기준으로 명령어 분리
        parts = line.split()
        command = parts[0]
        args = parts[1:]

        # Exit는 대소문자 구분 없이 처리 가능하도록 조치
        if command.lower() == "exit":
            print("시스템을 종료합니다.")
            break

        handler = COMMANDS.get(command)
        if handler is None:
            print(f"ERROR: 알 수 없는 명령어 '{command}' 입니다.")
            continue

        # 핸들러 내부에서 예상치 못한 예외가 나더라도 프로그램 전체가 죽지 않도록 보호
        try:
            handler(args)
        except Exception as e:
            print(f"ERROR: 명령 처리 중 예상치 못한 오류가 발생했습니다. ({e})")


if __name__ == "__main__":
    main()