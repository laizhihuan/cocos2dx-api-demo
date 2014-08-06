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

1.用户触摸事件

在处理触摸事件时，既可以重写三个方法`onTouchBegan`,`onTouchMoved`和`onTouchEnded`，也可以直接通过Lambda表达式完成响应逻辑。

用户触摸事件demo,详细请看:[HiTouchScene.cpp](https://github.com/laizhihuan/cocos2dx-api-demo/blob/master/cocos2dx_02_gui/MyCppGame/Classes/HiTouchSence.cpp)


