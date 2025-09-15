# 声明需要的cmake的最低版本，不写并不会报错，但是可能会有警告
cmake_minimum_required(VERSION 3.16.3)

# 定义工程名称，并可指定工程的版本、工程描述、web主页地址、支持的语言（默认情况支持所有语言），
# 如果不需要这些都是可以忽略的，只需要指定出工程名字即可。
project(test)

# SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])，[] 中的参数为可选项, 如不需要可以不写
# VAR：变量名。可大写可小写。
# VALUE：变量值。
# 五个源文件需要反复被使用，每次都直接将它们的名字写出来确实是很麻烦，此时我们就需要定义一个变量，
# 将文件名对应的字符串存储起来，在cmake里定义变量需要使用set。各个源文件之间使用空格或;间隔
# 变量的使用是${变量名}
set(SRC main.c;add.c;sub.c;mult.c;div.c)

# set还可对固定宏设置值。如EXECUTABLE_OUTPUT_PATH是指定生成的可执行文件的路径。
# 路径中的文件不存在时，会默认生成文件夹。
set(EXECUTABLE_OUTPUT_PATH /home/loading/linux-c-apply/cmake练习/1)

# add_executable(可执行程序名 源文件名称)。定义工程会生成一个可执行程序
# 这里的可执行程序名和project中的项目名没有任何关系
# 源文件名可以是一个也可以是多个，如有多个可用空格或;间隔
add_executable(test ${SRC})