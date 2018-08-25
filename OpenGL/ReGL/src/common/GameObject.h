//
// Created by ��� on 2018/7/29.
//

#ifndef REGL_GAMEOBJECT_HPP
#define REGL_GAMEOBJECT_HPP

#include <map>
#include <vector>
#include "Object.h"
#include "Singleton.h"
#include "Component.h"

using namespace Utility;

namespace ReGL{

    class GameObject;

    /**
     * GameObject������
     */
    class GameObjectManager : public Singleton<GameObjectManager> {
    public:
        void AddGameObject(GameObject& go);
        void RemoveGameObject(GameObject &go);
        const bool GetGameObject(const uint64_t guid, GameObject* result) const;
    private:
        std::map<uint64_t, GameObject> game_object_map_;
    };

    /**
     * GameObject,ʹ��Component��������Դ�ɲ�ͬ��Ŀ��
     */
    class GameObject : public Object {
    public:
        GameObject(){
            GameObjectManager::GetInstance().AddGameObject(*this);
        }

        GameObject(const GameObject &test) = delete;
        void operator=(const GameObject &test) = delete;

        void Destroy() override {
            GameObjectManager::GetInstance().RemoveGameObject(*this);
        }

    private:
        std::vector<Component> components_;
    };
}



#endif //REGL_GAMEOBJECT_HPP
