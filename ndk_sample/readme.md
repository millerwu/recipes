### NDK SAMPLE
#### ndk-build
ndk-build 脚本可用于便于采用 NDK 基于 Make 的编译系统项目。

运行 ndk-build 脚本相当于运行了以下命令：
```
$GNUMAKE -f <ndk>/build/core/build-local.mk
<parameters>
```
ndk-build 脚本位于 NDK 安装目录的顶层，要从命令行运行该脚本，请在应用项目目录或者其子目录进行调用：

```
$ cd <project>
$ <ndk>/ndk-build
```
project 指向项目的根目录，ndk 则是安装 NDK 的目录

#### ndk-build 常用选项

##### clean
移除之前生成的所有二进制文件

##### V=1
启动编译，并显示编译命令，对于查看问题时非常有帮助

##### -B
强制执行完整的重新编译

其他的选项可以使用 ndk-build -h 来进行查看


