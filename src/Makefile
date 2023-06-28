.PHONY: test

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TEST_FLAGS = `pkg-config --cflags --libs check` -lm -lcheck
MODEL_FILES = $(wildcard Model/*.c)
TEST_FILES = $(wildcard Tests/*.c)

all:
	$(MAKE) clean
	$(MAKE) uninstall
	$(MAKE) install

install:
	$(MAKE) uninstall
	mkdir SmartCalc
	cd SmartCalc && cmake -B build "../View/" && make -C build SmartCalc

uninstall:
	rm -rf SmartCalc

launch:
	open SmartCalc/build/SmartCalc.app

dvi:
	open documentation.md

dist:
	 tar -cf SmartCalc.tar SmartCalc

test:
	 $(MAKE) clean
	 $(CC) $(CFLAGS) $(TEST_FILES) $(MODEL_FILES) $(TEST_FLAGS) -o test
	 ./test

gcov_report:
	 $(MAKE) clean
	 $(CC) $(CFLAGS) $(TEST_FILES) $(MODEL_FILES) -coverage $(TEST_FLAGS) -o gcovreport
	 ./gcovreport
	 lcov -t "gcovreport" -o gcovreport.info -c -d .
	 genhtml -o report gcovreport.info
	 @rm -rf *.a *.info *.gcda *.gcno gcovreport

style:
	 clang-format -style=Google -i Model/*.c Model/*.h View/*.cpp View/*.h Tests/*.c Tests/*.h

clean:
	 @rm -rf *.o *.a report *.gcno *.gcda  *.tar SmartCalc test gcovreport