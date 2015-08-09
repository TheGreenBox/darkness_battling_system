PRODUCT=product

CC=g++
LIB=
FLAGS=-std=c++11 -Wall -I ../ -I .

app:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/play_icfp2015 \
	app.cpp \
	board.cpp \
	board_metrics.cpp \
	game_session_rules.cpp \
	../lib/json/jsoncpp.cpp \
	game_set_settings.cpp \
	solution_cmd.cpp \
	coordinate_systems.cpp \
	move_operations.cpp \
	output_format.cpp \
	segment.cpp \
	unit.cpp

ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
	ut.cpp

clear:
	rm product -r

prepare:
	mkdir product

