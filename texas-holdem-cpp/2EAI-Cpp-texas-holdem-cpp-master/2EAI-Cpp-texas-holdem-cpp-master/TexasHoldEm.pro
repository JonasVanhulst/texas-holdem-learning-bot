TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

#DEFINES += FULL_PRINT \ DEBUG_PRINT


SOURCES += main.cpp \
	JonasVanhulst.cpp \
	bart.cpp \
	deck.cpp \
	dries.cpp \
	game.cpp \
	hand.cpp \
	jonas.cpp \
	king_of_aces.cpp \
	kobe.cpp \
	miguel.cpp \
	poker_rank.cpp \
	seppe.cpp \
	table.cpp \
	tournament.cpp

HEADERS += \
	JonasVanhulst.h \
	bart.h \
	card.h \
	deck.h \
	dries.h \
	game.h \
	hand.h \
	jonas.h \
	king_of_aces.h \
	kobe.h \
	miguel.h \
	player.h \
	playerid.h \
	poker_rank.h \
	seppe.h \
	table.h \
	tournament.h \
	shootout.h
