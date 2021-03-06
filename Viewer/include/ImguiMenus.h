#pragma once

#define _USE_MATH_DEFINES
#include <imgui/imgui.h>
#include "Scene.h"
#include "Camera.h"

void DrawImguiMenus(ImGuiIO& io, Scene& scene);
const glm::vec4& GetClearColor();
