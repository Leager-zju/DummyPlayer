# DummyPlayer

支持以下命令

- login <用户账号id> 如存在，从磁盘读取数据，如果不存，创建用户
- set-name <name>
- add-money 增加金币
- add-item <item-id> <item-cnt> 增加道具
- sub-item <item-id> <item-cnt> 减少道具
- logout 登出，并把数据写入磁盘
