# Sakiko
あなた、ご自分のことばかりですのね。

# 使用方法
## 配置
`touch config/config.json`

在`config/`里面创建`config.json`。

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

`./Sakichan`

### 参数
`-c`：清空本地记录。
