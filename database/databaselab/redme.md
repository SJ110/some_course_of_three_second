  一个简易的仓库管理系统，基于mysql和qt实现。需要再qt动态链接库中包含以上两个文件 libmysql.dll
和libmysql.lab。
需要在.pro中加入
QT+=sql

CONFIG +=console

DISTFILES +=

RESOURCES += \
    background.qrc
界面比较简陋，但是可以应付课设。  完成度还行