#初级写法
#main: main.c printf.c 
#	gcc main.c printf.c -o main
#clean:
#	rm main


#改进写法
#main: main.o printf.o
#	gcc main.o printf.o -o main
#main.o: main.c
#	gcc -c main.c -o main.o
#printf.o: printf.c
#	gcc -c printf.c -o printf.o
#clean: 
#	rm main *.o



#多文件改进写法
#自定义变量的声明
#compile=gcc #编译器的类型
#exec=main   #可执行的目标文件名
#obj=main.o printf.o #依赖的文件名
#cflags=-Wall -g  #警告级别
#
#${exec}: ${obj}
#	${compile} ${obj} -o ${exec} ${cflags}
#main.o: main.c
#	${compile} -c main.c -o main.o  ${cflags}
#printf.o: printf.c
#	${compile} -c printf.c -o printf.o  ${cflags}
#clean: 
#	rm ${exec} *.o
#	echo ${PWD}     #系统环境变量



#改进版
#预定义变量的声明的使用
#自定义变量的声明
#compile=gcc #编译器的类型
#exec=main   #可执行的目标文件名
#obj=main.o printf.o #依赖的文件名
#cflags=-Wall -g  #警告级别
#${exec}: ${obj}
#	${compile} $^ -o $@ ${cflags}
#main.o: main.c
#	${compile} -c $< -o $@  ${cflags}
#printf.o: printf.c
#	${compile} -c $< -o $@  ${cflags}
#clean: 
#	rm ${exec} *.o


#改进版
#预定义变量的声明的使用
#自定义变量的声明
compile=gcc #编译器的类型
exec=main   #可执行的目标文件名
obj=main.o printf.o #依赖的文件名
cflags=-Wall -g  #警告级别

${exec}: ${obj}
	${compile} $^ -o $@ ${cflags}
%.o: %.c
	${compile} -c $< -o $@  ${cflags}
clean: 
	rm ${exec} *.o
