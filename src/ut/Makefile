PRODUCT=product

CC=g++
LIB=
FLAGS=-std=c++11 -Wall -I ../.. -I .. -I .

ut: game_session_rules_ut board_ut coordinate_systems_ut movement_ut
	${PRODUCT}/game_session_rules_ut
	${PRODUCT}/board_ut
	${PRODUCT}/coordinate_systems_ut
	${PRODUCT}/movement_ut

game_session_rules_ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/game_session_rules_ut \
	game_session_rules_ut.cpp \
	../../lib/json/jsoncpp.cpp \
	../board.cpp \
	../game_session_rules.cpp \
	../game_set_settings.cpp \
	../move_operations.cpp \
	../segment.cpp \
	../unit.cpp \
	../coordinate_systems.cpp

board_ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/board_ut \
	board_ut.cpp \
	../board.cpp \
	../move_operations.cpp \
	../segment.cpp \
	../unit.cpp \
	../coordinate_systems.cpp

coordinate_systems_ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/coordinate_systems_ut \
	coordinate_systems_ut.cpp \
	../coordinate_systems.cpp

movement_ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/movement_ut \
	movement_ut.cpp \
	../move_operations.cpp \
	../segment.cpp \
	../unit.cpp \
	../coordinate_systems.cpp


clear:
	rm product -r

prepare:
	mkdir product

