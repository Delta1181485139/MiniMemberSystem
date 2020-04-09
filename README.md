# MiniMemberSystem
the first time to develop a mini GUI program by Qt 

# 项目开发工具

- Qt 5.9.0 MinGW 32bit
- 数据库：Microsoft SQL Server 2017
- 编译器：MinGW 5.3.0 32bit for C++

# 项目组成员

单人（之前忘记组队了）

# 安装&配置

## 数据库部分（以SQLsever为例）

### 建表

1. 建立数据库并创建表格的sql语句在文件 **createBD.sql** 中。
2. 在sqlsever中新建用户，并选择以sqlsever登录验证方式登录，解除勾选以强制密码登录。在选项页——用户映射中，选择需要映射的数据库。
3. 在数据库——安全性——用户——用户名——属性中，选择数据库角色成员身份。
4. 由此便可以通过刚才新建的用户名来访问数据库了。

### 新建数据源

1. 确保1433端口开启，这个是SQLsever默认的服务端口。
2. 打开SQLsever的配置管理器，选择severSQL网络配置，启用TCP/IP服务，右键打开属性将IP地址窗口最下面的IPALL的TCP窗口设置为1433。
3. 由于与SQLsever连接的接口是ODBC，因此打开ODBC数据源管理器，选择add添加新的数据源，选择SQLsever。
4. 填写数据源的基本信息，其中Name是数据源名称，后面在Qt中会用到，sever里填SQLsever对应的服务器名。
5. 再下一步选择要连接的数据库作为默认数据库。

## Qt部分

### 连接数据库

只需要在源文件**global.cpp**中将以下四个属性修改即可。

```cpp
//数据源名称
extern const QString dsn = "ManagementSys";
//服务器地址
extern const QString hostname = "127.0.0.1";
//数据库登录的用户名
extern const QString username = "uzi";
//密码
extern const QString password = "vn";
```

### 项目打包

- 首先在Release模式下将代码跑一遍，在根目录中出现可执行文件(.exe)。将该文件复制到一个目录下。
- 打开Qt的命令行窗口(Qt5.9 for Desktop)，进入到该目录。
- 输入命令：```windeployqt [文件名.exe]```
- 这时会发现所有的依赖文件将会自动生成在文件夹内。直接双击程序的对应图标就可以执行了。

# 业务功能介绍

## 登录界面

![image-20200409163452630](D:\Qt\memberManagementSystem\login_show.png)

> 在此输入用户名和密码，如果是管理员则要勾选**我是管理员**选项，否则会显示用户名或密码错误。如果没有账号，可以点击注册按钮。

![image-20200409163810955](D:\Qt\memberManagementSystem\register_show.png)

> 在此输入希望注册的用户名和密码，如果用户名重复，将会显示用户名已存在。注册后的用户均为普通用户，新增管理员用户还得直接用数据库。

## 管理员界面

![image-20200409164054401](D:\Qt\memberManagementSystem\admin_login_show.png)

> 输入管理员账号与密码，勾选**我是管理员**，可进入管理员界面。

### 管理所有人

![image-20200409164245262](D:\Qt\memberManagementSystem\admin_index_show.png)

> - 进入主页默认是管理所有人的窗口。
> - **查找操作**在这里首先可以通过用户名查找某个用户，并显示其信息在主窗口。
> - **删号操作：**鼠标选定用户（或者CTRL+左键）选中多个用户，点击删号，这时候用户名的左边会出现感叹号，如果点击撤销修改，感叹号会消失，如果点击保存修改，才会真正删除用户账号。

### 审核用户的动态

![image-20200409165058766](D:\Qt\memberManagementSystem\admin_review_show.png)

> - 点击待审核，在主窗口将会出现所有用户新发表的动态，需要经过管理员的审核才能够向所有人展示。
> - **通过审核**，选中整行需要通过的动态（也能够通过CTRL+鼠标左键多选），点击通过，此时选中的所有行的序号和列名将会加粗显示。如果点击撤销修改，则通过失败，如果点击保存修改，则通过成功，所有选中的动态都将消失，并显示在已通过那一栏中。

![image-20200409165627122](D:\Qt\memberManagementSystem\admin_reviewed_show.png)

> 在选择已通过按钮之后，会在主窗口展示所有人都可见的动态，并能够删除，删除的具体操作和之前的通过操作和删号操作是一样的。

## 普通用户界面

![image-20200409170032230](D:\Qt\memberManagementSystem\user_index_show.png)

> 在登陆界面取消勾选**我是管理员**按钮，输入正确的用户名和密码，将会进入普通用户界面。在页眉将会有欢迎提示，和上一次的登出时间（第一次登录则不显示）。主窗口默认展示的是本用户以往所发表的所有动态。

### 修改密码

![image-20200409170339349](D:\Qt\memberManagementSystem\user_changePwd_show.png)

> 点击修改密码将会弹出窗口，用户需要在正确填入原密码，并保证两次输入的新密码相同之后，可成功修改密码。

### 个性签名

![image-20200409170834273](D:\Qt\memberManagementSystem\user_signature_show.png)

点击个性签名旁的编辑按钮，可以进行编辑个性签名，字数限定32个字。

### 发布动态

![image-20200409171115767](D:\Qt\memberManagementSystem\user_editMoment_show.png)

> 在主界面的上方文字编辑框内可以输入动态，限定字数200字以内，点击发布之后，动态将会新增到我的动态列表中。但一分钟内只能发布一条动态，否则会被系统警告。

![image-20200409171213449](D:\Qt\memberManagementSystem\user_review_show.png)

> 正文下方将会显示待审核，在管理员审核之前，其他的用户是看不到该动态的。

### 查看其他人动态

![image-20200409171407727](D:\Qt\memberManagementSystem\user_explore_show.png)

> 点击**发现**按钮，主窗口将会显示系统中所有用户所发布，并通过管理员审核的动态。

### 删除动态

![image-20200409171655876](D:\Qt\memberManagementSystem\user_delete_show.png)

> 用户只能够删除自身发布的动态，并按照发布时间来删除，操作比管理员稍微复杂。删除操作成功之后，记录将会从**我的发布**和**发现**中消失。

# 结语

由于对Qt中的组件不太熟悉，导致界面做的比较丑。数据库方面我自定义了一个专门与数据库通信的类，还是感觉代码很冗杂，不够优雅。

BUG方面目前好像没发现什么大的BUG。有一个管理员在进行修改操作之后，无法再次选中新的行，必须重新点击相关的展示按钮，才可以再次选中。还有就是这个系统是单线程的，没有考虑多用户同时操作，如果同时登录多个普通用户窗口，同时发布动态，第一个用户的动态发出去之后，后面用户的动态要隔一分钟才能继续发出去。

另外，其实最好把源代码里面数据库设置的那一块封装成用户接口，这样其实就不需要修改源代码，可以在图形界面中设置数据库并连接了。

所以总的来说这算是一个Qt的入门小项目吧。