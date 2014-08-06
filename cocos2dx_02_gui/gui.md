### cocos2dx之GUI实例

#### 用户交互的处理 

用户触摸事件demo,详细请看:HiTouchScene.cpp

* 如何添加事件监听？

```cpp

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


