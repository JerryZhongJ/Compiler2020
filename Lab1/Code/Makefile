# GNU make手册：http://www.gnu.org/software/make/manual/make.html
# ************ 遇到不明白的地方请google以及阅读手册 *************

# 编译器设定和编译选项
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99

# 编译目标：src目录下的所有.c文件
CFILES = $(shell find ./ -name "*.c")
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

parser: syntax $(filter-out $(LFO),$(OBJS))
	$(CC) -o parser $(filter-out $(LFO),$(OBJS)) -lfl

syntax: lexical syntax-c
	$(CC) -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v -t $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean test
test:
	./parser ../Test/test1.1.cmm >../Log/log1.1
	./parser ../Test/test1.2.cmm >../Log/log1.2
	./parser ../Test/test1.3.cmm >../Log/log1.3
	./parser ../Test/test1.4.cmm >../Log/log1.4
	./parser ../Test/test1.5.cmm >../Log/log1.5
	./parser ../Test/test1.6.cmm >../Log/log1.6
	./parser ../Test/test1.7.cmm >../Log/log1.7
	./parser ../Test/test1.8.cmm >../Log/log1.8
	./parser ../Test/test1.9.cmm >../Log/log1.9
	./parser ../Test/testA_1.cmm >../Log/logA_1
	./parser ../Test/testA_2.cmm >../Log/logA_2
	./parser ../Test/testA_3.cmm >../Log/logA_3
	./parser ../Test/testA_4.cmm >../Log/logA_4
	./parser ../Test/testA_5.cmm >../Log/logA_5
	./parser ../Test/testA_6.cmm >../Log/logA_6
	./parser ../Test/testA_7.cmm >../Log/logA_7
	./parser ../Test/testA_8.cmm >../Log/logA_8
	./parser ../Test/testA_9.cmm >../Log/logA_9
	./parser ../Test/testB_1.cmm >../Log/logB_1
	./parser ../Test/testB_2.cmm >../Log/logB_2
	./parser ../Test/testC_1.cmm >../Log/logC_1
	./parser ../Test/testC_2.cmm >../Log/logC_2
clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~
