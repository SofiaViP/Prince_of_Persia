# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRCS = main.c video_gr.c kbd.c utils.c mouse.c timer.c state.c prince.c map.c text.c target.c thief.c rtc.c scoreboard.c princess.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CPPFLAGS += -pedantic

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
