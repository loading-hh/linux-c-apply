# 1.
# 声明需要的cmake的最低版本，不写并不会报错，但是可能会有警告
cmake_minimum_required(VERSION 3.16.3)


message(adflkj)

# 2.
# 定义工程名称，并可指定工程的版本、工程描述、web主页地址、支持的语言（默认情况支持所有语言），
# 如果不需要这些都是可以忽略的，只需要指定出工程名字即可。
project(test)

# 3.1
# SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])，[] 中的参数为可选项, 如不需要可以不写。
    # VAR：变量名。可大写可小写。
    # VALUE：变量值。
# 五个源文件需要反复被使用，每次都直接将它们的名字写出来确实是很麻烦，此时我们就需要定义一个变量，
# 将文件名对应的字符串存储起来，在cmake里定义变量需要使用set。各个源文件之间使用空格或;间隔
# 变量的使用是${变量名}
# set(SRC main.c;add.c;sub.c;mult.c;div.c)

# 3.2
# set还可对固定宏设置值。如EXECUTABLE_OUTPUT_PATH是指定生成的可执行文件的路径。
# 路径中的文件不存在时，会默认生成文件夹。
set(EXECUTABLE_OUTPUT_PATH /home/loading/linux-c-apply/cmake练习/3)

# 4.1
# aux_source_directory(< dir > < variable >),命令可以查找某个路径下的所有源文件
    # dir：要搜索的目录。PROJECT_SOURCE_DIR宏是cmake命令要找的的CMakeLists.txt的目录，也可自己写目录。
    # variable：将从dir目录下搜索到的源文件列表存储到该变量中
# aux_source_directory(/home/loading/linux-c-apply/cmake练习/3/src SRC)

# 4.2
# file(GLOB/GLOB_RECURSE 变量名 要搜索的文件路径和文件类型)
    # GLOB: 将指定目录不包括指定目录下的子目录下搜索到的满足条件的所有文件名生成一个列表，并将其存储到变量中。
    # GLOB_RECURSE: 将指定目录包括指定目录下的子目录下搜索到的满足条件的所有文件名生成一个列表，并将其存储到变量中。
    # CMAKE_CURRENT_SOURCE_DIR 宏表示当前访问的 CMakeLists.txt 文件所在的路径。
file(GLOB SRC /home/loading/linux-c-apply/cmake练习/3/main.c)
# 这个是搜索头文件。
# file(GLOB SRC_H /home/loading/linux-c-apply/cmake练习/3/inclue/*.h)

# 5.
# 很多时候源文件对应的头文件不在一个目录下，所以需要将源文件对应的头文件指定出来，
# 这样才能保证在编译过程中编译器能够找到这些头文件，并顺利通过编译。
# include_directories(headpath)
    # headpath：头文件路径
include_directories(/home/loading/linux-c-apply/cmake练习/3/include)

# 6.
# 生成动静/态库
# add_library(库名称 STATIC/SHARED 源文件1 [源文件2] ...)
    # STATIC：生成静态库。
    # SHARED：生成动态库。
# add_library(mylib SHARED ${SRC})
# set(LIBRARY_OUTPUT_PATH /home/loading/linux-c-apply/cmake练习/3/lib)

# 7.
# 连接动/静态库
# link_libraries(<static lib> [<static lib>...])
# link_libraries(libmylib.a)

# 8.
# 包含路径
# link_directories(<lib path>)
link_directories(/home/loading/linux-c-apply/cmake练习/3/lib)

# 9.
# add_executable(可执行程序名 源文件名称)。定义工程会生成一个可执行程序，源文件不能为.h和.txt等文件。
# 这里的可执行程序名和project中的项目名没有任何关系
# 源文件名可以是一个也可以是多个，如有多个可用空格或;间隔
add_executable(main ${SRC})

# 10.
# 连接动态库
# target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> <item>... [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)
target_link_libraries(main libmylib.so)
