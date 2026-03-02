- 开工前：拉取最新并把远端变更放到本地顶部（推荐）
```powershell
git pull --rebase origin main
```

- 查看当前状态（可选）
```powershell
git status -sb
```

- 暂存所有修改（包括新建/删除文件）
```powershell
git add -A
```

- 提交（把双引号内替换为描述性信息）
```powershell
git commit -m "你的本次修改说明"
```

- 推送到远程 `main`
```powershell
git push origin main
```

- 使用分支工作（推荐做较大改动），创建并切换到新分支：
```powershell
git checkout -b feature/描述
git push -u origin feature/描述
```
完成后可在 GitHub 发 Pull Request 合并回 `main`。

- 如果 push 被拒绝（提示远端有更新），按提示先拉取并变基，然后继续推送：
```powershell
git pull --rebase origin main
# 若有冲突：手动解决冲突文件后
git add <冲突文件>
git rebase --continue
# 继续推送
git push origin main
```

- 快速查看最近提交
```powershell
git log --oneline -n 10
```

- 如需设置提交身份（只需做一次）
```powershell
git config --global user.name "你的名字"
git config --global user.email "you@example.com"
```

遇到冲突需要帮助时，把冲突文件发给我或运行 `git status` 的输出，我来逐步带你解决。

User: 帮我写一个token交给电脑B的copilot，让他下载工程并把进度添加进去，要符合现在的文件结构，文档可以合并

GitHub Copilot: 我将创建一个 PowerShell 上传脚本和配套说明文件，方便电脑B 使用 token 下载仓库并提交进度。

已创建 [](file:///d%3A/project/c%2B%2B/study/scripts/upload_progress.ps1)

已创建 [](file:///d%3A/project/c%2B%2B/study/scripts/README_for_B.md)

Completed: *拉取最新代码（pull）* (1/6)

脚本和说明已创建于 scripts：

- upload_progress.ps1 — 电脑B 在本地运行的 PowerShell 脚本（支持 token，自动 clone、复制代码到 cpp、合并第一个 md 到 README.md、提交并推送到新分支）。
- README_for_B.md — 面向电脑B 的使用说明（如何生成 token、运行示例、注意事项）。

注意：
- 我不能为你生成 GitHub token；请在电脑B 上按 README_for_B.md 的说明创建 Personal Access Token（`repo` 权限），然后将 token 设置到环境变量 `GITHUB_TOKEN` 后运行脚本，或在运行时输入 token。
- 脚本使用 HTTPS + token 的方式克隆并推送；若希望用 SSH，我可以把脚本改为 SSH 模式（需电脑B 配置好 SSH key）。

需要我把这两个文件提交到 Git 并推送到远程仓库吗？

Made changes.