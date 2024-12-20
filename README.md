![logo](./img/title.png)\
**Computer Room Control Software Nemesis: 轻松破解机房控制.**\
©️ 2023 - present MaxLHy0424.

# 📦 获取

| 分支    | 最新发行版                                                                     | 状态         | 生命周期                |
| ------- | ------------------------------------------------------------------------------ | ------------ | ----------------------- |
| CRCSN 1 | [v1.0_Stable](https://github.com/MaxLHy0424/CRCSN/releases/tag/v1.0_Stable)    | ❌ 停止更新   | 2023/12/17 ~ 2023/12/18 |
| CRCSN 2 | [v2.5_Stable](https://github.com/MaxLHy0424/CRCSN/releases/tag/v2.5_Stable)    | ❌ 停止更新   | 2024/01/01 ~ 2024/01/07 |
| CRCSN 3 | [v3.0.1 (Build 30174)](https://github.com/MaxLHy0424/CRCSN/releases/tag/30174) | ❌ 停止更新   | 2024/02/09 ~ 2024/02/10 |
| CRCSN 4 | [v4.10.7](https://github.com/MaxLHy0424/CRCSN/releases/tag/v4.10.7)            | ❌ 停止更新   | 2024/03/26 ~ 2024/06/19 |
| CRCSN 5 | [v5.11.1](https://github.com/MaxLHy0424/CRCSN/releases/tag/v5.11.1)            | ♻️ 仅常规更新 | 2024/08/25 ~ 2024/12/31 |
| CRCSN 6 | 🔒 尚未推出                                                                     | 🛠️ 正在开发   | 尚未确定                |

相关链接:

- [GitHub Repository Release](https://github.com/MaxLHy0424/CRCSN/releases);
- [中国大陆云盘镜像站点 (不含预发行版)](https://pan.huang1111.cn/s/y548jt6).

# 📖 使用指南

> [!NOTE]
> 适用于 v5.11.1.

## 0 开始之前

**使用 CRCSN 时建议关闭防病毒软件. 若 CRCSN 被报为恶意软件, 请在防病毒软件中添加排除项.**

**请勿使用 CRCSN 扰乱课堂纪律, 造成的后果与开发者无关.**

## 1 启动

> [!IMPORTANT]
> 启动脚本已进入维护阶段, 不再添加新功能.

一般情况下, 运行 `launcher.cmd` 即可启动 CRCSN.

如果默认的启动方式不满足您的需求, 可以根据下文修改.

### 1.1 修改 Runtime

找到:
```dos
set launch.runtime=ucrt
```

CRCSN 支持的 Runtime 如下:
- `ucrt` (默认, 推荐): 开发工具链为 *MSYS2* `mingw-w64-ucrt-x86_64-toolchain`, Runtime 为新式的 *Universal C Runtime*, 支持 Windows 10 以上的 Windows OS (部分 Windows OS 在安装最新补丁后可以运行).
- `msvcrt`: 开发工具链为 *MSYS2* `mingw-w64-x86_64-toolchain`, Runtime 为老旧的 *Microsoft Visual C Runtime*, 支持大部分 Windows OS.

根据上述内容, 选择需要版本的对应字符串替换即可.

### 1.2 自动启动

启用时, 将会直接启动 CRCSN, 无需确认.

找到:
```dos
set config.auto_launch=0
```

将等号后面的数字改为 `0` 之外的其他数字, 即可启用. 禁用只需改回去即可.

### 1.3 详细信息

启用时, 启动脚本将会输出 CRCSN 二进制文件的详细信息.

找到:
```dos
set config.show_verbose_info=0
```

将等号后面的数字改为 `0` 之外的其他数字, 即可启用. 禁用只需改回去即可.

### 1.4 窗口操作

> [!IMPORTANT]
> 此参数区分大小写.

找到:
```dos
set launch.args=
```

窗口操作的主参数为 `-W`, 附加参数如下:
- `f`: 置顶窗口并每间隔 100ms 将窗口设为焦点;
- `t`: 将窗口不透明度设为 90% (仅支持新版控制台);
- `c`: 允许缩放 / 最大化 / 最小化窗口 (可能导致意外行为).

可以有多个附加参数, 其顺序不影响应用效果, 但不可以仅使用主参数.

使用示例:
```dos
set launch.args=-Wtf
```

### 1.5 深度自定义

启动脚本的本质是 Windows 命令脚本, 可以根据需求深度自定义.

## 2 功能使用及说明

### 2.1 快捷操作

位于 CRCSN 标题下方. 通过鼠标点击按钮 `< 退出` 可以直接退出 CRCSN , 点击 `> 信息` 查看软件信息.

### 2.2 破解 & 恢复

位于 "快捷操作" 区域下方.

使用鼠标在 `[破解]` 下点击需要破解的控制软件, 以禁用破解. 如需恢复, 可以在 `[恢复]` 下点击需要恢复的控制软件, 即可恢复控制. 如果 `[破解]` 和 `[恢复]` 下的控件点击后输出 `(i) 需要管理员权限.`, 则请以管理员权限重新启动 CRCSN .

# 🛠️ 下一个主要更新

> [!NOTE]
> 正在准备 CRCSN 的下一个主要更新! 如果有什么建议, 欢迎在 GitHub Repository Issues 中提出.

### 基本完成 / 正在开发

- 弃置命令行参数, 使用配置文件;
- 新的配置选项;
- 新的初始化流程;
- 保护 CRCSN 运行环境;
- 重新添加工具箱;
- 自定义破解/恢复规则;
- 重绘图标;
- 自动申请管理员权限;
- 优化操作体验.

### 计划执行

- 支持 i686 架构;
- 移除 `launcher.cmd`.

### 正在讨论

- **[弃置]** 添加命令行模式;
- **[弃置]** 使用 Windows API 代替 Windows 命令调用.

# 📜 许可证

CRCSN 使用 [MIT License](./LICENSE), 详细内容请自行阅读.

# ❓ 常见问题

## 1 CRCSN 无法非 x86_64 架构的 Windows OS 中使用.

受限于开发工具链, 构建出的二进制文件架构仅支持 x86_64 架构.

## 2 运行 CRCSN 时控制台总是输出 "命令提示符已被管理员禁用", 无法正常使用.

可以运行注册表编辑器, 定位到 `HKEY_CURRENT_USER\Software\Policies\Microsoft\Windows\System` 下, 看看有没有一个叫 `DisableCMD` 的值, 有的话就删掉, 再试试.

## 3 破解后一些软件运行时报错 "找不到文件".

在不影响软件正常运行的情况下, 可以给软件文件修改一个名称, 再试试. 或者打开注册表编辑器, 定位到 `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options`, 找到和要运行的软件的文件名称相同的项, 删除即可.

# ❤️ 鸣谢

- Bilibili 用户 [lateworker_晚工](https://space.bilibili.com/454920362) 提供界面代码 (详见[此处](https://www.bilibili.com/video/BV1X14y1n7S4), 有修改);
- Bilibili 用户 [痕继痕迹](https://space.bilibili.com/39337803) 指导界面设计;
- GitHub 用户 [Zhu-Xinrong (Kendall)](https://github.com/Zhu-Xinrong) 指导图标设计.
