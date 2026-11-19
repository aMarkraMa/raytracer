# M0 内容与提交核对

核对日期：2026-11-17。此文件供你使用，正式被评分的是同目录下的 [discovery-report.md](discovery-report.md)。

## 已阅读的五个页面

你提供的两个链接实际上拼接了五个网址，已拆开并阅读每页正文：

| 页面 | 与 M0 有关的要求 |
|---|---|
| [课程首页](https://learn.glassworks.tech/raytracer/) | 虚构的 2035 年洛杉矶电影工作室背景；重点是可信、可维护、可扩展的渲染工具；课程规定使用 C++。 |
| [How to research](https://learn.glassworks.tech/raytracer/veille-perspective/how-to-research/) | 区分桌面研究与客户访谈；核查原始来源；标明价格查阅日期；区分客户原话、自己的推论及未知问题。 |
| [Discovery report](https://learn.glassworks.tech/raytracer/veille-perspective/discovery-report/) | 英文单文档；五个固定部分；指定文件路径；个人 GitHub 仓库及 README。 |
| [M0 交付与评价](https://learn.glassworks.tech/raytracer/veille-perspective/livrable-et-evaluation/) | 仓库共享给 `glassworks`；填写班级表；提交并推送 `m0` 标签；读取标签处的报告评分。 |
| [Milestones](https://learn.glassworks.tech/raytracer/milestones/) | M0 是个人 discovery report；M1/M2 的代码、M3 的分布式渲染与 RFC 贡献是后续阶段。 |

## 报告内容状态

- [x] **Problem statement**：一句话，交代客户、问题及影响；依据课程 brief，不冒充访谈结果。
- [ ] **Client interview summary**：按你的要求留空，仅保留标题和不可见的填写说明。
- [x] **State of the art**：Arnold、RenderMan、Cycles、pbrt-v4；覆盖商业与开源方案；统一比较作者、许可证、价格、能力、来源；每行有实际查阅日期。
- [x] **What is ray tracing?**：一段说明输入、处理及输出；附入门资料和后续参考。
- [x] **What is C++?**：编程范式、常见陷阱、领域建模；与你确认熟悉的 Python 和 JavaScript/TypeScript 对比；附资料。
- [x] README 和指定目录结构已创建。
- [ ] 你阅读并调整措辞，确保可以脱稿解释两段技术理解；课程明确要求形成自己的理解。

此时是“除访谈外已写好的报告草稿”，不是完整可评分状态。客户是否接受问题定义、现有方案为何不适用、具体性能和质量目标，都不能由桌面研究代替确认。

## 访谈补齐规则

正文暂不填写任何访谈回答。之后用真实记录按主题整理；每条需要都应对应问题、提问者及客户回答，个人推论另行标注，最后列出未解决问题或矛盾。不要把准备的问题当成已问过的问题，也不要把课程背景写成客户引语。

M0 不要求完成 MoSCoW 优先级表或完整的功能/非功能需求分类；研究方法页面明确说明本次报告可以先不做这一项。

## 提交前剩余事项

课程页面列出的截止时间是 **11 月 16 日星期一 23:00，巴黎时间**。按本次课程所在的 2026 年理解，当前已超过该时间。这里没有回填日期、创建历史提交或移动已有标签；迟交是否接受需要与教师核实。

1. 补入真实访谈记录并复核英文正文。
2. 创建或选定你自己的 GitHub 项目，把本目录内容放入仓库。
3. 在仓库设置的 Collaborators 中邀请 **`glassworks`**。课程明确要求这一操作；即使仓库公开，也按要求完成。
4. 在 [班级表](https://docs.google.com/spreadsheets/d/1iy5ryZ4w0Hk_DC-taq4zpf2zPQrsz0NaER8peg6MzVA/edit?usp=sharing) 填写名字、姓氏和**项目仓库链接**，不是个人主页链接。
5. 提交、推送报告，然后在拟提交的那个 commit 上创建并推送 `m0` 标签。
6. 确认远端 `m0` 标签存在，并能看到标签对应版本的 `docs/discovery/discovery-report.md`。

以下命令是供你在已经配置好 Git 仓库和 `origin` 后使用的说明，本次没有执行：

```bash
git status
git add README.md docs/discovery/discovery-report.md docs/discovery/m0-checklist.zh.md
git commit -m "docs: add m0 discovery report"
git push -u origin HEAD
git tag m0
git push origin m0
git show m0:docs/discovery/discovery-report.md
git ls-remote --tags origin refs/tags/m0
```

如果仓库已有 `m0` 标签，不要直接重复或覆盖它；先检查它对应的内容及教师对迟交/修改的安排。普通后续提交不会改变已有标签，评分脚本也不会自动读取主分支上的最新版本。

## 评价方式

第一轮由脚本根据班级表定位仓库和标签，并用 Claude 初评报告；第二轮由教师复核。没有项目入口、没有 `m0` 标签或文件路径错误，都可能导致报告无法被读取。当前完成的是本地文件准备，未创建远端仓库、推送标签、邀请协作者或填写班级表。
