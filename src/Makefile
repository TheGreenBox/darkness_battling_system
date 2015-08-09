PRODUCT=product

CC=g++
LIB=
FLAGS=-std=c++11 -Wall -I ../ -I .

app:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/play_icfp2015 \
	app.cpp \
	board.cpp \
	game_session_rules.cpp \
	../lib/json/jsoncpp.cpp \
	game_set_settings.cpp \
	move_operations.cpp \
	segment.cpp \
	unit.cpp

ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
	ut.cpp

clear:
	rm product -r

prepare:
	mkdir product

