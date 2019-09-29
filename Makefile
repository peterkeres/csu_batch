# peter keres
# sep 28 2019

# this is the make file for the csu batch program

# HOW TO USE MAKE FILES
# at command line in the directory of the project
# if you type in just 'make' it will run the first part of this make file
# aka the part on line 18
# if you type in 'make example' it will run the example code tide to that name
# aka line 22
# you can also have make run mutilple ones at same time
# if you want to comple both example batch fiels at same time
# 'make example example2'

# this is the default, run this to compile whole code base needed
csubatch: 4175proj1.c schedule_model.c JobQueue.c	dispatching_model.c commandline.c
	gcc 4175proj1.c schedule_model.c JobQueue.c	dispatching_model.c commandline.c	-o csubatch	-lpthread

# this will create the first example batch program
example: example_batch.c
	gcc -Wall example_batch.c -o example_batch

# this will create the second example batch program
example2: example_batch2.c
	gcc -Wall example_batch2.c -o example_batch2

# this will delete the excuatbles for our main program and the 2 examples
clear:
	rm csubatch example_batch example_batch2
