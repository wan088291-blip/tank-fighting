# ==========================================
# Battle Game Project Makefile
# ==========================================

# 编译器设置
CXX = g++

# 编译选项
# -Wall: 显示所有警告
# -g: 生成调试信息 (用于 gdb)
# -std=c++11: 使用 C++11 标准 (必须，因为用了 auto 等特性)
CXXFLAGS = -Wall -g -std=c++11

# 目标可执行文件名称
TARGET = battle_game

# === 自动源文件列表 ===
# wildcard *.C 会自动查找当前目录下所有的 .C 文件
# 这将自动包含: main.C, GameEngine.C, Enemy.C, GunBoat.C, 
# Shell.C, Missile.C, Player.C 等所有源文件
SRCS = $(wildcard *.C)

# 将源文件列表 (.C) 转换为目标文件列表 (.o)
OBJS = $(SRCS:.C=.o)

# 默认目标 (输入 make 默认执行)
all: $(TARGET)

# 链接阶段：将所有 .o 文件链接为可执行文件
$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 编译阶段：将每个 .C 文件编译为对应的 .o 文件
# $< 代表依赖项 (xxx.C)，$@ 代表目标 (xxx.o)
%.o: %.C
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理构建文件 (输入 make clean 执行)
clean:
	@echo "Cleaning up..."
	rm -f $(OBJS) $(TARGET)

# 伪目标声明 (防止目录下有同名文件导致冲突)
.PHONY: all clean