#ups_monitor_v3 project makefile
#2015.06.12 kimi

ups_monitor_v3.o: ups_monitor_v3.c
	gcc -c ups_monitor_v3.c `pkg-config gtk+-3.0 --cflags --libs` --std c99

dbug:
	gcc ups_monitor_v3.c -static --std c99 `pkg-config gtk+-3.0 --cflags --libs` -o ups_monitor_v3_debug.exe -lwinmm -Wall
exe:
	gcc ups_monitor_v3.c -static --std c99 `pkg-config gtk+-3.0 --cflags --libs` -o ups_monitor_v3.exe -lwinmm -Wall -mwindows