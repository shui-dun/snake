# 贪吃蛇冒险

贪吃蛇误入一片全新的领域，你的挑战开始了！这里危机四伏：无处不在的陷阱、突如其来的炸弹……你要如何克服重重阻碍，吃到美味的食物呢？

## 安装方法

```shell
apt install libncursesw5-dev # 如果是msys2，使用pacman -S mingw-w64-x86_64-ncurses
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

## 介绍

* **方向**：
  
  使用`"wsad"`控制方向。
  
* **死亡**： 
  
  当你碰撞墙壁、咬到自己、碰到陷阱或炸弹时，游戏结束，游戏结束时会展示你的分数，维持5秒后退出，当然你可以按`"ctrl+c"`强制退出。
  
* **陷阱（TRAP）**：
  
  用'+'表示，它们随机分布在地图之中，你应当避开它们。
  
* **炸弹（BOMB）**：
  
  用'x'表示，它们在地图中随机游走，如果你的头部碰到炸弹，游戏结束，但你可以将自己的身体围成一个`较小`的圈（太大不行），将炸弹束缚在其中，这时炸弹会被破坏，变为普通的障碍物，而你会获得附加的分数（2）。因此，你应当尽量用身体圈住炸弹，但不要用头部接触它。
  
* **墙壁（BORDER）**：
  
  用'+'表示，它们围在地图四周，你应该避免撞击墙壁。
  
* **食物（FOOD）**：
  
  用'@'表示，在一个时刻地图中只存在一个食物，当你吞吃食物时，你会增加一个长度。
  
* **分数**：
  
  分数是你的长度（初始长度+吞吃食物增加的长度）与附加分数（破坏炸弹）之和，地图的左上角会实时展示你的分数。

## 选项与参数

* **-s N**

  设置蛇移动的速度（Speed），速度有五个等级[0 - 4]，数字越小速度越快，默认情况下为2。
  
* **-h CHAR**

  设置蛇头部（Head）的字符，默认为'O'。
  
* **-o CHAR**
  
  设置蛇身体（bOdy）的字符，默认为'o'。
  
* **-t N**

  设置陷阱（Trap）的数目，数字必须在[0 - MAX_N_TRAP]范围内，(MAX_N_TRAP在源代码被指定为255，这是uint8_t的上界，你可以通过修改源代码来更改这个值)，若你指定的值小于零，将自动调整为零，若你指定的值大于MAX_N_TRAP，将自动调整为MAX_N_TRAP，若不指定，默认为30。
  
* **-b N**

  设置炸弹（Bomb）的数目，数字必须在[0 - MAX_N_BOMB]范围内(MAX_N_TRAP在源代码被指定为20），若你指定的值小于零，将自动调整为零，若你指定的值大于MAX_N_BOMB，将自动调整为MAX_N_BOMB，若不指定，默认为5。

* **-l N**

  设置蛇的初始长度（Len），该值应该介于[2 - COLS / 2],（COLS为控制台的宽度），如果你指定的值不在这个范围内，程序会将该值调节到合适的值，若不指定，默认长度为5。

* **-g**

  上帝（God）模式，你是不死的。

## 截图

![image-20230813162932204](assets/image-20230813162932204.png)

## 作者

黄小可

huang_xiaoke@foxmail.com
