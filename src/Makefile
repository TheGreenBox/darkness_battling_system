PRODUCT=product

CC=g++
LIB=
FLAGS=-std=c++11 -Wall

app:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/play_icfp2015 \
	app.cpp

ut:
	${CC} ${FLAGS} ${LIB} -o ${PRODUCT}/ut \
	ut.cpp

clear:
	rm product -r

prepare:
	mkdir product

