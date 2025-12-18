
# 인자로 컴파일할 파일을 받습니다. (예: make run F=test.cpp)
# 기본값은 'main.cpp'로 설정합니다. (main.cc를 쓰신다면 F=main.cc로 지정해야 합니다)
F ?= main.cc
TARGET = $(basename $(F))
CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra -pedantic -DDEBUG

# .PHONY: 이 이름들이 실제 파일이 아님을 선언
.PHONY: all run
# 기본 타겟 ('make'만 입력 시)
all: $(TARGET)
# 실행 타겟: 빌드 후 'in' 파일을 입력으로 받아 실행
run: $(TARGET)
	@echo "--- [$(TARGET)] 실행 (입력: 'in' 파일) ---"
	./$(TARGET) < in
	@echo "--- 실행 완료 ---"

# 빌드 타겟: 지정된 단일 .cpp 파일을 직접 실행 파일로 컴파일합니다.
$(TARGET): $(F)
	@echo "컴파일: $(F) -> $(TARGET)"
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(F)

