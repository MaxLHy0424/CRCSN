<div align="center">

![logo](./img/title_next.png)\
**Computer Room Control Software Nemesis**\
**轻松破解机房控制**\
©️ 2023 MaxLHy0424. All Rights Reserved.

</div>

# 📦 获取

| 分支 | 最新版本 | 状态 | 最新发行版 |
| - | - | - | - |
| CRCSN 1 | v1.0_Stable | ❌ 停止维护 | [📋 更新日志](https://github.com/MaxLHy0424/CRCSN/releases/tag/v1.0_Stable) |
| CRCSN 2 | v2.5_Stable | ❌ 停止维护 | [📋 更新日志](https://github.com/MaxLHy0424/CRCSN/releases/tag/v2.5_Stable) |
| CRCSN 3 | v3.0.1 (Build 30174) | ❌ 停止维护 | [📋 更新日志](https://github.com/MaxLHy0424/CRCSN/releases/tag/30174) |
| CRCSN 4 | v4.10.7 | ❌ 停止维护 | [📋 更新日志](https://github.com/MaxLHy0424/CRCSN/releases/tag/v4.10.7) |
| CRCSN 5 | v5.10.2 | 🛠️ 正常更新 | [📋 更新日志](https://github.com/MaxLHy0424/CRCSN/releases/tag/v5.10.2) |
| CRCSN 6 | 无 | ✨ 正在开发 | 🔒 即将退出 |
| CRCSN Core | 无 | ✨ 正在开发 | 🔒 即将退出 |

相关链接:

- [GitHub Repository Release](https://github.com/MaxLHy0424/CRCSN/releases);
- [中国大陆云盘镜像站点 (不含预发行版)](https://pan.huang1111.cn/s/y548jt6).

# 📖 使用指南

**使用 CRCSN 时建议关闭防病毒软件. 若 CRCSN 被报为恶意软件, 请添加排除项.**

> [!NOTE]
> 适用于 v6.0.0-preview.2.

## 0 开始之前

**CRCSN 仅供学习交流用途, 请勿扰乱课堂纪律, 造成的后果与开发者无关.**

## 1 启动

CRCSN 发行版文件名规则为 `[tag]-[arch]-[runtime].exe`, 其中 `[tag]` 一般为 `std`, `[arch]` 一般为 `x86_64`, `[runtime]` 一般为 `ucrt` 或 `msvcrt`.

两个 `[runtime]` 的具体信息如下:
- **`ucrt` (默认, 推荐)**\
  开发工具链为 *MSYS2* `mingw-w64-ucrt-x86_64-toolchain`, Runtime 为新式的 *Universal C Runtime*, 支持 Windows 10 以上的 Windows OS (部分 Windows OS 在安装最新补丁后可以运行).
- **`msvcrt`**\
  开发工具链为 *MSYS2* `mingw-w64-x86_64-toolchain`, Runtime 为老旧的 *Microsoft Visual C Runtime*, 支持大部分 Windows OS.

## 2 退出 & 重新启动 & 命令提示符

- **退出 CRCSN**\
  `< 退出`
- **重新启动 CRCSN**\
  `< 重启`
- **启动命令提示符**\
  `> 命令提示符`

功能和字面意思一样.

## 3 CRCSN 信息

- **查看 CRCSN 发行版信息**\
  `> 关于`

查看运行的 CRCSN 发行版的相关信息.

## 4 配置 CRCSN

- **进入配置编辑页面**\
  `> 配置`

### 4.1 配置操作

- **同步已保存的配置和暂存区配置**\
  `< 同步配置并返回`
- **使用默认软件打开配置文件**\
  `> 打开配置文件`

### 4.2 常规设置

所有常规设置可在配置页面中修改.

- **隐藏窗口关闭控件 (下次启动时生效)**\
  [作用] 隐藏窗口控件中的关闭按钮.
- **增强窗口 (下次启动时生效)**\
  [作用] 将窗口不透明度设为 90% 并强制置顶窗口.
- **增强操作**\
  [作用] 破解/恢复时将映像劫持可执行文件, 并禁用相关服务

### 4.3 自定义规则

在执行从自定义规则破解/恢复时使用自定义规则.

#### 4.3.1 可执行文件

配置文件中标签 `<rule_exe>` 到下一个标签的部分.

可执行文件后面没有 `.exe` 扩展名.

示例:
```ini
<rule_exe>
abc_client_gui
abc_client_server
abc_protect_server
```

#### 4.3.2 服务

配置文件中标签 `<rule_svc>` 到下一个标签的部分.

每项规则为服务名称, 非显示名称.

示例:
```ini
<rule_svc>
abc_network
abc_diag_track
```

## 5 破解/恢复

- **破解控制**\
  `[破解]`
- **恢复控制**\
  `[恢复]`

每个控制软件有独立的破解/恢复选项, 可根据需求运行.

`[破解]`/`[恢复]` 下的 `> 自定义` 将执行自定义规则, 可参阅 [4.3 自定义规则](#43-自定义规则).

当启用 "增强操作" (详见 [4.2 常规设置](#42-常规设置)) 时, 破解/恢复时将映像劫持可执行文件, 并禁用相关服务.

# 📜 许可证

CRCSN 使用 [MIT License](./LICENSE), 详细内容请自行阅读.

# ❓ 常见问题

## 1 软件无法非 x86_64 架构的 Windows OS 中使用.

受限于开发工具链, 构建出的二进制文件架构仅支持 x86_64 架构.

## 2 运行软件时控制台总是输出 "命令提示符已被管理员禁用", 无法正常使用.

可以运行注册表编辑器, 定位到 `HKEY_CURRENT_USER\Software\Policies\Microsoft\Windows\System` 下, 看看有没有一个叫 `DisableCMD` 的值, 有的话就删掉, 再试试.

## 3 破解后一些软件运行时报错 "找不到文件".

在不影响软件正常运行的情况下, 可以给软件文件修改一个名称, 再试试. 或者打开注册表编辑器, 定位到 `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options`, 找到和要运行的软件的文件名称相同的项, 删除即可.

# ❤️ 鸣谢

- Bilibili 用户 [lateworker_晚工](https://space.bilibili.com/454920362) 提供界面代码 (详见[此处](https://www.bilibili.com/video/BV1X14y1n7S4), 软件有修改);
- Bilibili 用户 [痕继痕迹](https://space.bilibili.com/39337803) 指导软件界面设计;
- GitHub 用户 [Zhu-Xinrong (Kendall)](https://github.com/Zhu-Xinrong) 指导软件图标设计.