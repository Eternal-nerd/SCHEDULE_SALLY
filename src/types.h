#pragma once

#include <stdbool.h>

// numeric
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;
typedef float f32;
typedef double f64;
typedef int b32;
typedef bool b8;

// vectors

// UI
typedef enum OverlayMode {
    OVERLAY_DEFAULT = 0,
    OVERLAY_MENU = 1,
    OVERLAY_STATS = 2,
    OVERLAY_INVENTORY = 3
} OverlayMode;

typedef enum OverlayContainerType {
    OVERLAY_CONTAINER_COLUMN = 0,
    OVERLAY_CONTAINER_ROW = 1,
    OVERLAY_CONTAINER_BOX = 2,
} OverlayContainerType;

/*
struct OverlayState {
    bool initialized = false;

    // mouse stuff
    bool mouseDown = false;
    glm::vec2 mousePos = { 0.f,0.f };
    glm::vec2 oldMousePos = { 0.f,0.f };

    // state stuff
    bool menuShown = false;
    float scale = 1.f;

    // screen size stuff
    VkExtent2D extent;

    bool updatedTri = true;
    bool updatedLine = true;
};

struct OverlayElementState {
    OverlayMode mode = OVERLAY_DEFAULT;

    // ??? glm::vec2 position = {0.f, 0.f};

    bool hovered = false;
    bool dragged = false;
    int interaction = 0;

    bool movable = false;
};*/


