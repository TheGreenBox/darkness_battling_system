PRODUCT=product

CC=g++
LIB=
FLAGS=-std=c++11 -Wall -I ../.. -I .. -I .

ut: game_session_rules_ut

game_session_rules_ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
	game_session_rules_ut.cpp \
	../../lib/json/jsoncpp.cpp \
	../board.cpp \
	../game_session_rules.cpp \
	../game_set_settings.cpp \
	../move_operations.cpp \
	../segment.cpp \
	../unit.cpp

clear:
	rm product -r

prepare:
	mkdir product

