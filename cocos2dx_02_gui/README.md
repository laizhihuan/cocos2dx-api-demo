### cocos2dx之GUI实例

#### 1.事件分发器 

事件分发器的工作由三部分组成：

* 事件分发器 `EventDispatcher`
* 事件类型 `EventTouch`, `EventKeyboard` 等
* 事件监听器 `EventListenerTouch`, `EventListenerKeyboard` 等

监听器实现了各种触发后的逻辑，在适当时候由事件分发器分发事件类型，然后调用相应类型的监听器。

* 事件监听器有以下几种：
	* 触摸事件 `EventListenerTouch` 
	* 键盘响应事件 `EventListenerKeyboard`
	* 鼠标响应事件 `EventListenerMouse`
	* 自定义事件 `EventListenerCustom`
	* 加速记录事件 `EventListenerAcceleration`

* 如何添加事件监听？

```c

    //1.添加监听器
    auto listener = EventListenerTouchOneByOne::create();
    
    //2.监听器的闭包函数
    listener->onTouchBegan = [label](Touch *t,Event *event) {
        return false;
    };
    
    //注册label监听器
    Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(listener, label);
```

#### 2.用户输入事件

#####2.1.用户触摸事件

在处理触摸事件时，既可以重写三个方法`onTouchBegan`,`onTouchMoved`和`onTouchEnded`，也可以直接通过Lambda表达式完成响应逻辑。

用户触摸事件demo,详细请看:[HiTouchScene.cpp](https://github.com/laizhihuan/cocos2dx-api-demo/blob/master/cocos2dx_02_gui/MyCppGame/Classes/HiTouchSence.cpp)

#### 3.常用控件

* Director:     是用来却换Scene,导演类是游戏中的组织者和领导者，是整个游戏的负责人、总指挥，导演类可以制定游戏的运行规则，从而让游戏内的场景、布景类和精灵类有序地进行。
* Scene:        导演类是游戏中的组织者和领导者，是整个游戏的负责人、总指挥，导演类可以制定游戏的运行规则，从而让游戏内的场景、布景类和精灵类有序地进行。管理游戏元素，eg: Layer，Label，* Sprite....
* Layer:        一个场景可以由多个布景层构成，布景层就是关卡里的背景，不同关卡也就是场景需要的布景层不同。有时候，为了游戏的不同模块的管理更加方便，会把一个场景分为多个布景层，如UI布景层、游戏布景层；有些游戏需要更细致的划分，可以分为游戏对象布景层和游戏地图布景图。
* Sprite:       cocos2dx中图像相关的呈现控件
* Log:          cocos2dx跨平台日志输出,ios,android,win都是通用
* MessageBox:   cocos2dx的对话框,游戏开发中少用，一般都是用自定义的对话框
* LabelTTF:     文本显示（输出）标签
* TextFieldTTF: 文本输入标签,首先添加一个监听器,然后连接IME(输入法)
* Menu:         菜单的使用
* TableView:    cocos2dx列表的使用
       
```c   
	
	Size size = Director::getInstance()->getVisibleSize();
	
	Sprite *s=Sprite::create("img.jpg");
	s->setAnchorPoint(Point(0,0));
	addChild(s);
	
	MessageBox("message content","message title");
	
	LabelTTF *label = LabelTTF::create();
	label->setString("hi label");
	label->setFontSize(36);
	label->setPosition(size.width/2,size.height/2);
	addChild(label);
	
	TextFieldTTF *txt = TextFieldTTF::create();
	txt->setString("hi text");
	txt->setFontSize(36);
	txt->setPosition(size.width/2,size.height/2);
	addChild(label);
	
	auto menu = Menu::create(
					MenuItemImage::create("normal.png","selected.png",[](Object* obj){log("menu item touched")
					}),NULL);
	addChild(menu);
	
	
	
```   

#### 4.自定义类
* 自定义类:       
* 引入        `#include <cocos2d.h>` 
* 使用        `USING_NS_CC;` 
* 定义默认方法 `virtual bool init();` 
* 使用宏创建类 `CREATE_FUNC(HiImageSence)`

#### 5.内存管理

#### 6.坐标系简介

* OpenGL坐标系:Cocos2D-X以OpenGL和OpenGL ES为基础，所以自然支持OpenGL坐标系，坐标系原点在屏幕左下角，x轴正方向向右，y轴正方向向上。

* 屏幕坐标系:屏幕坐标系使用的是不同的坐标系统，原点在屏幕左上角，x轴正方向向右，y轴正方向向下。

在之前的引擎版本中，屏幕触摸事件Touch传入的位置信息使用的是屏幕坐标系。因此在Cocos2D-X中对触摸事件做出响应前，需要首先把触摸点转化到OpenGL坐标系，需要调用Director的convertToGL函数来完成这一转化，但是在3.0版本中，Touch把转化的一步封装在了自己的函数里，可以直接调用getLocation函数来获得坐标，这样就不需要再进行转换了，简化了调用函数和接口。




