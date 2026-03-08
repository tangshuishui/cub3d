This project has been created as part of the 42 curriculum by yshi and hanwang


cub3d/
├── Makefile                # 编译规则 (NAME, all, clean, fclean, re)
├── includes/
│   └── cub3d.h             # 包含所有库、宏定义和结构体、函数声明
└── src/
    ├── main.c              # 检查参数数量，初始化结构体，启动MLX Loop
    │
    ├── init/               # 【初始化模块】
    │   ├── init_data.c     # 将 t_game 内所有指针设为 NULL，变量置 0
    │   └── init_mlx.c      # 初始化 MLX，创建窗口和 screen buffer
    │
    ├── parse/              # 【解析器模块】 (最繁琐的部分)
    │   ├── parse_main.c    # 打开 .cub 文件，控制读取流程
    │   ├── parse_config.c  # 提取 NO, SO, WE, EA 的路径和 F, C 的 RGB 值
    │   ├── parse_map.c     # 提取地图主体，找到最长行，存为矩阵
    │   ├── parse_utils.c   # RGB 字符串转 Hex int 的工具，跳过空格的工具
    │   └── flood_fill.c    # 校验地图封闭性 (检查 0 是否接触到边界或空格)
    │
    ├── render/             # 【渲染模块】
    │   ├── render_main.c   # 渲染主循环，清空屏幕，调用 Raycasting
    │   ├── raycast.c       # 执行 DDA 算法，计算撞墙距离和撞击面
    │   ├── draw_walls.c    # 计算墙壁的屏幕高度，计算纹理 X/Y 坐标并提取像素
    │   └── draw_utils.c    # 画天花板和地板的循环，以及 my_mlx_pixel_put 函数
    │
    ├── events/             # 【交互与物理模块】
    │   ├── hooks.c         # 注册按键按下 (Press) 和松开 (Release) 事件
    │   ├── movement.c      # 根据 player.dir 和 player.pos 更新坐标 (带墙壁碰撞检测)
    │   └── rotation.c      # 使用旋转矩阵更新 player.dir 和 player.plane
    │
    └── utils/              # 【工具与清理模块】
        ├── cleanup.c       # free_map, destroy_images, 释放所有内存
        └── error.c         # 打印 "Error\n" 并输出具体原因，随后安全退出


https://free-game-assets.itch.io/free-industrial-zone-tileset-pixel-art
https://totuslotus.itch.io/free-pixel-art-tiles
https://clavs.itch.io/16x16neon-tileset
https://karsiori.itch.io/free-pixel-art-neon-signs
