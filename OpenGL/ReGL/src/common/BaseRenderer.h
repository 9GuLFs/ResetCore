//
// Created by ��� on 2018/8/26.
//

#ifndef REGL_BASERENDERER_H
#define REGL_BASERENDERER_H

#include "Singleton.h"
#include "Component.h"
#include "Camera.h"
#include <vector>

using namespace Utility;

namespace ReGL{

    class BaseRenderer;

    /**
     * �������е�Renderer��Camera�Խ�����Ⱦ
     */
    class RendererManager : public Singleton<RendererManager>{

    public:
        void AddRenderer(const BaseRenderer& renderer);

        void RemoveRenderer(const BaseRenderer& renderer);

        void AddCamera(const Camera& camera);

        void RemoveCamera(const Camera& camera);

        bool Init();

        bool Render();

        bool UnInit();

    private:
        std::vector<Camera> camera_list;
        std::vector<BaseRenderer> renderer_list_;
    };

    /**
     * ������Ⱦ����
     */
    class BaseRenderer : public Component {

    public:
        void Render(Camera& camera);


    };
}


#endif //REGL_BASERENDERER_H
