# Sakiko
あなた、ご自分のことばかりですのね。

# 使用方法
## 配置
`mkdir config && touch config/config.json`

在工作目录里创建`config/`，并在里面创建`config.json`。

配置方法如下：

```
{
    "token": <bot_token_here>,
    "gmt": <-12 ~ 12>,
    "local_dir": "../local/"
}
```
## 编译
`mkdir build`

创建`build`目录。

`cd build && cmake .. && make`

编译。
## 运行

`./Sakiko`

`-c`：清空本地记录。
