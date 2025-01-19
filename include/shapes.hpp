#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"

#include <SDL2/SDL.h>

class Sphere {
    public:
        Sphere(float x, float y, float radius) : 
            pos(x, y), radius(radius), dragging(false) {}

        void UpdatePos(const ImVec2& mousePos, bool isDragging) {
            if (isDragging) {
                pos = mousePos;
            }
        }

        bool isMouseOver(const ImVec2& mousePos) const {
            float dx = mousePos.x - pos.x;
            float dy = mousePos.y - pos.y;
            return (dx * dx + dy * dy) <= (radius * radius);
        }

        void Render(SDL_Renderer* rend) const {
            SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

            // draw sphere
            for (int w = 0; w < radius * 2; w++) {
                for (int h = 0; h < radius * 2; h++) {
                    int dx = radius - w;
                    int dy = radius - h;
                    if ((dx * dx + dy * dy) <= (radius * radius)) {
                        SDL_RenderDrawPoint(rend, pos.x + dx, pos.y + dy);
                    }
                }
            }    
        }

        const ImVec2& GetPos() const { return pos; }
        void SetDragging(bool draggingStatus) { dragging = draggingStatus; }
        
    private:
        ImVec2 pos;
        float radius;

        bool dragging;
};

#endif