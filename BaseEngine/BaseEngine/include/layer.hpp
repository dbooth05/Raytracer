#ifndef LAYER_HPP
#define LAYER_HPP

namespace BaseEngine {

    class Layer {
        public:
            virtual ~Layer() = default;

            virtual void onAttach() {}
            virtual void onDetach() {}

            virtual void onUpdate(float ts) {}
            virtual void onUIRender() {}
    };
}

#endif
