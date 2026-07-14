import sys

# 시스템 데이터 초기화
books = {}       # {책이름: 남은수량} -> 등록 순서 유지됨
user_loans = {}  # {사용자: set(대출한 책이름들)}


def handle_add(args):
    """책 등록 및 수량 추가"""
    if len(args) != 2:
        print("ERROR: 잘못된 명령어 형식입니다. (사용법: add [책이름] [수량])")
        return

    book_name, quantity_str = args
    if not quantity_str.isdigit():
        print("ERROR: 수량은 0 이상의 정수여야 합니다.")
        return

    quantity = int(quantity_str)
    if book_name in books:
        books[book_name] += quantity
    else:
        books[book_name] = quantity


def handle_borrow(args):
    """도서 대출"""
    if len(args) != 2:
        print("ERROR: 잘못된 명령어 형식입니다. (사용법: borrow [사용자] [책이름])")
        return

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


def handle_return(args):
    """도서 반납"""
    if len(args) != 2:
        print("ERROR: 잘못된 명령어 형식입니다. (사용법: return [사용자] [책이름])")
        return

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


def handle_status(args):
    """책 상태(남은 수량) 출력"""
    if len(args) != 1:
        print("ERROR: 잘못된 명령어 형식입니다. (사용법: status [책이름])")
        return

    book_name = args[0]
    if book_name not in books:
        print(f"ERROR: '{book_name}'은(는) 존재하지 않는 책입니다.")
    else:
        print(f"{book_name}: 남은 수량 {books[book_name]}권")


def handle_user(args):
    """사용자의 대출 목록 출력"""
    if len(args) != 1:
        print("ERROR: 잘못된 명령어 형식입니다. (사용법: user [사용자])")
        return

    username = args[0]
    if username not in user_loans or not user_loans[username]:
        print("EMPTY")
    else:
        # 보기 편하게 쉼표로 구분하여 출력
        print(f"{username}의 대출 목록: {', '.join(sorted(user_loans[username]))}")


def handle_list():
    """전체 책 목록을 등록 순서대로 출력"""
    if not books:
        print("등록된 책이 없습니다.")
        return
        
    print("--- 전체 도서 목록 (등록 순) ---")
    for book_name, quantity in books.items():
        print(f"- {book_name}: {quantity}권")


def main():
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
        if command.lower() == 'exit':
            print("시스템을 종료합니다.")
            break

        # 명령어 분기 매핑
        if command == 'add':
            handle_add(args)
        elif command == 'borrow':
            handle_borrow(args)
        elif command == 'return':
            handle_return(args)
        elif command == 'status':
            handle_status(args)
        elif command == 'user':
            handle_user(args)
        elif command == 'list':
            if args: # list 뒤에 인자가 붙은 경우 에러 처리
                print("ERROR: 잘못된 명령어 형식입니다. (사용법: list)")
            else:
                handle_list()
        else:
            print(f"ERROR: 알 수 없는 명령어 '{command}' 입니다.")


if __name__ == "__main__":
    main()