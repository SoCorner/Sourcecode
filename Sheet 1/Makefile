CFLAGS  = -Wall -Werror -pedantic -O2
GSL_FLAGS = -lgsl -lgslcblas
SRC_PATH = ./src\ tasks/
SRC_MODULES_PATH = ./modules/

C_FILES_TASK_2 = $(SRC_PATH)rejection_sampling.c $(SRC_MODULES_PATH)sampling_methods.c $(SRC_MODULES_PATH)arrayhelpers.c
C_FILES_TASK_4 = $(SRC_PATH)draw_standard_normal_rv.c $(SRC_MODULES_PATH)sampling_methods.c $(SRC_MODULES_PATH)arrayhelpers.c
C_FILES_TASK_6 = $(SRC_PATH)box_muller.c $(SRC_MODULES_PATH)sampling_methods.c $(SRC_MODULES_PATH)arrayhelpers.c
C_FILES_TASK_8 = $(SRC_PATH)estimate_sigma.c $(SRC_MODULES_PATH)sampling_methods.c $(SRC_MODULES_PATH)arrayhelpers.c
C_FILES_TASK_9 = $(SRC_PATH)estimation_error.c $(SRC_MODULES_PATH)sampling_methods.c $(SRC_MODULES_PATH)arrayhelpers.c
C_FILES_TASK_10 = $(SRC_PATH)draw_paths.c $(SRC_MODULES_PATH)sampling_methods.c $(SRC_MODULES_PATH)arrayhelpers.c
C_FILES_TASK_11 = $(SRC_PATH)estimate_gbm_parameter.c $(SRC_MODULES_PATH)sampling_methods.c $(SRC_MODULES_PATH)arrayhelpers.c

task_2: $(C_FILES_TASK_2) $(SRC_MODULES_PATH)sampling_methods.h
	mkdir -p Task\ 2
	gcc $(CFLAGS) $(C_FILES_TASK_2) -o ./Task\ 2/rejection_sampling $(GSL_FLAGS) -lm

task_4: $(C_FILES_TASK_4) $(SRC_MODULES_PATH)sampling_methods.h
	mkdir -p Task\ 4
	gcc $(CFLAGS) $(C_FILES_TASK_4) -o ./Task\ 4/draw_standard_normal_rv $(GSL_FLAGS) -lm

task_6: $(C_FILES_TASK_6) $(SRC_MODULES_PATH)sampling_methods.h
	mkdir -p Task\ 6
	gcc $(CFLAGS) $(C_FILES_TASK_6) -o ./Task\ 6/box_muller $(GSL_FLAGS) -lm

task_8: $(C_FILES_TASK_8) $(SRC_MODULES_PATH)sampling_methods.h
	mkdir -p Task\ 8
	gcc $(CFLAGS) $(C_FILES_TASK_8) -o ./Task\ 8/estimate_sigma $(GSL_FLAGS) -lm

task_9: $(C_FILES_TASK_9) $(SRC_MODULES_PATH)sampling_methods.h
	mkdir -p Task\ 9
	gcc $(CFLAGS) $(C_FILES_TASK_9) -o ./Task\ 9/estimation_error $(GSL_FLAGS) -lm

task_10: $(C_FILES_TASK_10) $(SRC_MODULES_PATH)sampling_methods.h
	mkdir -p Task\ 10
	gcc $(CFLAGS) $(C_FILES_TASK_10) -o ./Task\ 10/draw_paths $(GSL_FLAGS) -lm

task_11: $(C_FILES_TASK_11) $(SRC_MODULES_PATH)sampling_methods.h
	mkdir -p Task\ 11
	gcc $(CFLAGS) $(C_FILES_TASK_11) -o ./Task\ 11/estimate_gbm_parameter $(GSL_FLAGS) -lm
