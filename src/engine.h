#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <stdio.h>
#include <string.h>

#include "types.h"
#include "util.h"

typedef struct engine_config {
	char* window_name;
	u32 window_width;
	u32 window_height;
	char* app_name;
} engine_config;


typedef struct engine {
	// config
	engine_config config;
	
	// State variables
	b8 running;
	b8 visible;
	
	// SDL stuff
	SDL_Event sdl_event;
	SDL_Window* sdl_window;
	
	// Vulkan stuff
	VkDebugUtilsMessengerEXT debug_messenger;
	VkInstance instance;
	VkPhysicalDevice physical_device;
	VkDevice device;
	VkRenderPass renderpass;
	VkBuffer vertex_buffer;
	VkDeviceMemory vertex_buffer_memory;
	VkBuffer index_buffer;
	VkDeviceMemory index_buffer_memory;
	VkDescriptorPool descriptor_pool;
	VkDescriptorSetLayout descriptor_set_layout;
	VkDescriptorSet descriptor_set;
	VkPipelineLayout pipeline_layout;
	VkPipelineCache pipeline_cache;
	VkPipeline pipeline;
	
} engine;

// CORE FUNCTIONS
b8 run_engine(engine* e);
b8 init_engine(engine* e);
b8 loop_engine(engine* e);
b8 cleanup_engine(engine* e);

// CONFIGURATION
b8 clear_engine_config(engine* e);
b8 config_engine(engine* e);

// VULKAN INIT
b8 init_vulkan(engine* e);
